#pragma once

#include <android/binder_to_string.h>
#include <array>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class Uuid : public ::android::Parcelable {
public:
  std::array<uint8_t, 16> uuid = {{}};
  inline bool operator!=(const Uuid& rhs) const {
    return std::tie(uuid) != std::tie(rhs.uuid);
  }
  inline bool operator<(const Uuid& rhs) const {
    return std::tie(uuid) < std::tie(rhs.uuid);
  }
  inline bool operator<=(const Uuid& rhs) const {
    return std::tie(uuid) <= std::tie(rhs.uuid);
  }
  inline bool operator==(const Uuid& rhs) const {
    return std::tie(uuid) == std::tie(rhs.uuid);
  }
  inline bool operator>(const Uuid& rhs) const {
    return std::tie(uuid) > std::tie(rhs.uuid);
  }
  inline bool operator>=(const Uuid& rhs) const {
    return std::tie(uuid) >= std::tie(rhs.uuid);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.Uuid");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Uuid{";
    os << "uuid: " << ::android::internal::ToString(uuid);
    os << "}";
    return os.str();
  }
};  // class Uuid
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
