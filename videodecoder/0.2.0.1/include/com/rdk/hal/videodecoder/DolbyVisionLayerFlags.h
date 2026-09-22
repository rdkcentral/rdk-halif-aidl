#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
class DolbyVisionLayerFlags : public ::android::Parcelable {
public:
  bool blPresent = false;
  bool elPresent = false;
  inline bool operator!=(const DolbyVisionLayerFlags& rhs) const {
    return std::tie(blPresent, elPresent) != std::tie(rhs.blPresent, rhs.elPresent);
  }
  inline bool operator<(const DolbyVisionLayerFlags& rhs) const {
    return std::tie(blPresent, elPresent) < std::tie(rhs.blPresent, rhs.elPresent);
  }
  inline bool operator<=(const DolbyVisionLayerFlags& rhs) const {
    return std::tie(blPresent, elPresent) <= std::tie(rhs.blPresent, rhs.elPresent);
  }
  inline bool operator==(const DolbyVisionLayerFlags& rhs) const {
    return std::tie(blPresent, elPresent) == std::tie(rhs.blPresent, rhs.elPresent);
  }
  inline bool operator>(const DolbyVisionLayerFlags& rhs) const {
    return std::tie(blPresent, elPresent) > std::tie(rhs.blPresent, rhs.elPresent);
  }
  inline bool operator>=(const DolbyVisionLayerFlags& rhs) const {
    return std::tie(blPresent, elPresent) >= std::tie(rhs.blPresent, rhs.elPresent);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videodecoder.DolbyVisionLayerFlags");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DolbyVisionLayerFlags{";
    os << "blPresent: " << ::android::internal::ToString(blPresent);
    os << ", elPresent: " << ::android::internal::ToString(elPresent);
    os << "}";
    return os.str();
  }
};  // class DolbyVisionLayerFlags
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
