#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/cryptoengine/Algorithm.h>
#include <com/rdk/hal/cryptoengine/BlockMode.h>
#include <com/rdk/hal/cryptoengine/Digest.h>
#include <com/rdk/hal/cryptoengine/SecurityLevel.h>
#include <cstdint>
#include <string>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
class EngineCapabilities : public ::android::Parcelable {
public:
  ::std::string halVersion;
  ::com::rdk::hal::cryptoengine::SecurityLevel securityLevel = ::com::rdk::hal::cryptoengine::SecurityLevel::SOFTWARE;
  ::std::vector<::com::rdk::hal::cryptoengine::Algorithm> algorithms = {};
  ::std::vector<::com::rdk::hal::cryptoengine::BlockMode> blockModes = {};
  ::std::vector<::com::rdk::hal::cryptoengine::Digest> digests = {};
  ::std::vector<int32_t> keySizes = {};
  int32_t maxConcurrentOperations = 0;
  bool hardwareAccelerated = false;
  inline bool operator!=(const EngineCapabilities& rhs) const {
    return std::tie(halVersion, securityLevel, algorithms, blockModes, digests, keySizes, maxConcurrentOperations, hardwareAccelerated) != std::tie(rhs.halVersion, rhs.securityLevel, rhs.algorithms, rhs.blockModes, rhs.digests, rhs.keySizes, rhs.maxConcurrentOperations, rhs.hardwareAccelerated);
  }
  inline bool operator<(const EngineCapabilities& rhs) const {
    return std::tie(halVersion, securityLevel, algorithms, blockModes, digests, keySizes, maxConcurrentOperations, hardwareAccelerated) < std::tie(rhs.halVersion, rhs.securityLevel, rhs.algorithms, rhs.blockModes, rhs.digests, rhs.keySizes, rhs.maxConcurrentOperations, rhs.hardwareAccelerated);
  }
  inline bool operator<=(const EngineCapabilities& rhs) const {
    return std::tie(halVersion, securityLevel, algorithms, blockModes, digests, keySizes, maxConcurrentOperations, hardwareAccelerated) <= std::tie(rhs.halVersion, rhs.securityLevel, rhs.algorithms, rhs.blockModes, rhs.digests, rhs.keySizes, rhs.maxConcurrentOperations, rhs.hardwareAccelerated);
  }
  inline bool operator==(const EngineCapabilities& rhs) const {
    return std::tie(halVersion, securityLevel, algorithms, blockModes, digests, keySizes, maxConcurrentOperations, hardwareAccelerated) == std::tie(rhs.halVersion, rhs.securityLevel, rhs.algorithms, rhs.blockModes, rhs.digests, rhs.keySizes, rhs.maxConcurrentOperations, rhs.hardwareAccelerated);
  }
  inline bool operator>(const EngineCapabilities& rhs) const {
    return std::tie(halVersion, securityLevel, algorithms, blockModes, digests, keySizes, maxConcurrentOperations, hardwareAccelerated) > std::tie(rhs.halVersion, rhs.securityLevel, rhs.algorithms, rhs.blockModes, rhs.digests, rhs.keySizes, rhs.maxConcurrentOperations, rhs.hardwareAccelerated);
  }
  inline bool operator>=(const EngineCapabilities& rhs) const {
    return std::tie(halVersion, securityLevel, algorithms, blockModes, digests, keySizes, maxConcurrentOperations, hardwareAccelerated) >= std::tie(rhs.halVersion, rhs.securityLevel, rhs.algorithms, rhs.blockModes, rhs.digests, rhs.keySizes, rhs.maxConcurrentOperations, rhs.hardwareAccelerated);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.cryptoengine.EngineCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "EngineCapabilities{";
    os << "halVersion: " << ::android::internal::ToString(halVersion);
    os << ", securityLevel: " << ::android::internal::ToString(securityLevel);
    os << ", algorithms: " << ::android::internal::ToString(algorithms);
    os << ", blockModes: " << ::android::internal::ToString(blockModes);
    os << ", digests: " << ::android::internal::ToString(digests);
    os << ", keySizes: " << ::android::internal::ToString(keySizes);
    os << ", maxConcurrentOperations: " << ::android::internal::ToString(maxConcurrentOperations);
    os << ", hardwareAccelerated: " << ::android::internal::ToString(hardwareAccelerated);
    os << "}";
    return os.str();
  }
};  // class EngineCapabilities
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
