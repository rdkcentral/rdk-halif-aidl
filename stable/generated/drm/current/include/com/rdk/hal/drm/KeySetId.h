#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class KeySetId : public ::android::Parcelable {
public:
  ::std::vector<uint8_t> keySetId;
  inline bool operator!=(const KeySetId& rhs) const {
    return std::tie(keySetId) != std::tie(rhs.keySetId);
  }
  inline bool operator<(const KeySetId& rhs) const {
    return std::tie(keySetId) < std::tie(rhs.keySetId);
  }
  inline bool operator<=(const KeySetId& rhs) const {
    return std::tie(keySetId) <= std::tie(rhs.keySetId);
  }
  inline bool operator==(const KeySetId& rhs) const {
    return std::tie(keySetId) == std::tie(rhs.keySetId);
  }
  inline bool operator>(const KeySetId& rhs) const {
    return std::tie(keySetId) > std::tie(rhs.keySetId);
  }
  inline bool operator>=(const KeySetId& rhs) const {
    return std::tie(keySetId) >= std::tie(rhs.keySetId);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.KeySetId");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "KeySetId{";
    os << "keySetId: " << ::android::internal::ToString(keySetId);
    os << "}";
    return os.str();
  }
};  // class KeySetId
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
