#pragma once
// @aidl-doc
/**
 * @file StartConfig.h
 * @brief Configuration parameters for starting a motion sensor session.
 *
 * Passed to {@link IMotionSensorController#start(StartConfig)} and
 * retrievable via {@link IMotionSensorController#getStartConfig()}.
 */

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/sensor/motion/OperationalMode.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
class StartConfig : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * @brief Operational mode — determines which event type the sensor reports.
   *
   * MOTION: fire onEvent when motion is detected.
   * NO_MOTION: fire onEvent after noMotionSeconds of inactivity.
   */
  ::com::rdk::hal::sensor::motion::OperationalMode operationalMode = ::com::rdk::hal::sensor::motion::OperationalMode(0);
  // @aidl-doc
  /**
   * @brief Contiguous seconds without motion before a NO_MOTION event fires.
   *
   * Only meaningful when operationalMode is NO_MOTION. Use 0 to disable.
   *
   * Valid range: 0 (disabled), or 1–86400 (1 second to 24 hours).
   * Values outside this range cause start() to throw EX_ILLEGAL_ARGUMENT.
   */
  int32_t noMotionSeconds = 0;
  // @aidl-doc
  /**
   * @brief Delay in seconds before the sensor becomes active after start().
   *
   * Allows the caller to vacate the detection area before monitoring begins.
   * Use 0 for immediate activation.
   */
  int32_t activeStartSeconds = 0;
  // @aidl-doc
  /**
   * @brief Duration in seconds after which the sensor automatically stops.
   *
   * Use 0 for no automatic stop (sensor runs until stop() is called).
   */
  int32_t activeStopSeconds = 0;
  inline bool operator!=(const StartConfig& rhs) const {
    return std::tie(operationalMode, noMotionSeconds, activeStartSeconds, activeStopSeconds) != std::tie(rhs.operationalMode, rhs.noMotionSeconds, rhs.activeStartSeconds, rhs.activeStopSeconds);
  }
  inline bool operator<(const StartConfig& rhs) const {
    return std::tie(operationalMode, noMotionSeconds, activeStartSeconds, activeStopSeconds) < std::tie(rhs.operationalMode, rhs.noMotionSeconds, rhs.activeStartSeconds, rhs.activeStopSeconds);
  }
  inline bool operator<=(const StartConfig& rhs) const {
    return std::tie(operationalMode, noMotionSeconds, activeStartSeconds, activeStopSeconds) <= std::tie(rhs.operationalMode, rhs.noMotionSeconds, rhs.activeStartSeconds, rhs.activeStopSeconds);
  }
  inline bool operator==(const StartConfig& rhs) const {
    return std::tie(operationalMode, noMotionSeconds, activeStartSeconds, activeStopSeconds) == std::tie(rhs.operationalMode, rhs.noMotionSeconds, rhs.activeStartSeconds, rhs.activeStopSeconds);
  }
  inline bool operator>(const StartConfig& rhs) const {
    return std::tie(operationalMode, noMotionSeconds, activeStartSeconds, activeStopSeconds) > std::tie(rhs.operationalMode, rhs.noMotionSeconds, rhs.activeStartSeconds, rhs.activeStopSeconds);
  }
  inline bool operator>=(const StartConfig& rhs) const {
    return std::tie(operationalMode, noMotionSeconds, activeStartSeconds, activeStopSeconds) >= std::tie(rhs.operationalMode, rhs.noMotionSeconds, rhs.activeStartSeconds, rhs.activeStopSeconds);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.sensor.motion.StartConfig");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "StartConfig{";
    os << "operationalMode: " << ::android::internal::ToString(operationalMode);
    os << ", noMotionSeconds: " << ::android::internal::ToString(noMotionSeconds);
    os << ", activeStartSeconds: " << ::android::internal::ToString(activeStartSeconds);
    os << ", activeStopSeconds: " << ::android::internal::ToString(activeStopSeconds);
    os << "}";
    return os.str();
  }
};  // class StartConfig
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
