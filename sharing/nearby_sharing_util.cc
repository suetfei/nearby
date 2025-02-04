// Copyright 2023 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "sharing/nearby_sharing_util.h"

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <filesystem>  // NOLINT(build/c++17)
#include <optional>
#include <string>
#include <vector>

#include "absl/hash/hash.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "internal/flags/nearby_flags.h"
#include "internal/platform/device_info.h"
#include "proto/sharing_enums.pb.h"
#include "sharing/advertisement.h"
#include "sharing/certificates/nearby_share_decrypted_public_certificate.h"
#include "sharing/common/nearby_share_enums.h"
#include "sharing/flags/generated/nearby_sharing_feature_flags.h"
#include "sharing/internal/base/encode.h"
#include "sharing/internal/public/logging.h"
#include "sharing/nearby_connections_types.h"
#include "sharing/nearby_sharing_service.h"
#include "sharing/transfer_metadata.h"

namespace nearby {
namespace sharing {
namespace {
using ::location::nearby::proto::sharing::AttachmentTransmissionStatus;
using ::location::nearby::proto::sharing::ConnectionLayerStatus;

// Used to hash a token into a 4 digit string.
constexpr int kHashModulo = 9973;
constexpr int kHashBaseMultiplier = 31;
}  // namespace

bool IsBackgroundScanningFeatureEnabled() {
  return NearbyFlags::GetInstance().GetBoolFlag(
      sharing::config_package_nearby::nearby_sharing_feature::
          kEnableBackgroundScanning);
}

std::string ReceiveSurfaceStateToString(
    NearbySharingService::ReceiveSurfaceState state) {
  switch (state) {
    case NearbySharingService::ReceiveSurfaceState::kForeground:
      return "FOREGROUND";
    case NearbySharingService::ReceiveSurfaceState::kBackground:
      return "BACKGROUND";
    case NearbySharingService::ReceiveSurfaceState::kUnknown:
      return "UNKNOWN";
  }
}

std::string SendSurfaceStateToString(
    NearbySharingService::SendSurfaceState state) {
  switch (state) {
    case NearbySharingService::SendSurfaceState::kForeground:
      return "FOREGROUND";
    case NearbySharingService::SendSurfaceState::kBackground:
      return "BACKGROUND";
    case NearbySharingService::SendSurfaceState::kUnknown:
      return "UNKNOWN";
  }
}

std::string PowerLevelToString(PowerLevel level) {
  switch (level) {
    case PowerLevel::kLowPower:
      return "LOW_POWER";
    case PowerLevel::kMediumPower:
      return "MEDIUM_POWER";
    case PowerLevel::kHighPower:
      return "HIGH_POWER";
    case PowerLevel::kUnknown:
      return "UNKNOWN";
  }
}

std::optional<std::vector<uint8_t>> GetBluetoothMacAddressFromCertificate(
    const NearbyShareDecryptedPublicCertificate& certificate) {
  if (!certificate.unencrypted_metadata().has_bluetooth_mac_address()) {
    NL_LOG(WARNING) << __func__ << ": Public certificate "
                    << nearby::utils::HexEncode(certificate.id())
                    << " did not contain a Bluetooth mac address.";
    return std::nullopt;
  }

  std::string mac_address =
      certificate.unencrypted_metadata().bluetooth_mac_address();
  if (mac_address.size() != 6) {
    NL_LOG(ERROR) << __func__ << ": Invalid bluetooth mac address: '"
                  << mac_address << "'";
    return std::nullopt;
  }

  return std::vector<uint8_t>(mac_address.begin(), mac_address.end());
}

std::optional<std::string> GetDeviceName(
    const Advertisement* advertisement,
    const std::optional<NearbyShareDecryptedPublicCertificate>& certificate) {
  NL_DCHECK(advertisement);

  // Device name is always included when visible to everyone.
  if (advertisement->device_name().has_value()) {
    return advertisement->device_name();
  }

  // For contacts only advertisements, we can't do anything without the
  // certificate.
  if (!certificate.has_value() ||
      !certificate->unencrypted_metadata().has_device_name()) {
    return std::nullopt;
  }

  return certificate->unencrypted_metadata().device_name();
}

// Return the most stable device identifier with the following priority:
//   1. Hash of Bluetooth MAC address.
//   2. Certificate ID.
//   3. Endpoint ID.
std::string GetDeviceId(
    absl::string_view endpoint_id,
    const std::optional<NearbyShareDecryptedPublicCertificate>& certificate) {
  if (!certificate.has_value()) {
    return std::string(endpoint_id);
  }

  std::optional<std::vector<uint8_t>> mac_address =
      GetBluetoothMacAddressFromCertificate(*certificate);
  if (mac_address.has_value()) {
    return absl::StrCat(absl::Hash<std::vector<uint8_t>>{}(*mac_address));
  }

  if (!certificate->id().empty()) {
    return std::string(certificate->id().begin(), certificate->id().end());
  }

  return std::string(endpoint_id);
}

std::optional<std::string> TokenToFourDigitString(
    const std::optional<std::vector<uint8_t>>& bytes) {
  if (!bytes.has_value()) {
    return std::nullopt;
  }

  int hash = 0;
  int multiplier = 1;
  for (uint8_t byte : *bytes) {
    // Java bytes are signed two's complement so cast to use the correct sign.
    hash = (hash + static_cast<int8_t>(byte) * multiplier) % kHashModulo;
    multiplier = (multiplier * kHashBaseMultiplier) % kHashModulo;
  }

  return absl::StrFormat("%04d", std::abs(hash));
}

bool IsOutOfStorage(DeviceInfo& device_info, std::filesystem::path file_path,
                    int64_t storage_required) {
  std::optional<size_t> available_storage =
      device_info.GetAvailableDiskSpaceInBytes(file_path);

  if (!available_storage.has_value()) {
    return false;
  }

  return *available_storage <= storage_required;
}

AttachmentTransmissionStatus ConvertToTransmissionStatus(
    TransferMetadata::Status status) {
  switch (status) {
    case TransferMetadata::Status::kComplete:
      return AttachmentTransmissionStatus::
          COMPLETE_ATTACHMENT_TRANSMISSION_STATUS;
    case TransferMetadata::Status::kCancelled:
      return AttachmentTransmissionStatus::
          CANCELED_ATTACHMENT_TRANSMISSION_STATUS;
    case TransferMetadata::Status::kFailed:
      return AttachmentTransmissionStatus::
          FAILED_ATTACHMENT_TRANSMISSION_STATUS;
    case TransferMetadata::Status::kAwaitingRemoteAcceptanceFailed:
      return AttachmentTransmissionStatus::
          AWAITING_REMOTE_ACCEPTANCE_FAILED_ATTACHMENT;
    case TransferMetadata::Status::kFailedToInitiateOutgoingConnection:
      return AttachmentTransmissionStatus::FAILED_NULL_CONNECTION_INIT_OUTGOING;
    case TransferMetadata::Status::kFailedToReadOutgoingConnectionResponse:
      return AttachmentTransmissionStatus::FAILED_UNKNOWN_REMOTE_RESPONSE;
    case TransferMetadata::Status::kIncompletePayloads:
      return AttachmentTransmissionStatus::FAILED_NO_PAYLOAD;
    case TransferMetadata::Status::kInvalidIntroductionFrame:
      return AttachmentTransmissionStatus::FAILED_WRITE_INTRODUCTION;
    case TransferMetadata::Status::kMediaUnavailable:
      return AttachmentTransmissionStatus::MEDIA_UNAVAILABLE_ATTACHMENT;
    case TransferMetadata::Status::kMissingEndpointId:
      return AttachmentTransmissionStatus::FAILED_NO_SHARE_TARGET_ENDPOINT;
    case TransferMetadata::Status::kMissingPayloads:
      return AttachmentTransmissionStatus::FAILED_NO_PAYLOAD;
    case TransferMetadata::Status::kMissingTransferUpdateCallback:
      return AttachmentTransmissionStatus::FAILED_NO_TRANSFER_UPDATE_CALLBACK;
    case TransferMetadata::Status::kPairedKeyVerificationFailed:
      return AttachmentTransmissionStatus::FAILED_PAIRED_KEYHANDSHAKE;
    case TransferMetadata::Status::kRejected:
      return AttachmentTransmissionStatus::REJECTED_ATTACHMENT;
    case TransferMetadata::Status::kTimedOut:
      return AttachmentTransmissionStatus::TIMED_OUT_ATTACHMENT;
    case TransferMetadata::Status::kUnexpectedDisconnection:
      return AttachmentTransmissionStatus::FAILED_NULL_CONNECTION_DISCONNECTED;
    case TransferMetadata::Status::kUnsupportedAttachmentType:
      return AttachmentTransmissionStatus::
          UNSUPPORTED_ATTACHMENT_TYPE_ATTACHMENT;
    default:
      return AttachmentTransmissionStatus::
          UNKNOWN_ATTACHMENT_TRANSMISSION_STATUS;
  }
}

ConnectionLayerStatus ConvertToConnectionLayerStatus(Status status) {
  switch (status) {
    case Status::kUnknown:
      return ConnectionLayerStatus::CONNECTION_LAYER_STATUS_UNKNOWN;
    case Status::kSuccess:
      return ConnectionLayerStatus::CONNECTION_LAYER_STATUS_SUCCESS;
    case Status::kError:
      return ConnectionLayerStatus::CONNECTION_LAYER_STATUS_ERROR;
    case Status::kOutOfOrderApiCall:
      return ConnectionLayerStatus::
          CONNECTION_LAYER_STATUS_OUT_OF_ORDER_API_CALL;
    case Status::kAlreadyHaveActiveStrategy:
      return ConnectionLayerStatus::
          CONNECTION_LAYER_STATUS_ALREADY_HAVE_ACTIVE_STRATEGY;
    case Status::kAlreadyAdvertising:
      return ConnectionLayerStatus::CONNECTION_LAYER_STATUS_ALREADY_ADVERTISING;
    case Status::kAlreadyDiscovering:
      return ConnectionLayerStatus::CONNECTION_LAYER_STATUS_ALREADY_DISCOVERING;
    case Status::kAlreadyListening:
      return ConnectionLayerStatus::CONNECTION_LAYER_STATUS_ALREADY_LISTENING;
    case Status::kEndpointIOError:
      return ConnectionLayerStatus::CONNECTION_LAYER_STATUS_END_POINT_IO_ERROR;
    case Status::kEndpointUnknown:
      return ConnectionLayerStatus::CONNECTION_LAYER_STATUS_END_POINT_UNKNOWN;
    case Status::kConnectionRejected:
      return ConnectionLayerStatus::CONNECTION_LAYER_STATUS_CONNECTION_REJECTED;
    case Status::kAlreadyConnectedToEndpoint:
      return ConnectionLayerStatus::
          CONNECTION_LAYER_STATUS_ALREADY_CONNECTED_TO_END_POINT;
    case Status::kNotConnectedToEndpoint:
      return ConnectionLayerStatus::
          CONNECTION_LAYER_STATUS_NOT_CONNECTED_TO_END_POINT;
    case Status::kBluetoothError:
      return ConnectionLayerStatus::CONNECTION_LAYER_STATUS_BLUETOOTH_ERROR;
    case Status::kBleError:
      return ConnectionLayerStatus::CONNECTION_LAYER_STATUS_BLE_ERROR;
    case Status::kWifiLanError:
      return ConnectionLayerStatus::CONNECTION_LAYER_STATUS_WIFI_LAN_ERROR;
    case Status::kPayloadUnknown:
      return ConnectionLayerStatus::CONNECTION_LAYER_STATUS_PAYLOAD_UNKNOWN;
    case Status::kReset:
      return ConnectionLayerStatus::CONNECTION_LAYER_STATUS_RESET;
    case Status::kTimeout:
      return ConnectionLayerStatus::CONNECTION_LAYER_STATUS_TIMEOUT;
    default:
      return ConnectionLayerStatus::CONNECTION_LAYER_STATUS_UNKNOWN;
  }
}

}  // namespace sharing
}  // namespace nearby
