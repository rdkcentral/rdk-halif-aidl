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
namespace avbuffer {
class Pool : public ::android::Parcelable {
public:
  int8_t handle = 0;
  inline bool operator!=(const Pool& rhs) const {
    return std::tie(handle) != std::tie(rhs.handle);
  }
  inline bool operator<(const Pool& rhs) const {
    return std::tie(handle) < std::tie(rhs.handle);
  }
  inline bool operator<=(const Pool& rhs) const {
    return std::tie(handle) <= std::tie(rhs.handle);
  }
  inline bool operator==(const Pool& rhs) const {
    return std::tie(handle) == std::tie(rhs.handle);
  }
  inline bool operator>(const Pool& rhs) const {
    return std::tie(handle) > std::tie(rhs.handle);
  }
  inline bool operator>=(const Pool& rhs) const {
    return std::tie(handle) >= std::tie(rhs.handle);
  }

  enum : int8_t { INVALID_POOL = -1 };
  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.avbuffer.Pool");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Pool{";
    os << "handle: " << ::android::internal::ToString(handle);
    os << "}";
    return os.str();
  }
};  // class Pool
}  // namespace avbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
