/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _RDK_HALCOMPAT_H_
#define _RDK_HALCOMPAT_H_

/**
 * @brief  Client-side interface compatibility helpers for RDK HAL AIDL
 *         services.
 *
 * `getInterfaceVersion()` reports the release version as a positional int
 * and behaves identically in every era. The era only changes the
 * COMPATIBILITY PREDICATE, and these helpers keep that internal: clients
 * call the same functions before and after a component adopts frozen AIDL
 * discipline, and never handle the encoding directly.
 *
 * Typical client:
 * @code
 *   using namespace com::rdk::hal;
 *
 *   auto service = halcompat::getService<bootreason::IBootReason>();
 *   if (!halcompat::isCompatible(service)) {
 *       // absent, unfrozen, or incompatible server
 *   }
 *   if (halcompat::atLeast(service, 0, 3)) {   // server >= 0.3.x.x
 *       // safe to use APIs added in 0.3.0.0
 *   }
 * @endcode
 */

#include <cstdint>
#include <string>
#include <binder/IServiceManager.h>
#include <binder/IInterface.h>
#include <utils/String16.h>

namespace com::rdk::hal::halcompat {

/**
 * Internal encoding machinery. Clients never handle version values —
 * everything public below takes a service proxy (and, for atLeast(),
 * the human-readable release fields of the feature being gated).
 */
namespace detail {

/**
 * Encodes a release version as the positional interface-version int.
 * e.g. version(0,1,0,0) == 1000, version(1,0,0,0) == 100000.
 */
constexpr int32_t version(int32_t era, int32_t major, int32_t minor = 0,
                          int32_t bugfix = 0)
{
    return era * 100000 + major * 1000 + minor * 10 + bugfix;
}

/** Field accessors over an encoded interface version. */
constexpr int32_t era(int32_t v)    { return v / 100000; }
constexpr int32_t major(int32_t v)  { return (v / 1000) % 100; }
constexpr int32_t minor(int32_t v)  { return (v / 10) % 100; }
constexpr int32_t bugfix(int32_t v) { return v % 10; }

/**
 * Compatibility predicate over encoded interface versions.
 *
 * Era >= 1 (frozen AIDL discipline, additive-only): ordering is
 * sufficient — the server is compatible if it is the same or newer.
 * Era 0: compatibility only holds within one major generation.
 *
 * A pre-freeze development server reports the generator default (1),
 * which never satisfies a released client — by design.
 */
constexpr bool isCompatible(int32_t clientVersion, int32_t serverVersion)
{
    return (era(serverVersion) >= 1 && era(clientVersion) >= 1)
        ? (serverVersion >= clientVersion)
        : (era(serverVersion) == era(clientVersion)
           && major(serverVersion) == major(clientVersion)
           && serverVersion >= clientVersion);
}

// Compile-time proofs of the encoding and the era rules — re-verified by
// every compile that includes this header.
static_assert(version(0, 1, 0, 0) == 1000,   "encode 0.1.0.0");
static_assert(version(0, 10, 0, 0) == 10000, "encode 0.10.0.0");
static_assert(version(1, 0, 0, 0) == 100000, "encode 1.0.0.0");
static_assert(era(100000) == 1 && major(3000) == 3
              && minor(3020) == 2 && bugfix(1001) == 1, "decode");
// Era 0: >= holds only within one major ("at least" means == on major).
static_assert(isCompatible(3000, 3000), "era0 exact");
static_assert(isCompatible(3000, 3020), "era0 newer minor, same major");
static_assert(!isCompatible(3000, 4000), "era0 cross-major rejected");
static_assert(!isCompatible(3000, 2000), "era0 older rejected");
// Era 1+: additive-only discipline makes plain ordering sufficient.
static_assert(isCompatible(100000, 101000), "era1 newer server");
static_assert(!isCompatible(101000, 100000), "era1 older server rejected");
// Cross-era and development servers never satisfy a released client.
static_assert(!isCompatible(3000, 100000), "era-0 gate vs era-1 server");
static_assert(!isCompatible(1000, 1), "unfrozen dev server rejected");

} // namespace detail

/**
 * Looks up interface I via the service manager using its published
 * `serviceName` and returns the typed proxy, or nullptr if absent.
 */
template <typename I>
inline android::sp<I> getService()
{
    return android::interface_cast<I>(
        android::defaultServiceManager()->checkService(
            android::String16(I::serviceName().c_str())));
}

/**
 * True when the connected server is frozen: it reports a real contract
 * hash rather than the pre-freeze "notfrozen" marker. A development
 * build makes no compatibility promise; production clients treat it as
 * a mismatch.
 */
template <typename I>
inline bool isFrozen(const android::sp<I>& service)
{
    return service != nullptr && service->getInterfaceHash() != "notfrozen";
}

/**
 * One-call compatibility check: the service exists, is frozen, and its
 * version satisfies this client's compiled-against I::VERSION under the
 * era rules. Set allowUnfrozen=true only on development images.
 */
template <typename I>
inline bool isCompatible(const android::sp<I>& service,
                         bool allowUnfrozen = false)
{
    if (service == nullptr) {
        return false;
    }
    if (!isFrozen(service)) {
        return allowUnfrozen;
    }
    return detail::isCompatible(I::VERSION, service->getInterfaceVersion());
}

/**
 * Feature gate: true when the connected server's version is at least the
 * given release version AND the server is era-compatible with it (an era-0
 * server from a different major does not satisfy the gate even if its
 * encoded value is numerically larger).
 */
template <typename I>
inline bool atLeast(const android::sp<I>& service, int32_t featureEra,
                    int32_t featureMajor, int32_t featureMinor = 0,
                    int32_t featureBugfix = 0)
{
    if (service == nullptr) {
        return false;
    }
    const int32_t needed = detail::version(featureEra, featureMajor,
                                           featureMinor, featureBugfix);
    return detail::isCompatible(needed, service->getInterfaceVersion());
}

} // namespace com::rdk::hal::halcompat

#endif // _RDK_HALCOMPAT_H_
