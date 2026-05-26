#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/drm/KeyStatusType.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class KeyStatus : public ::android::Parcelable {
public:
  ::std::vector<uint8_t> keyId;
  ::com::rdk::hal::drm::KeyStatusType type = ::com::rdk::hal::drm::KeyStatusType(0);
  inline bool operator!=(const KeyStatus& rhs) const {
    return std::tie(keyId, type) != std::tie(rhs.keyId, rhs.type);
  }
  inline bool operator<(const KeyStatus& rhs) const {
    return std::tie(keyId, type) < std::tie(rhs.keyId, rhs.type);
  }
  inline bool operator<=(const KeyStatus& rhs) const {
    return std::tie(keyId, type) <= std::tie(rhs.keyId, rhs.type);
  }
  inline bool operator==(const KeyStatus& rhs) const {
    return std::tie(keyId, type) == std::tie(rhs.keyId, rhs.type);
  }
  inline bool operator>(const KeyStatus& rhs) const {
    return std::tie(keyId, type) > std::tie(rhs.keyId, rhs.type);
  }
  inline bool operator>=(const KeyStatus& rhs) const {
    return std::tie(keyId, type) >= std::tie(rhs.keyId, rhs.type);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.KeyStatus");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "KeyStatus{";
    os << "keyId: " << ::android::internal::ToString(keyId);
    os << ", type: " << ::android::internal::ToString(type);
    os << "}";
    return os.str();
  }
};  // class KeyStatus
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
