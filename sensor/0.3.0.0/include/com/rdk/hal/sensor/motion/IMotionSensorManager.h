#pragma once
// @aidl-doc
/**
 * @file IMotionSensorManager.h
 * @brief Service entry point for discovering and accessing motion sensors.
 *
 * The manager enumerates available motion sensors and returns interfaces
 * to them.  A typical implementation is a singleton service registered under
 * {@link #serviceName}.
 */

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/sensor/motion/IMotionSensor.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
// @aidl-doc
/**
 * @interface IMotionSensorManager
 * @brief Top-level manager interface for Motion Sensor HAL access.
 */
class IMotionSensorManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(MotionSensorManager)
  static const int32_t VERSION = 3000;
  const std::string HASH = "ca14e229e5f8cefddd0d8b6e67b08b46794a46ad";
  static constexpr char* HASHVALUE = "ca14e229e5f8cefddd0d8b6e67b08b46794a46ad";
  // @aidl-doc
  /**
   * @brief Binder service registration name.
   *
   * Vendors should publish the service with this name at system startup.
   */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * @brief Enumerate all platform-specific motion sensor identifiers.
   * @param[out] _aidl_return Array of available motion sensor IDs.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getMotionSensorIds(::std::optional<::std::vector<::std::optional<::com::rdk::hal::sensor::motion::IMotionSensor::Id>>>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Retrieve a motion sensor interface by ID.
   * @param motionSensorId The identifier of the requested sensor.
   * @param[out] _aidl_return The sensor interface, or null if the ID is invalid.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getMotionSensor(const ::com::rdk::hal::sensor::motion::IMotionSensor::Id& motionSensorId, ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensor>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IMotionSensorManager

class IMotionSensorManagerDefault : public IMotionSensorManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getMotionSensorIds(::std::optional<::std::vector<::std::optional<::com::rdk::hal::sensor::motion::IMotionSensor::Id>>>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getMotionSensor(const ::com::rdk::hal::sensor::motion::IMotionSensor::Id& /*motionSensorId*/, ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensor>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IMotionSensorManagerDefault
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
