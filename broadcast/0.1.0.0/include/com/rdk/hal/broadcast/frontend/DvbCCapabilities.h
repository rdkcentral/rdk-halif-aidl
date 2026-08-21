#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/Bandwidth.h>
#include <com/rdk/hal/broadcast/frontend/DvbCAnnex.h>
#include <com/rdk/hal/broadcast/frontend/Modulation.h>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class DvbCCapabilities : public ::android::Parcelable {
public:
  ::std::vector<::com::rdk::hal::broadcast::frontend::Bandwidth> bandwidths;
  ::std::vector<::com::rdk::hal::broadcast::frontend::Modulation> modulations;
  ::std::vector<::com::rdk::hal::broadcast::frontend::DvbCAnnex> dvbCAnnexes;
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const DvbCCapabilities& rhs) const {
    return std::tie(bandwidths, modulations, dvbCAnnexes, extension) != std::tie(rhs.bandwidths, rhs.modulations, rhs.dvbCAnnexes, rhs.extension);
  }
  inline bool operator<(const DvbCCapabilities& rhs) const {
    return std::tie(bandwidths, modulations, dvbCAnnexes, extension) < std::tie(rhs.bandwidths, rhs.modulations, rhs.dvbCAnnexes, rhs.extension);
  }
  inline bool operator<=(const DvbCCapabilities& rhs) const {
    return std::tie(bandwidths, modulations, dvbCAnnexes, extension) <= std::tie(rhs.bandwidths, rhs.modulations, rhs.dvbCAnnexes, rhs.extension);
  }
  inline bool operator==(const DvbCCapabilities& rhs) const {
    return std::tie(bandwidths, modulations, dvbCAnnexes, extension) == std::tie(rhs.bandwidths, rhs.modulations, rhs.dvbCAnnexes, rhs.extension);
  }
  inline bool operator>(const DvbCCapabilities& rhs) const {
    return std::tie(bandwidths, modulations, dvbCAnnexes, extension) > std::tie(rhs.bandwidths, rhs.modulations, rhs.dvbCAnnexes, rhs.extension);
  }
  inline bool operator>=(const DvbCCapabilities& rhs) const {
    return std::tie(bandwidths, modulations, dvbCAnnexes, extension) >= std::tie(rhs.bandwidths, rhs.modulations, rhs.dvbCAnnexes, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.DvbCCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DvbCCapabilities{";
    os << "bandwidths: " << ::android::internal::ToString(bandwidths);
    os << ", modulations: " << ::android::internal::ToString(modulations);
    os << ", dvbCAnnexes: " << ::android::internal::ToString(dvbCAnnexes);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class DvbCCapabilities
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
