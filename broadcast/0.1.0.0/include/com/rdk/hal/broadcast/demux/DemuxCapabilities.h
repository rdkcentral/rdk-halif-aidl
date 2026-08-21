#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/demux/DemuxCapabilities.h>
#include <com/rdk/hal/broadcast/demux/FilterType.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class DemuxCapabilities : public ::android::Parcelable {
public:
  class FilterCapability : public ::android::Parcelable {
  public:
    ::com::rdk::hal::broadcast::demux::FilterType filterType = ::com::rdk::hal::broadcast::demux::FilterType(0);
    int32_t maxInstances = 0;
    inline bool operator!=(const FilterCapability& rhs) const {
      return std::tie(filterType, maxInstances) != std::tie(rhs.filterType, rhs.maxInstances);
    }
    inline bool operator<(const FilterCapability& rhs) const {
      return std::tie(filterType, maxInstances) < std::tie(rhs.filterType, rhs.maxInstances);
    }
    inline bool operator<=(const FilterCapability& rhs) const {
      return std::tie(filterType, maxInstances) <= std::tie(rhs.filterType, rhs.maxInstances);
    }
    inline bool operator==(const FilterCapability& rhs) const {
      return std::tie(filterType, maxInstances) == std::tie(rhs.filterType, rhs.maxInstances);
    }
    inline bool operator>(const FilterCapability& rhs) const {
      return std::tie(filterType, maxInstances) > std::tie(rhs.filterType, rhs.maxInstances);
    }
    inline bool operator>=(const FilterCapability& rhs) const {
      return std::tie(filterType, maxInstances) >= std::tie(rhs.filterType, rhs.maxInstances);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.demux.DemuxCapabilities.FilterCapability");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "FilterCapability{";
      os << "filterType: " << ::android::internal::ToString(filterType);
      os << ", maxInstances: " << ::android::internal::ToString(maxInstances);
      os << "}";
      return os.str();
    }
  };  // class FilterCapability
  bool acceptsDataFromSoftware = false;
  bool acceptsDataFromHardware = false;
  bool canHoldBackData = false;
  ::std::vector<::com::rdk::hal::broadcast::demux::DemuxCapabilities::FilterCapability> supportedFilters;
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const DemuxCapabilities& rhs) const {
    return std::tie(acceptsDataFromSoftware, acceptsDataFromHardware, canHoldBackData, supportedFilters, extension) != std::tie(rhs.acceptsDataFromSoftware, rhs.acceptsDataFromHardware, rhs.canHoldBackData, rhs.supportedFilters, rhs.extension);
  }
  inline bool operator<(const DemuxCapabilities& rhs) const {
    return std::tie(acceptsDataFromSoftware, acceptsDataFromHardware, canHoldBackData, supportedFilters, extension) < std::tie(rhs.acceptsDataFromSoftware, rhs.acceptsDataFromHardware, rhs.canHoldBackData, rhs.supportedFilters, rhs.extension);
  }
  inline bool operator<=(const DemuxCapabilities& rhs) const {
    return std::tie(acceptsDataFromSoftware, acceptsDataFromHardware, canHoldBackData, supportedFilters, extension) <= std::tie(rhs.acceptsDataFromSoftware, rhs.acceptsDataFromHardware, rhs.canHoldBackData, rhs.supportedFilters, rhs.extension);
  }
  inline bool operator==(const DemuxCapabilities& rhs) const {
    return std::tie(acceptsDataFromSoftware, acceptsDataFromHardware, canHoldBackData, supportedFilters, extension) == std::tie(rhs.acceptsDataFromSoftware, rhs.acceptsDataFromHardware, rhs.canHoldBackData, rhs.supportedFilters, rhs.extension);
  }
  inline bool operator>(const DemuxCapabilities& rhs) const {
    return std::tie(acceptsDataFromSoftware, acceptsDataFromHardware, canHoldBackData, supportedFilters, extension) > std::tie(rhs.acceptsDataFromSoftware, rhs.acceptsDataFromHardware, rhs.canHoldBackData, rhs.supportedFilters, rhs.extension);
  }
  inline bool operator>=(const DemuxCapabilities& rhs) const {
    return std::tie(acceptsDataFromSoftware, acceptsDataFromHardware, canHoldBackData, supportedFilters, extension) >= std::tie(rhs.acceptsDataFromSoftware, rhs.acceptsDataFromHardware, rhs.canHoldBackData, rhs.supportedFilters, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.demux.DemuxCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DemuxCapabilities{";
    os << "acceptsDataFromSoftware: " << ::android::internal::ToString(acceptsDataFromSoftware);
    os << ", acceptsDataFromHardware: " << ::android::internal::ToString(acceptsDataFromHardware);
    os << ", canHoldBackData: " << ::android::internal::ToString(canHoldBackData);
    os << ", supportedFilters: " << ::android::internal::ToString(supportedFilters);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class DemuxCapabilities
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
