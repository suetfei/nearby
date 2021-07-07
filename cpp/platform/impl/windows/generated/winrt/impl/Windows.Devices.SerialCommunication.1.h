// Copyright 2020 Google LLC
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

// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210505.3

#ifndef WINRT_Windows_Devices_SerialCommunication_1_H
#define WINRT_Windows_Devices_SerialCommunication_1_H
#include "winrt/impl/Windows.Foundation.0.h"
#include "winrt/impl/Windows.Devices.SerialCommunication.0.h"
WINRT_EXPORT namespace winrt::Windows::Devices::SerialCommunication
{
    struct __declspec(empty_bases) IErrorReceivedEventArgs :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IErrorReceivedEventArgs>
    {
        IErrorReceivedEventArgs(std::nullptr_t = nullptr) noexcept {}
        IErrorReceivedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IErrorReceivedEventArgs(IErrorReceivedEventArgs const&) noexcept = default;
        IErrorReceivedEventArgs(IErrorReceivedEventArgs&&) noexcept = default;
        IErrorReceivedEventArgs& operator=(IErrorReceivedEventArgs const&) & noexcept = default;
        IErrorReceivedEventArgs& operator=(IErrorReceivedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IPinChangedEventArgs :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IPinChangedEventArgs>
    {
        IPinChangedEventArgs(std::nullptr_t = nullptr) noexcept {}
        IPinChangedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IPinChangedEventArgs(IPinChangedEventArgs const&) noexcept = default;
        IPinChangedEventArgs(IPinChangedEventArgs&&) noexcept = default;
        IPinChangedEventArgs& operator=(IPinChangedEventArgs const&) & noexcept = default;
        IPinChangedEventArgs& operator=(IPinChangedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) ISerialDevice :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<ISerialDevice>,
        impl::require<winrt::Windows::Devices::SerialCommunication::ISerialDevice, winrt::Windows::Foundation::IClosable>
    {
        ISerialDevice(std::nullptr_t = nullptr) noexcept {}
        ISerialDevice(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        ISerialDevice(ISerialDevice const&) noexcept = default;
        ISerialDevice(ISerialDevice&&) noexcept = default;
        ISerialDevice& operator=(ISerialDevice const&) & noexcept = default;
        ISerialDevice& operator=(ISerialDevice&&) & noexcept = default;
    };
    struct __declspec(empty_bases) ISerialDeviceStatics :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<ISerialDeviceStatics>
    {
        ISerialDeviceStatics(std::nullptr_t = nullptr) noexcept {}
        ISerialDeviceStatics(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        ISerialDeviceStatics(ISerialDeviceStatics const&) noexcept = default;
        ISerialDeviceStatics(ISerialDeviceStatics&&) noexcept = default;
        ISerialDeviceStatics& operator=(ISerialDeviceStatics const&) & noexcept = default;
        ISerialDeviceStatics& operator=(ISerialDeviceStatics&&) & noexcept = default;
    };
}
#endif