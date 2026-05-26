#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/deviceinfo/PropertyType.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace deviceinfo {
class Property : public ::android::Parcelable {
public:
  ::android::String16 key;
  ::com::rdk::hal::deviceinfo::PropertyType type = ::com::rdk::hal::deviceinfo::PropertyType(0);
  int32_t sizeInBytes = 0;
  bool zeroTerminated = false;
  inline bool operator!=(const Property& rhs) const {
    return std::tie(key, type, sizeInBytes, zeroTerminated) != std::tie(rhs.key, rhs.type, rhs.sizeInBytes, rhs.zeroTerminated);
  }
  inline bool operator<(const Property& rhs) const {
    return std::tie(key, type, sizeInBytes, zeroTerminated) < std::tie(rhs.key, rhs.type, rhs.sizeInBytes, rhs.zeroTerminated);
  }
  inline bool operator<=(const Property& rhs) const {
    return std::tie(key, type, sizeInBytes, zeroTerminated) <= std::tie(rhs.key, rhs.type, rhs.sizeInBytes, rhs.zeroTerminated);
  }
  inline bool operator==(const Property& rhs) const {
    return std::tie(key, type, sizeInBytes, zeroTerminated) == std::tie(rhs.key, rhs.type, rhs.sizeInBytes, rhs.zeroTerminated);
  }
  inline bool operator>(const Property& rhs) const {
    return std::tie(key, type, sizeInBytes, zeroTerminated) > std::tie(rhs.key, rhs.type, rhs.sizeInBytes, rhs.zeroTerminated);
  }
  inline bool operator>=(const Property& rhs) const {
    return std::tie(key, type, sizeInBytes, zeroTerminated) >= std::tie(rhs.key, rhs.type, rhs.sizeInBytes, rhs.zeroTerminated);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.deviceinfo.Property");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Property{";
    os << "key: " << ::android::internal::ToString(key);
    os << ", type: " << ::android::internal::ToString(type);
    os << ", sizeInBytes: " << ::android::internal::ToString(sizeInBytes);
    os << ", zeroTerminated: " << ::android::internal::ToString(zeroTerminated);
    os << "}";
    return os.str();
  }
};  // class Property
}  // namespace deviceinfo
}  // namespace hal
}  // namespace rdk
}  // namespace com
