#pragma once
// @aidl-doc
/**
 * @file IMotionSensorControllerListener.h
 * @brief Controller callback listener for motion sensor lifecycle and
 *        active window transitions.
 *
 * Passed into {@link IMotionSensor#open(IMotionSensorControllerListener)}.
 * Delivered exclusively to the controller owner. All callbacks are oneway
 * (non-blocking, fire-and-forget).
 *
 * Motion/no-motion detection events are delivered separately on
 * {@link IMotionSensorEventListener} to any registered observer.
 *
 * @author Gerald Weatherup
 */

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/sensor/motion/State.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
class IMotionSensorControllerListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(MotionSensorControllerListener)
  static const int32_t VERSION = 3000;
  const std::string HASH = "ca14e229e5f8cefddd0d8b6e67b08b46794a46ad";
  static constexpr char* HASHVALUE = "ca14e229e5f8cefddd0d8b6e67b08b46794a46ad";
  // @aidl-doc
  /**
   * @brief Called when the sensor transitions to a new lifecycle state.
   *
   * Fired for all transitions driven by start(), stop(), and error
   * conditions. The motion sensor State enum covers STOPPED, STARTING,
   * STARTED, STOPPING, ERROR — controller acquisition (IMotionSensor.open)
   * and release (IMotionSensor.close) do not produce dedicated state
   * values; they bracket the STOPPED period during which the controller
   * exists.
   *
   * @param[in] oldState  The state being left.
   * @param[in] newState  The state being entered.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::sensor::motion::State oldState, ::com::rdk::hal::sensor::motion::State newState) = 0;
  // @aidl-doc
  /**
   * @brief Called when the sensor enters an active monitoring period.
   *
   * Fires when the current time enters the union of all configured active
   * windows. If windows overlap, this callback fires once on the first
   * entry — not per-window. Motion events may be delivered while inside
   * the active period.
   *
   * Only fires when active windows have been configured via
   * IMotionSensorController.setActiveWindows() with a non-empty array.
   * Not fired when 24-hour monitoring is in effect, whether that is
   * because no windows have been set or because setActiveWindows() was
   * called with an empty array.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onActiveWindowEntered() = 0;
  // @aidl-doc
  /**
   * @brief Called when the sensor exits all active monitoring windows.
   *
   * Fires when the current time leaves the union of all configured active
   * windows. Motion events are suppressed while outside active windows.
   *
   * Only fires when active windows have been configured via
   * IMotionSensorController.setActiveWindows() with a non-empty array.
   * Not fired in 24-hour monitoring mode (no windows / empty array).
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onActiveWindowExited() = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IMotionSensorControllerListener

class IMotionSensorControllerListenerDefault : public IMotionSensorControllerListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::sensor::motion::State /*oldState*/, ::com::rdk::hal::sensor::motion::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onActiveWindowEntered() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onActiveWindowExited() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IMotionSensorControllerListenerDefault
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
