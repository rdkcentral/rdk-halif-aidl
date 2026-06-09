#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/sensor/motion/IMotionSensor.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
class BpMotionSensor : public ::android::BpInterface<IMotionSensor> {
public:
  explicit BpMotionSensor(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpMotionSensor() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::sensor::motion::Capabilities* _aidl_return) override;
  ::android::binder::Status getState(::com::rdk::hal::sensor::motion::State* _aidl_return) override;
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorControllerListener>& listener, ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorController>* _aidl_return) override;
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorController>& controller, bool* _aidl_return) override;
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorEventListener>& motionSensorEventListener, bool* _aidl_return) override;
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorEventListener>& motionSensorEventListener, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpMotionSensor
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
