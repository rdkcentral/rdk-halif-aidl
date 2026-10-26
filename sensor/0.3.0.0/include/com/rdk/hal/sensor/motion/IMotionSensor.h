#pragma once
// @aidl-doc
/**
 * @file IMotionSensor.h
 * @brief Instance interface for a motion sensor (PIR, radar, etc.).
 *
 * The motion sensor can operate in a mode that reports either "motion" events
 * or "no-motion" events after an inactivity window. Sensitivity is optional:
 * if unsupported, both minSensitivity and maxSensitivity are 0.
 *
 * Lifecycle ownership:
 * The sensor uses a controller pattern. A single middleware component
 * (e.g., a power management service) calls open() to acquire an exclusive
 * IMotionSensorController for lifecycle and configuration control. Other
 * components register as event listeners via registerEventListener() to
 * observe motion/no-motion events without needing ownership.
 *
 * If the client that opened the controller crashes, stop() and close()
 * are implicitly called by the HAL to release the sensor.
 *
 * Timing controls vs active windows:
 * StartConfig.activeStartSeconds/activeStopSeconds and active windows
 * (configured via IMotionSensorController.setActiveWindows()) are
 * independent, layered mechanisms:
 *   - Timing controls govern the sensor hardware lifecycle — whether
 *     the sensor is active at all.
 *   - Active windows govern event suppression — whether detected events
 *     are delivered to listeners.
 *
 * Timing controls take precedence. Callers are responsible for ensuring
 * sensible combinations.
 *
 * @author Gerald Weatherup
 */

#include <android/binder_to_string.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/sensor/motion/Capabilities.h>
#include <com/rdk/hal/sensor/motion/IMotionSensorController.h>
#include <com/rdk/hal/sensor/motion/IMotionSensorControllerListener.h>
#include <com/rdk/hal/sensor/motion/IMotionSensorEventListener.h>
#include <com/rdk/hal/sensor/motion/State.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
class IMotionSensor : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(MotionSensor)
  static const int32_t VERSION = 3000;
  const std::string HASH = "ca14e229e5f8cefddd0d8b6e67b08b46794a46ad";
  static constexpr char* HASHVALUE = "ca14e229e5f8cefddd0d8b6e67b08b46794a46ad";
  // @aidl-doc
  /** @brief Motion sensor resource identifier type. */
  class Id : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** @brief The concrete resource identifier value. */
    int32_t value = 0;
    inline bool operator!=(const Id& rhs) const {
      return std::tie(value) != std::tie(rhs.value);
    }
    inline bool operator<(const Id& rhs) const {
      return std::tie(value) < std::tie(rhs.value);
    }
    inline bool operator<=(const Id& rhs) const {
      return std::tie(value) <= std::tie(rhs.value);
    }
    inline bool operator==(const Id& rhs) const {
      return std::tie(value) == std::tie(rhs.value);
    }
    inline bool operator>(const Id& rhs) const {
      return std::tie(value) > std::tie(rhs.value);
    }
    inline bool operator>=(const Id& rhs) const {
      return std::tie(value) >= std::tie(rhs.value);
    }

    // @aidl-doc
    /** @brief Undefined/invalid ID value. */
    enum : int32_t { UNDEFINED = -1 };
    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.sensor.motion.IMotionSensor.Id");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "Id{";
      os << "value: " << ::android::internal::ToString(value);
      os << "}";
      return os.str();
    }
  };  // class Id
  // @aidl-doc
  /**
   * @brief Returns immutable capabilities for this sensor.
   *
   * Can be called at any time, regardless of sensor state.
   *
   * @param[out] _aidl_return Immutable capabilities describing this sensor instance.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::sensor::motion::Capabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Get the current lifecycle state of the sensor.
   *
   * @param[out] _aidl_return Current state (e.g. STARTED, STOPPED, ERROR).
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getState(::com::rdk::hal::sensor::motion::State* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Open this sensor for exclusive control.
   *
   * On success the sensor is ready for configuration and start().
   * The returned IMotionSensorController provides lifecycle control,
   * configuration, and diagnostic queries.
   *
   * Only one controller may exist at a time. If the owning client
   * crashes, the HAL implicitly calls stop() and close() to release
   * the sensor.
   *
   * @param listener Listener for controller callbacks (state changes,
   *                 active window transitions).
   *
   * @param[out] _aidl_return IMotionSensorController, or null if the sensor cannot be opened.
   *
   * @see close(), IMotionSensorController
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if sensor is already open.
   * @retval ::android::binder::Status::EX_NULL_POINTER if listener is null.
   */
  virtual ::android::binder::Status open(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorControllerListener>& listener, ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorController>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Close this sensor and release the controller.
   *
   * Accepted from STOPPED or ERROR. From STOPPED this is the normal close
   * path. From ERROR this is the recovery path: after a start() failure
   * (which transitions the sensor to ERROR), the client calls close() to
   * release the controller and the sensor returns to a state where it can
   * be opened again. On success the controller is invalidated and another
   * client may `open()` the sensor.
   *
   * If the sensor is in STARTED, STARTING, or STOPPING the call fails with
   * EX_ILLEGAL_STATE — the client must call stop() first (or, from ERROR,
   * close() directly).
   *
   * @param controller The IMotionSensorController instance returned by open().
   *
   * @param[out] _aidl_return Success flag.
   *   - true: Successfully closed.
   *   - false: The supplied controller is not the instance returned by open().
   * @see open(), IMotionSensorController.start()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if sensor is not in STOPPED or ERROR state.
   * @retval ::android::binder::Status::EX_NULL_POINTER if controller is null.
   */
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorController>& controller, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Register an event listener.
   *
   * Multiple listeners may be registered. Event listeners receive
   * motion/no-motion detection events via onEvent(). Registration does
   * not require the sensor to be open.
   *
   * @param motionSensorEventListener Listener to receive motion events.
   *
   * @param[out] _aidl_return Success flag.
   *   - true: Listener registered.
   *   - false: Listener already registered.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorEventListener>& motionSensorEventListener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Unregister a previously registered listener.
   *
   * @param motionSensorEventListener Listener to remove.
   *
   * @param[out] _aidl_return Success flag.
   *   - true: Listener unregistered.
   *   - false: Listener not found.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorEventListener>& motionSensorEventListener, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IMotionSensor

class IMotionSensorDefault : public IMotionSensor {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::sensor::motion::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getState(::com::rdk::hal::sensor::motion::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorControllerListener>& /*listener*/, ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorController>& /*controller*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorEventListener>& /*motionSensorEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorEventListener>& /*motionSensorEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IMotionSensorDefault
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
