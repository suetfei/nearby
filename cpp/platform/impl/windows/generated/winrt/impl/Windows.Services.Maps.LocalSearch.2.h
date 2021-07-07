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

#ifndef WINRT_Windows_Services_Maps_LocalSearch_2_H
#define WINRT_Windows_Services_Maps_LocalSearch_2_H
#include "winrt/impl/Windows.Devices.Geolocation.1.h"
#include "winrt/impl/Windows.Services.Maps.LocalSearch.1.h"
WINRT_EXPORT namespace winrt::Windows::Services::Maps::LocalSearch
{
    struct LocalCategories
    {
        LocalCategories() = delete;
        [[nodiscard]] static auto BankAndCreditUnions();
        [[nodiscard]] static auto EatDrink();
        [[nodiscard]] static auto Hospitals();
        [[nodiscard]] static auto HotelsAndMotels();
        [[nodiscard]] static auto All();
        [[nodiscard]] static auto Parking();
        [[nodiscard]] static auto SeeDo();
        [[nodiscard]] static auto Shop();
    };
    struct __declspec(empty_bases) LocalLocation : winrt::Windows::Services::Maps::LocalSearch::ILocalLocation,
        impl::require<LocalLocation, winrt::Windows::Services::Maps::LocalSearch::ILocalLocation2>
    {
        LocalLocation(std::nullptr_t) noexcept {}
        LocalLocation(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Services::Maps::LocalSearch::ILocalLocation(ptr, take_ownership_from_abi) {}
        LocalLocation(LocalLocation const&) noexcept = default;
        LocalLocation(LocalLocation&&) noexcept = default;
        LocalLocation& operator=(LocalLocation const&) & noexcept = default;
        LocalLocation& operator=(LocalLocation&&) & noexcept = default;
    };
    struct LocalLocationFinder
    {
        LocalLocationFinder() = delete;
        static auto FindLocalLocationsAsync(param::hstring const& searchTerm, winrt::Windows::Devices::Geolocation::Geocircle const& searchArea, param::hstring const& localCategory, uint32_t maxResults);
    };
    struct __declspec(empty_bases) LocalLocationFinderResult : winrt::Windows::Services::Maps::LocalSearch::ILocalLocationFinderResult
    {
        LocalLocationFinderResult(std::nullptr_t) noexcept {}
        LocalLocationFinderResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Services::Maps::LocalSearch::ILocalLocationFinderResult(ptr, take_ownership_from_abi) {}
        LocalLocationFinderResult(LocalLocationFinderResult const&) noexcept = default;
        LocalLocationFinderResult(LocalLocationFinderResult&&) noexcept = default;
        LocalLocationFinderResult& operator=(LocalLocationFinderResult const&) & noexcept = default;
        LocalLocationFinderResult& operator=(LocalLocationFinderResult&&) & noexcept = default;
    };
    struct __declspec(empty_bases) LocalLocationHoursOfOperationItem : winrt::Windows::Services::Maps::LocalSearch::ILocalLocationHoursOfOperationItem
    {
        LocalLocationHoursOfOperationItem(std::nullptr_t) noexcept {}
        LocalLocationHoursOfOperationItem(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Services::Maps::LocalSearch::ILocalLocationHoursOfOperationItem(ptr, take_ownership_from_abi) {}
        LocalLocationHoursOfOperationItem(LocalLocationHoursOfOperationItem const&) noexcept = default;
        LocalLocationHoursOfOperationItem(LocalLocationHoursOfOperationItem&&) noexcept = default;
        LocalLocationHoursOfOperationItem& operator=(LocalLocationHoursOfOperationItem const&) & noexcept = default;
        LocalLocationHoursOfOperationItem& operator=(LocalLocationHoursOfOperationItem&&) & noexcept = default;
    };
    struct __declspec(empty_bases) LocalLocationRatingInfo : winrt::Windows::Services::Maps::LocalSearch::ILocalLocationRatingInfo
    {
        LocalLocationRatingInfo(std::nullptr_t) noexcept {}
        LocalLocationRatingInfo(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Services::Maps::LocalSearch::ILocalLocationRatingInfo(ptr, take_ownership_from_abi) {}
        LocalLocationRatingInfo(LocalLocationRatingInfo const&) noexcept = default;
        LocalLocationRatingInfo(LocalLocationRatingInfo&&) noexcept = default;
        LocalLocationRatingInfo& operator=(LocalLocationRatingInfo const&) & noexcept = default;
        LocalLocationRatingInfo& operator=(LocalLocationRatingInfo&&) & noexcept = default;
    };
    struct PlaceInfoHelper
    {
        PlaceInfoHelper() = delete;
        static auto CreateFromLocalLocation(winrt::Windows::Services::Maps::LocalSearch::LocalLocation const& location);
    };
}
#endif