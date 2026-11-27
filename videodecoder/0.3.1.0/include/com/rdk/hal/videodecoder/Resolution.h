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
namespace videodecoder {
// @aidl-doc
/**
 *  @brief     Two-dimensional pixel resolution.
 *
 *  Carries a `{width, height}` pair in pixels. Used wherever a structured
 *  resolution is required in place of two loose `int` parameters — for
 *  example, batched stream-configuration parcelables and capability
 *  descriptors.
 *
 *  Both fields are integer pixel counts and MUST be > 0 when the
 *  resolution is used as a hint or target. Container types that allow
 *  "unknown" must document that convention on the carrying field.
 *
 *  @author    Gerald Weatherup
 */
class Resolution : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Frame width in pixels. Must be > 0. */
  int32_t width = 0;
  // @aidl-doc
  /** Frame height in pixels. Must be > 0. */
  int32_t height = 0;
  inline bool operator!=(const Resolution& rhs) const {
    return std::tie(width, height) != std::tie(rhs.width, rhs.height);
  }
  inline bool operator<(const Resolution& rhs) const {
    return std::tie(width, height) < std::tie(rhs.width, rhs.height);
  }
  inline bool operator<=(const Resolution& rhs) const {
    return std::tie(width, height) <= std::tie(rhs.width, rhs.height);
  }
  inline bool operator==(const Resolution& rhs) const {
    return std::tie(width, height) == std::tie(rhs.width, rhs.height);
  }
  inline bool operator>(const Resolution& rhs) const {
    return std::tie(width, height) > std::tie(rhs.width, rhs.height);
  }
  inline bool operator>=(const Resolution& rhs) const {
    return std::tie(width, height) >= std::tie(rhs.width, rhs.height);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videodecoder.Resolution");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Resolution{";
    os << "width: " << ::android::internal::ToString(width);
    os << ", height: " << ::android::internal::ToString(height);
    os << "}";
    return os.str();
  }
};  // class Resolution
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
