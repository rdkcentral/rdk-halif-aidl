#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class KeyValue : public ::android::Parcelable {
public:
  ::android::String16 key;
  ::android::String16 value;
  inline bool operator!=(const KeyValue& rhs) const {
    return std::tie(key, value) != std::tie(rhs.key, rhs.value);
  }
  inline bool operator<(const KeyValue& rhs) const {
    return std::tie(key, value) < std::tie(rhs.key, rhs.value);
  }
  inline bool operator<=(const KeyValue& rhs) const {
    return std::tie(key, value) <= std::tie(rhs.key, rhs.value);
  }
  inline bool operator==(const KeyValue& rhs) const {
    return std::tie(key, value) == std::tie(rhs.key, rhs.value);
  }
  inline bool operator>(const KeyValue& rhs) const {
    return std::tie(key, value) > std::tie(rhs.key, rhs.value);
  }
  inline bool operator>=(const KeyValue& rhs) const {
    return std::tie(key, value) >= std::tie(rhs.key, rhs.value);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.KeyValue");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "KeyValue{";
    os << "key: " << ::android::internal::ToString(key);
    os << ", value: " << ::android::internal::ToString(value);
    os << "}";
    return os.str();
  }
};  // class KeyValue
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
