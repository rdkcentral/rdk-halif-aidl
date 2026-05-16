#pragma once

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
  static const int32_t VERSION = 1;
  const std::string HASH = "fe60d3f4495ff4af10cfa3bdd049282660d60367";
  static constexpr char* HASHVALUE = "fe60d3f4495ff4af10cfa3bdd049282660d60367";
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::sensor::motion::State oldState, ::com::rdk::hal::sensor::motion::State newState) = 0;
  virtual ::android::binder::Status onActiveWindowEntered() = 0;
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
