#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class SubSample : public ::android::Parcelable {
public:
  int32_t numBytesOfClearData = 0;
  int32_t numBytesOfEncryptedData = 0;
  inline bool operator!=(const SubSample& rhs) const {
    return std::tie(numBytesOfClearData, numBytesOfEncryptedData) != std::tie(rhs.numBytesOfClearData, rhs.numBytesOfEncryptedData);
  }
  inline bool operator<(const SubSample& rhs) const {
    return std::tie(numBytesOfClearData, numBytesOfEncryptedData) < std::tie(rhs.numBytesOfClearData, rhs.numBytesOfEncryptedData);
  }
  inline bool operator<=(const SubSample& rhs) const {
    return std::tie(numBytesOfClearData, numBytesOfEncryptedData) <= std::tie(rhs.numBytesOfClearData, rhs.numBytesOfEncryptedData);
  }
  inline bool operator==(const SubSample& rhs) const {
    return std::tie(numBytesOfClearData, numBytesOfEncryptedData) == std::tie(rhs.numBytesOfClearData, rhs.numBytesOfEncryptedData);
  }
  inline bool operator>(const SubSample& rhs) const {
    return std::tie(numBytesOfClearData, numBytesOfEncryptedData) > std::tie(rhs.numBytesOfClearData, rhs.numBytesOfEncryptedData);
  }
  inline bool operator>=(const SubSample& rhs) const {
    return std::tie(numBytesOfClearData, numBytesOfEncryptedData) >= std::tie(rhs.numBytesOfClearData, rhs.numBytesOfEncryptedData);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.SubSample");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "SubSample{";
    os << "numBytesOfClearData: " << ::android::internal::ToString(numBytesOfClearData);
    os << ", numBytesOfEncryptedData: " << ::android::internal::ToString(numBytesOfEncryptedData);
    os << "}";
    return os.str();
  }
};  // class SubSample
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
