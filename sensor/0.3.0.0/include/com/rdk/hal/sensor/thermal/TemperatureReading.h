#pragma once
// @aidl-doc
/**
 * @file TemperatureReading.h
 * @brief Optional temperature telemetry record.
 *
 * @details Implementations may return zero readings if telemetry is unsupported.
 */

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cstdint>
#include <string>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace thermal {
class TemperatureReading : public ::android::Parcelable {
public:
  // @aidl-doc
  /** @brief Human-readable identifier (e.g., "SoC Die", "DDR", "PMIC"). */
  ::std::string sensorName;
  // @aidl-doc
  /** @brief Optional location/domain hint (e.g., "CPU", "GPU", "Board"). */
  ::std::string location;
  // @aidl-doc
  /** @brief Temperature in degrees Celsius. */
  double temperatureCelsius = 0.000000;
  // @aidl-doc
  /** @brief Monotonic timestamp (ms) when this reading was sampled. */
  int64_t timestampMonotonicMs = 0L;
  // @aidl-doc
  /**
   * @brief Optional vendor reason/diagnostic code.
   *         Used for telemetry or diagnostics.
   */
  int32_t vendorCode = 0;
  // @aidl-doc
  /**
   * @brief Optional vendor info string (domain, details, etc.).
   *         May be null or empty, and used for telemetry or diagnostics.
   */
  ::std::string vendorInfo;
  inline bool operator!=(const TemperatureReading& rhs) const {
    return std::tie(sensorName, location, temperatureCelsius, timestampMonotonicMs, vendorCode, vendorInfo) != std::tie(rhs.sensorName, rhs.location, rhs.temperatureCelsius, rhs.timestampMonotonicMs, rhs.vendorCode, rhs.vendorInfo);
  }
  inline bool operator<(const TemperatureReading& rhs) const {
    return std::tie(sensorName, location, temperatureCelsius, timestampMonotonicMs, vendorCode, vendorInfo) < std::tie(rhs.sensorName, rhs.location, rhs.temperatureCelsius, rhs.timestampMonotonicMs, rhs.vendorCode, rhs.vendorInfo);
  }
  inline bool operator<=(const TemperatureReading& rhs) const {
    return std::tie(sensorName, location, temperatureCelsius, timestampMonotonicMs, vendorCode, vendorInfo) <= std::tie(rhs.sensorName, rhs.location, rhs.temperatureCelsius, rhs.timestampMonotonicMs, rhs.vendorCode, rhs.vendorInfo);
  }
  inline bool operator==(const TemperatureReading& rhs) const {
    return std::tie(sensorName, location, temperatureCelsius, timestampMonotonicMs, vendorCode, vendorInfo) == std::tie(rhs.sensorName, rhs.location, rhs.temperatureCelsius, rhs.timestampMonotonicMs, rhs.vendorCode, rhs.vendorInfo);
  }
  inline bool operator>(const TemperatureReading& rhs) const {
    return std::tie(sensorName, location, temperatureCelsius, timestampMonotonicMs, vendorCode, vendorInfo) > std::tie(rhs.sensorName, rhs.location, rhs.temperatureCelsius, rhs.timestampMonotonicMs, rhs.vendorCode, rhs.vendorInfo);
  }
  inline bool operator>=(const TemperatureReading& rhs) const {
    return std::tie(sensorName, location, temperatureCelsius, timestampMonotonicMs, vendorCode, vendorInfo) >= std::tie(rhs.sensorName, rhs.location, rhs.temperatureCelsius, rhs.timestampMonotonicMs, rhs.vendorCode, rhs.vendorInfo);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.sensor.thermal.TemperatureReading");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "TemperatureReading{";
    os << "sensorName: " << ::android::internal::ToString(sensorName);
    os << ", location: " << ::android::internal::ToString(location);
    os << ", temperatureCelsius: " << ::android::internal::ToString(temperatureCelsius);
    os << ", timestampMonotonicMs: " << ::android::internal::ToString(timestampMonotonicMs);
    os << ", vendorCode: " << ::android::internal::ToString(vendorCode);
    os << ", vendorInfo: " << ::android::internal::ToString(vendorInfo);
    os << "}";
    return os.str();
  }
};  // class TemperatureReading
}  // namespace thermal
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
