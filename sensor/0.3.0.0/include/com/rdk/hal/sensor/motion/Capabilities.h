#pragma once
// @aidl-doc
/**
 * @file Capabilities.h
 * @brief Static properties describing a specific motion sensor instance.
 *
 * Values returned by this parcelable are immutable across the lifetime of the
 * process and must not change between calls to
 * {@link com.rdk.hal.sensor.motion.IMotionSensor#getCapabilities()}.
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
namespace motion {
class Capabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /** @brief Human-readable sensor name (e.g. "PIR-Front-1" or "Radar-SoC-0"). */
  ::std::string sensorName;
  // @aidl-doc
  /** @brief Minimum supported sensitivity (0 if sensitivity not supported). */
  int32_t minSensitivity = 0;
  // @aidl-doc
  /** @brief Maximum supported sensitivity (0 if sensitivity not supported). */
  int32_t maxSensitivity = 0;
  // @aidl-doc
  /**
   * @brief Indicates whether the sensor can autonomously detect events during deep sleep.
   *
   * If true, platform may support wake-from-motion without full SoC resume.
   */
  bool supportsDeepSleepAutonomy = false;
  inline bool operator!=(const Capabilities& rhs) const {
    return std::tie(sensorName, minSensitivity, maxSensitivity, supportsDeepSleepAutonomy) != std::tie(rhs.sensorName, rhs.minSensitivity, rhs.maxSensitivity, rhs.supportsDeepSleepAutonomy);
  }
  inline bool operator<(const Capabilities& rhs) const {
    return std::tie(sensorName, minSensitivity, maxSensitivity, supportsDeepSleepAutonomy) < std::tie(rhs.sensorName, rhs.minSensitivity, rhs.maxSensitivity, rhs.supportsDeepSleepAutonomy);
  }
  inline bool operator<=(const Capabilities& rhs) const {
    return std::tie(sensorName, minSensitivity, maxSensitivity, supportsDeepSleepAutonomy) <= std::tie(rhs.sensorName, rhs.minSensitivity, rhs.maxSensitivity, rhs.supportsDeepSleepAutonomy);
  }
  inline bool operator==(const Capabilities& rhs) const {
    return std::tie(sensorName, minSensitivity, maxSensitivity, supportsDeepSleepAutonomy) == std::tie(rhs.sensorName, rhs.minSensitivity, rhs.maxSensitivity, rhs.supportsDeepSleepAutonomy);
  }
  inline bool operator>(const Capabilities& rhs) const {
    return std::tie(sensorName, minSensitivity, maxSensitivity, supportsDeepSleepAutonomy) > std::tie(rhs.sensorName, rhs.minSensitivity, rhs.maxSensitivity, rhs.supportsDeepSleepAutonomy);
  }
  inline bool operator>=(const Capabilities& rhs) const {
    return std::tie(sensorName, minSensitivity, maxSensitivity, supportsDeepSleepAutonomy) >= std::tie(rhs.sensorName, rhs.minSensitivity, rhs.maxSensitivity, rhs.supportsDeepSleepAutonomy);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.sensor.motion.Capabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Capabilities{";
    os << "sensorName: " << ::android::internal::ToString(sensorName);
    os << ", minSensitivity: " << ::android::internal::ToString(minSensitivity);
    os << ", maxSensitivity: " << ::android::internal::ToString(maxSensitivity);
    os << ", supportsDeepSleepAutonomy: " << ::android::internal::ToString(supportsDeepSleepAutonomy);
    os << "}";
    return os.str();
  }
};  // class Capabilities
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
