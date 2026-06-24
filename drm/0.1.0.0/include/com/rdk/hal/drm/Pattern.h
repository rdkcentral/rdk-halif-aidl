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
class Pattern : public ::android::Parcelable {
public:
  int32_t encryptBlocks = 0;
  int32_t skipBlocks = 0;
  inline bool operator!=(const Pattern& rhs) const {
    return std::tie(encryptBlocks, skipBlocks) != std::tie(rhs.encryptBlocks, rhs.skipBlocks);
  }
  inline bool operator<(const Pattern& rhs) const {
    return std::tie(encryptBlocks, skipBlocks) < std::tie(rhs.encryptBlocks, rhs.skipBlocks);
  }
  inline bool operator<=(const Pattern& rhs) const {
    return std::tie(encryptBlocks, skipBlocks) <= std::tie(rhs.encryptBlocks, rhs.skipBlocks);
  }
  inline bool operator==(const Pattern& rhs) const {
    return std::tie(encryptBlocks, skipBlocks) == std::tie(rhs.encryptBlocks, rhs.skipBlocks);
  }
  inline bool operator>(const Pattern& rhs) const {
    return std::tie(encryptBlocks, skipBlocks) > std::tie(rhs.encryptBlocks, rhs.skipBlocks);
  }
  inline bool operator>=(const Pattern& rhs) const {
    return std::tie(encryptBlocks, skipBlocks) >= std::tie(rhs.encryptBlocks, rhs.skipBlocks);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.Pattern");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Pattern{";
    os << "encryptBlocks: " << ::android::internal::ToString(encryptBlocks);
    os << ", skipBlocks: " << ::android::internal::ToString(skipBlocks);
    os << "}";
    return os.str();
  }
};  // class Pattern
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
