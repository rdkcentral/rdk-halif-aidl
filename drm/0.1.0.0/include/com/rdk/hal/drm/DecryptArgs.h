#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/drm/Mode.h>
#include <com/rdk/hal/drm/Pattern.h>
#include <com/rdk/hal/drm/SubSample.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class DecryptArgs : public ::android::Parcelable {
public:
  bool secure = false;
  ::std::vector<uint8_t> keyId;
  ::std::vector<uint8_t> iv;
  ::com::rdk::hal::drm::Mode mode = ::com::rdk::hal::drm::Mode(0);
  ::com::rdk::hal::drm::Pattern pattern;
  ::std::vector<::com::rdk::hal::drm::SubSample> subSamples;
  int64_t sourceBufferHandle = 0L;
  int64_t destinationBufferHandle = 0L;
  inline bool operator!=(const DecryptArgs& rhs) const {
    return std::tie(secure, keyId, iv, mode, pattern, subSamples, sourceBufferHandle, destinationBufferHandle) != std::tie(rhs.secure, rhs.keyId, rhs.iv, rhs.mode, rhs.pattern, rhs.subSamples, rhs.sourceBufferHandle, rhs.destinationBufferHandle);
  }
  inline bool operator<(const DecryptArgs& rhs) const {
    return std::tie(secure, keyId, iv, mode, pattern, subSamples, sourceBufferHandle, destinationBufferHandle) < std::tie(rhs.secure, rhs.keyId, rhs.iv, rhs.mode, rhs.pattern, rhs.subSamples, rhs.sourceBufferHandle, rhs.destinationBufferHandle);
  }
  inline bool operator<=(const DecryptArgs& rhs) const {
    return std::tie(secure, keyId, iv, mode, pattern, subSamples, sourceBufferHandle, destinationBufferHandle) <= std::tie(rhs.secure, rhs.keyId, rhs.iv, rhs.mode, rhs.pattern, rhs.subSamples, rhs.sourceBufferHandle, rhs.destinationBufferHandle);
  }
  inline bool operator==(const DecryptArgs& rhs) const {
    return std::tie(secure, keyId, iv, mode, pattern, subSamples, sourceBufferHandle, destinationBufferHandle) == std::tie(rhs.secure, rhs.keyId, rhs.iv, rhs.mode, rhs.pattern, rhs.subSamples, rhs.sourceBufferHandle, rhs.destinationBufferHandle);
  }
  inline bool operator>(const DecryptArgs& rhs) const {
    return std::tie(secure, keyId, iv, mode, pattern, subSamples, sourceBufferHandle, destinationBufferHandle) > std::tie(rhs.secure, rhs.keyId, rhs.iv, rhs.mode, rhs.pattern, rhs.subSamples, rhs.sourceBufferHandle, rhs.destinationBufferHandle);
  }
  inline bool operator>=(const DecryptArgs& rhs) const {
    return std::tie(secure, keyId, iv, mode, pattern, subSamples, sourceBufferHandle, destinationBufferHandle) >= std::tie(rhs.secure, rhs.keyId, rhs.iv, rhs.mode, rhs.pattern, rhs.subSamples, rhs.sourceBufferHandle, rhs.destinationBufferHandle);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.DecryptArgs");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DecryptArgs{";
    os << "secure: " << ::android::internal::ToString(secure);
    os << ", keyId: " << ::android::internal::ToString(keyId);
    os << ", iv: " << ::android::internal::ToString(iv);
    os << ", mode: " << ::android::internal::ToString(mode);
    os << ", pattern: " << ::android::internal::ToString(pattern);
    os << ", subSamples: " << ::android::internal::ToString(subSamples);
    os << ", sourceBufferHandle: " << ::android::internal::ToString(sourceBufferHandle);
    os << ", destinationBufferHandle: " << ::android::internal::ToString(destinationBufferHandle);
    os << "}";
    return os.str();
  }
};  // class DecryptArgs
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
