#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/sensor/motion/IMotionSensorManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
class BpMotionSensorManager : public ::android::BpInterface<IMotionSensorManager> {
public:
  explicit BpMotionSensorManager(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpMotionSensorManager() = default;
  ::android::binder::Status getMotionSensorIds(::std::optional<::std::vector<::std::optional<::com::rdk::hal::sensor::motion::IMotionSensor::Id>>>* _aidl_return) override;
  ::android::binder::Status getMotionSensor(const ::com::rdk::hal::sensor::motion::IMotionSensor::Id& motionSensorId, ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensor>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpMotionSensorManager
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
