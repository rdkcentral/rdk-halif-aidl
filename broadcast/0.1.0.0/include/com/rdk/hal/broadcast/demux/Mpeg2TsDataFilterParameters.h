#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class Mpeg2TsDataFilterParameters : public ::android::Parcelable {
public:
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const Mpeg2TsDataFilterParameters& rhs) const {
    return std::tie(extension) != std::tie(rhs.extension);
  }
  inline bool operator<(const Mpeg2TsDataFilterParameters& rhs) const {
    return std::tie(extension) < std::tie(rhs.extension);
  }
  inline bool operator<=(const Mpeg2TsDataFilterParameters& rhs) const {
    return std::tie(extension) <= std::tie(rhs.extension);
  }
  inline bool operator==(const Mpeg2TsDataFilterParameters& rhs) const {
    return std::tie(extension) == std::tie(rhs.extension);
  }
  inline bool operator>(const Mpeg2TsDataFilterParameters& rhs) const {
    return std::tie(extension) > std::tie(rhs.extension);
  }
  inline bool operator>=(const Mpeg2TsDataFilterParameters& rhs) const {
    return std::tie(extension) >= std::tie(rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.demux.Mpeg2TsDataFilterParameters");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Mpeg2TsDataFilterParameters{";
    os << "extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class Mpeg2TsDataFilterParameters
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
