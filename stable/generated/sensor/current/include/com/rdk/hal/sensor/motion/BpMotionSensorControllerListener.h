#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/sensor/motion/IMotionSensorControllerListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
class BpMotionSensorControllerListener : public ::android::BpInterface<IMotionSensorControllerListener> {
public:
  explicit BpMotionSensorControllerListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpMotionSensorControllerListener() = default;
  ::android::binder::Status onStateChanged(::com::rdk::hal::sensor::motion::State oldState, ::com::rdk::hal::sensor::motion::State newState) override;
  ::android::binder::Status onActiveWindowEntered() override;
  ::android::binder::Status onActiveWindowExited() override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpMotionSensorControllerListener
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
