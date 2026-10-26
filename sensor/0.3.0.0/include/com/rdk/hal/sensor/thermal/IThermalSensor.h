#pragma once
// @aidl-doc
/**
 * @file IThermalSensor.h
 * @brief Thermal policy service interface (singleton).
 *
 * @details
 * Exposes high-level policy decisions via events and a summarized state query.
 * Does not expose raw thresholds to clients.
 */

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/sensor/thermal/IThermalEventListener.h>
#include <com/rdk/hal/sensor/thermal/State.h>
#include <com/rdk/hal/sensor/thermal/TemperatureReading.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace thermal {
class IThermalSensor : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(ThermalSensor)
  static const int32_t VERSION = 3000;
  const std::string HASH = "ca14e229e5f8cefddd0d8b6e67b08b46794a46ad";
  static constexpr char* HASHVALUE = "ca14e229e5f8cefddd0d8b6e67b08b46794a46ad";
  // @aidl-doc
  /** @brief Binder service registration name. */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * @brief Register for event-driven thermal actions.
   * @param listener Listener to receive thermal action events.
   * @param[out] _aidl_return
   *   - true: Listener registered.
   *   - false: Listener already registered.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::sensor::thermal::IThermalEventListener>& listener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Unregister a previously registered listener.
   * @param listener Listener to remove.
   * @param[out] _aidl_return
   *   - true: Listener unregistered.
   *   - false: Listener not found.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::sensor::thermal::IThermalEventListener>& listener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Query the worst current state across all thermal sensors.
   * @details Each sensor has its own state; this returns the most severe
   * (NORMAL < CRITICAL_TEMPERATURE_EXCEEDED < CRITICAL_SHUTDOWN_IMMINENT).
   * Use onThermalStateChange() events to see which sensor changed.
   * @param[out] _aidl_return State Worst current sensor state.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCurrentThermalState(::com::rdk::hal::sensor::thermal::State* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Optional temperature telemetry snapshot.
   * @details Implementations may return an empty array if unsupported.
   * @param[out] _aidl_return TemperatureReading[] Zero or more temperature readings.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCurrentTemperatures(::std::vector<::com::rdk::hal::sensor::thermal::TemperatureReading>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IThermalSensor

class IThermalSensorDefault : public IThermalSensor {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::sensor::thermal::IThermalEventListener>& /*listener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::sensor::thermal::IThermalEventListener>& /*listener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCurrentThermalState(::com::rdk::hal::sensor::thermal::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCurrentTemperatures(::std::vector<::com::rdk::hal::sensor::thermal::TemperatureReading>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IThermalSensorDefault
}  // namespace thermal
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
