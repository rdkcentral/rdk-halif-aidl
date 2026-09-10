#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/sensor/motion/MotionEvent.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
class IMotionSensorEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(MotionSensorEventListener)
  static const int32_t VERSION = 2000;
  const std::string HASH = "a1a83f7c04d62edd76436e8afc6af13e7053a62c";
  static constexpr char* HASHVALUE = "a1a83f7c04d62edd76436e8afc6af13e7053a62c";
  virtual ::android::binder::Status onEvent(const ::com::rdk::hal::sensor::motion::MotionEvent& event) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IMotionSensorEventListener

class IMotionSensorEventListenerDefault : public IMotionSensorEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onEvent(const ::com::rdk::hal::sensor::motion::MotionEvent& /*event*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IMotionSensorEventListenerDefault
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
