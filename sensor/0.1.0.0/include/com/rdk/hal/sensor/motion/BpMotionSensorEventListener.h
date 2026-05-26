#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/sensor/motion/IMotionSensorEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
class BpMotionSensorEventListener : public ::android::BpInterface<IMotionSensorEventListener> {
public:
  explicit BpMotionSensorEventListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpMotionSensorEventListener() = default;
  ::android::binder::Status onEvent(::com::rdk::hal::sensor::motion::OperationalMode mode) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpMotionSensorEventListener
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
