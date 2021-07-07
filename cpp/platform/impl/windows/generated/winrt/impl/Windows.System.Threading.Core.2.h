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

#ifndef WINRT_Windows_System_Threading_Core_2_H
#define WINRT_Windows_System_Threading_Core_2_H
#include "winrt/impl/Windows.Foundation.1.h"
#include "winrt/impl/Windows.System.Threading.1.h"
#include "winrt/impl/Windows.System.Threading.Core.1.h"
WINRT_EXPORT namespace winrt::Windows::System::Threading::Core
{
    struct SignalHandler : Windows::Foundation::IUnknown
    {
        SignalHandler(std::nullptr_t = nullptr) noexcept {}
        SignalHandler(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        SignalHandler(SignalHandler const&) noexcept = default;
        SignalHandler(SignalHandler&&) noexcept = default;
        SignalHandler& operator=(SignalHandler const&) & noexcept = default;
        SignalHandler& operator=(SignalHandler&&) & noexcept = default;
        template <typename L> SignalHandler(L lambda);
        template <typename F> SignalHandler(F* function);
        template <typename O, typename M> SignalHandler(O* object, M method);
        template <typename O, typename M> SignalHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> SignalHandler(weak_ref<O>&& object, M method);
        auto operator()(winrt::Windows::System::Threading::Core::SignalNotifier const& signalNotifier, bool timedOut) const;
    };
    struct __declspec(empty_bases) PreallocatedWorkItem : winrt::Windows::System::Threading::Core::IPreallocatedWorkItem
    {
        PreallocatedWorkItem(std::nullptr_t) noexcept {}
        PreallocatedWorkItem(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::System::Threading::Core::IPreallocatedWorkItem(ptr, take_ownership_from_abi) {}
        explicit PreallocatedWorkItem(winrt::Windows::System::Threading::WorkItemHandler const& handler);
        PreallocatedWorkItem(winrt::Windows::System::Threading::WorkItemHandler const& handler, winrt::Windows::System::Threading::WorkItemPriority const& priority);
        PreallocatedWorkItem(winrt::Windows::System::Threading::WorkItemHandler const& handler, winrt::Windows::System::Threading::WorkItemPriority const& priority, winrt::Windows::System::Threading::WorkItemOptions const& options);
        PreallocatedWorkItem(PreallocatedWorkItem const&) noexcept = default;
        PreallocatedWorkItem(PreallocatedWorkItem&&) noexcept = default;
        PreallocatedWorkItem& operator=(PreallocatedWorkItem const&) & noexcept = default;
        PreallocatedWorkItem& operator=(PreallocatedWorkItem&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SignalNotifier : winrt::Windows::System::Threading::Core::ISignalNotifier
    {
        SignalNotifier(std::nullptr_t) noexcept {}
        SignalNotifier(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::System::Threading::Core::ISignalNotifier(ptr, take_ownership_from_abi) {}
        SignalNotifier(SignalNotifier const&) noexcept = default;
        SignalNotifier(SignalNotifier&&) noexcept = default;
        SignalNotifier& operator=(SignalNotifier const&) & noexcept = default;
        SignalNotifier& operator=(SignalNotifier&&) & noexcept = default;
        static auto AttachToEvent(param::hstring const& name, winrt::Windows::System::Threading::Core::SignalHandler const& handler);
        static auto AttachToEvent(param::hstring const& name, winrt::Windows::System::Threading::Core::SignalHandler const& handler, winrt::Windows::Foundation::TimeSpan const& timeout);
        static auto AttachToSemaphore(param::hstring const& name, winrt::Windows::System::Threading::Core::SignalHandler const& handler);
        static auto AttachToSemaphore(param::hstring const& name, winrt::Windows::System::Threading::Core::SignalHandler const& handler, winrt::Windows::Foundation::TimeSpan const& timeout);
    };
}
#endif