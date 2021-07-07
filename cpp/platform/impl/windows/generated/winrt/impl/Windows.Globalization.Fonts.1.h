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

#ifndef WINRT_Windows_Globalization_Fonts_1_H
#define WINRT_Windows_Globalization_Fonts_1_H
#include "winrt/impl/Windows.Globalization.Fonts.0.h"
WINRT_EXPORT namespace winrt::Windows::Globalization::Fonts
{
    struct __declspec(empty_bases) ILanguageFont :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<ILanguageFont>
    {
        ILanguageFont(std::nullptr_t = nullptr) noexcept {}
        ILanguageFont(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        ILanguageFont(ILanguageFont const&) noexcept = default;
        ILanguageFont(ILanguageFont&&) noexcept = default;
        ILanguageFont& operator=(ILanguageFont const&) & noexcept = default;
        ILanguageFont& operator=(ILanguageFont&&) & noexcept = default;
    };
    struct __declspec(empty_bases) ILanguageFontGroup :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<ILanguageFontGroup>
    {
        ILanguageFontGroup(std::nullptr_t = nullptr) noexcept {}
        ILanguageFontGroup(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        ILanguageFontGroup(ILanguageFontGroup const&) noexcept = default;
        ILanguageFontGroup(ILanguageFontGroup&&) noexcept = default;
        ILanguageFontGroup& operator=(ILanguageFontGroup const&) & noexcept = default;
        ILanguageFontGroup& operator=(ILanguageFontGroup&&) & noexcept = default;
    };
    struct __declspec(empty_bases) ILanguageFontGroupFactory :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<ILanguageFontGroupFactory>
    {
        ILanguageFontGroupFactory(std::nullptr_t = nullptr) noexcept {}
        ILanguageFontGroupFactory(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        ILanguageFontGroupFactory(ILanguageFontGroupFactory const&) noexcept = default;
        ILanguageFontGroupFactory(ILanguageFontGroupFactory&&) noexcept = default;
        ILanguageFontGroupFactory& operator=(ILanguageFontGroupFactory const&) & noexcept = default;
        ILanguageFontGroupFactory& operator=(ILanguageFontGroupFactory&&) & noexcept = default;
    };
}
#endif