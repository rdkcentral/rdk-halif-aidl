#pragma once
// @aidl-doc
/**
 * @file IMotionSensorController.h
 * @brief Exclusive controller interface for a motion sensor instance.
 *
 * Returned by {@link IMotionSensor#open(IMotionSensorControllerListener)}.
 * Provides lifecycle control (start/stop), configuration, and diagnostic
 * queries. Only one controller may exist per sensor at a time.
 *
 * If the client that opened this controller crashes, stop() and close()
 * are implicitly called by the HAL to release the sensor.
 *
 * @author Gerald Weatherup
 */

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/sensor/motion/LastEventInfo.h>
#include <com/rdk/hal/sensor/motion/StartConfig.h>
#include <com/rdk/hal/sensor/motion/TimeWindow.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
class IMotionSensorController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(MotionSensorController)
  static const int32_t VERSION = 3000;
  const std::string HASH = "ca14e229e5f8cefddd0d8b6e67b08b46794a46ad";
  static constexpr char* HASHVALUE = "ca14e229e5f8cefddd0d8b6e67b08b46794a46ad";
  // @aidl-doc
  /**
   * @brief Start the motion sensor.
   *
   * On success, the state transitions STOPPED → STARTING → STARTED.
   * IMotionSensorControllerListener.onStateChanged() fires for each transition.
   * If hardware initialisation fails, the state transitions to ERROR
   * (observable via onStateChanged()) and this call fails with
   * EX_SERVICE_SPECIFIC. Use IMotionSensor.close() to release the sensor
   * from ERROR; close() accepts STOPPED or ERROR.
   *
   * @param config Start configuration (mode, timing parameters).
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if sensor is not in STOPPED state.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if StartConfig contains
   *                     invalid values (e.g. noMotionSeconds outside 0–86400 range).
   * @retval ::android::binder::Status::EX_SERVICE_SPECIFIC if hardware initialisation
   *                     fails. The state transitions to ERROR before the exception
   *                     is raised.
   *
   *          Aligned with the repo-wide controller convention (`void start()` +
   *          binder exceptions for failure, lifecycle observable via state change
   *          listener) — same shape as compositeinput, hdmiinput, audiosink, etc.
   */
  virtual ::android::binder::Status start(const ::com::rdk::hal::sensor::motion::StartConfig& config) = 0;
  // @aidl-doc
  /**
   * @brief Stop the motion sensor.
   *
   * On success, the state transitions STARTED → STOPPING → STOPPED.
   * IMotionSensorControllerListener.onStateChanged() fires for each transition.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if sensor is not in STARTED state.
   *
   *          Aligned with the repo-wide controller convention (`void stop()` +
   *          binder exception for failure).
   */
  virtual ::android::binder::Status stop() = 0;
  // @aidl-doc
  /**
   * @brief Retrieve the configuration passed to start().
   *
   * @param[out] _aidl_return The StartConfig used for the current session.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if sensor is in STOPPED or ERROR state.
   */
  virtual ::android::binder::Status getStartConfig(::com::rdk::hal::sensor::motion::StartConfig* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Retrieve diagnostic info about the most recent event.
   *
   * Returns the mode and timestamp of the last onEvent() delivered to
   * listeners. Returns null if no event has been delivered since start().
   *
   * @param[out] _aidl_return LastEventInfo, or null if no event has occurred.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if sensor is in STOPPED or ERROR state.
   */
  virtual ::android::binder::Status getLastEventInfo(::std::optional<::com::rdk::hal::sensor::motion::LastEventInfo>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Get the current sensitivity value.
   *
   * @param[out] _aidl_return Current sensitivity level (within Capabilities.minSensitivity..maxSensitivity).
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getSensitivity(int32_t* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Set the sensitivity level.
   *
   * @param sensitivity Desired level. Must be within
   *        {@link Capabilities#minSensitivity}..{@link Capabilities#maxSensitivity}.
   *
   * @param[out] _aidl_return Success flag.
   *   - true: Sensitivity was set.
   *   - false: Sensitivity out of range or unsupported.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if sensor is not in STOPPED state.
   */
  virtual ::android::binder::Status setSensitivity(int32_t sensitivity, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Enable or disable autonomous motion detection during deep sleep.
   *
   * When enabled and supported by the platform, the sensor may wake the system
   * from deep sleep based on motion activity without full SoC resume.
   *
   * The deep sleep module must be configured independently to support the
   * CPU wake-up reasons — enabling sensor autonomy alone does not affect
   * CPU deep sleep behaviour.
   *
   * @param enabled True to enable, false to disable.
   *
   * @param[out] _aidl_return Success flag.
   *   - true: Mode updated (or already at requested value).
   *   - false: Not supported (see Capabilities.supportsDeepSleepAutonomy).
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if sensor is not in STOPPED state.
   */
  virtual ::android::binder::Status setAutonomousDuringDeepSleep(bool enabled, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Query whether autonomous deep-sleep mode is enabled.
   *
   * @param[out] _aidl_return True if enabled, false otherwise (or unsupported).
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status isAutonomousDuringDeepSleepEnabled(bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Set daily time windows when the sensor should actively monitor.
   *
   * Windows wrapping across midnight are supported (endTime < startTime).
   * Changes take effect on next start() call. Calling this method replaces
   * any previously configured windows.
   *
   * @param windows Array of time windows. Motion events outside these windows
   *        are suppressed. Empty array or windows with both values set to 0
   *        enables 24-hour monitoring. Windows may overlap; the union of all
   *        windows defines the active periods.
   *
   * @param[out] _aidl_return Success flag.
   *   - true: Windows configured successfully.
   *   - false: Invalid window ranges or sensor state prevents configuration.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if any window has invalid
   *                     time values (outside 0–86399 range).
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if sensor is not in STOPPED state.
   */
  virtual ::android::binder::Status setActiveWindows(const ::std::vector<::com::rdk::hal::sensor::motion::TimeWindow>& windows, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Get the currently configured active time windows.
   *
   * @param[out] _aidl_return Array of active windows. Empty if 24-hour monitoring is configured
   *                          or no windows have been set.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getActiveWindows(::std::vector<::com::rdk::hal::sensor::motion::TimeWindow>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Clear all active time windows, enabling 24-hour monitoring.
   *
   * Equivalent to calling setActiveWindows() with an empty array.
   *
   * @param[out] _aidl_return Success flag.
   *   - true: Windows cleared successfully.
   *   - false: Unable to clear (e.g., sensor not in valid state).
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if sensor is not in STOPPED state.
   */
  virtual ::android::binder::Status clearActiveWindows(bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IMotionSensorController

class IMotionSensorControllerDefault : public IMotionSensorController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status start(const ::com::rdk::hal::sensor::motion::StartConfig& /*config*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getStartConfig(::com::rdk::hal::sensor::motion::StartConfig* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getLastEventInfo(::std::optional<::com::rdk::hal::sensor::motion::LastEventInfo>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getSensitivity(int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setSensitivity(int32_t /*sensitivity*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setAutonomousDuringDeepSleep(bool /*enabled*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status isAutonomousDuringDeepSleepEnabled(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setActiveWindows(const ::std::vector<::com::rdk::hal::sensor::motion::TimeWindow>& /*windows*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getActiveWindows(::std::vector<::com::rdk::hal::sensor::motion::TimeWindow>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status clearActiveWindows(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IMotionSensorControllerDefault
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
