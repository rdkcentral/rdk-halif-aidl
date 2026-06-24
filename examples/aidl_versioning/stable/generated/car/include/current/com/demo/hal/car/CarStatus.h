#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/demo/hal/common/FuelStatus.h>
#include <com/demo/hal/common/SpeedStatus.h>
#include <com/demo/hal/common/TireStatus.h>
#include <com/demo/hal/dashboard/DashboardInfo.h>
#include <com/demo/hal/dashboard/DashboardWarning.h>
#include <com/demo/hal/vehicle/VehicleStatus.h>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace demo {
namespace hal {
namespace car {
class CarStatus : public ::android::Parcelable {
public:
  ::com::demo::hal::vehicle::VehicleStatus vehicleStatus;
  ::std::optional<::com::demo::hal::common::FuelStatus> fuelStatus;
  ::std::optional<::com::demo::hal::common::SpeedStatus> speedStatus;
  ::std::optional<::std::vector<::std::optional<::com::demo::hal::common::TireStatus>>> tireStatuses;
  ::std::optional<::com::demo::hal::dashboard::DashboardInfo> dashboardInfo;
  ::std::optional<::std::vector<::std::optional<::com::demo::hal::dashboard::DashboardWarning>>> activeWarnings;
  inline bool operator!=(const CarStatus& rhs) const {
    return std::tie(vehicleStatus, fuelStatus, speedStatus, tireStatuses, dashboardInfo, activeWarnings) != std::tie(rhs.vehicleStatus, rhs.fuelStatus, rhs.speedStatus, rhs.tireStatuses, rhs.dashboardInfo, rhs.activeWarnings);
  }
  inline bool operator<(const CarStatus& rhs) const {
    return std::tie(vehicleStatus, fuelStatus, speedStatus, tireStatuses, dashboardInfo, activeWarnings) < std::tie(rhs.vehicleStatus, rhs.fuelStatus, rhs.speedStatus, rhs.tireStatuses, rhs.dashboardInfo, rhs.activeWarnings);
  }
  inline bool operator<=(const CarStatus& rhs) const {
    return std::tie(vehicleStatus, fuelStatus, speedStatus, tireStatuses, dashboardInfo, activeWarnings) <= std::tie(rhs.vehicleStatus, rhs.fuelStatus, rhs.speedStatus, rhs.tireStatuses, rhs.dashboardInfo, rhs.activeWarnings);
  }
  inline bool operator==(const CarStatus& rhs) const {
    return std::tie(vehicleStatus, fuelStatus, speedStatus, tireStatuses, dashboardInfo, activeWarnings) == std::tie(rhs.vehicleStatus, rhs.fuelStatus, rhs.speedStatus, rhs.tireStatuses, rhs.dashboardInfo, rhs.activeWarnings);
  }
  inline bool operator>(const CarStatus& rhs) const {
    return std::tie(vehicleStatus, fuelStatus, speedStatus, tireStatuses, dashboardInfo, activeWarnings) > std::tie(rhs.vehicleStatus, rhs.fuelStatus, rhs.speedStatus, rhs.tireStatuses, rhs.dashboardInfo, rhs.activeWarnings);
  }
  inline bool operator>=(const CarStatus& rhs) const {
    return std::tie(vehicleStatus, fuelStatus, speedStatus, tireStatuses, dashboardInfo, activeWarnings) >= std::tie(rhs.vehicleStatus, rhs.fuelStatus, rhs.speedStatus, rhs.tireStatuses, rhs.dashboardInfo, rhs.activeWarnings);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.demo.hal.car.CarStatus");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "CarStatus{";
    os << "vehicleStatus: " << ::android::internal::ToString(vehicleStatus);
    os << ", fuelStatus: " << ::android::internal::ToString(fuelStatus);
    os << ", speedStatus: " << ::android::internal::ToString(speedStatus);
    os << ", tireStatuses: " << ::android::internal::ToString(tireStatuses);
    os << ", dashboardInfo: " << ::android::internal::ToString(dashboardInfo);
    os << ", activeWarnings: " << ::android::internal::ToString(activeWarnings);
    os << "}";
    return os.str();
  }
};  // class CarStatus
}  // namespace car
}  // namespace hal
}  // namespace demo
}  // namespace com
