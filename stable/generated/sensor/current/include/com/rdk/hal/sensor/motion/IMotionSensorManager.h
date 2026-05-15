#pragma once

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
class IMotionSensorManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(MotionSensorManager)
  static const int32_t VERSION = 1;
  const std::string HASH = "fe60d3f4495ff4af10cfa3bdd049282660d60367";
  static constexpr char* HASHVALUE = "fe60d3f4495ff4af10cfa3bdd049282660d60367";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getMotionSensorIds(::std::optional<::std::vector<::std::optional<::com::rdk::hal::sensor::motion::IMotionSensor::Id>>>* _aidl_return) = 0;
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
