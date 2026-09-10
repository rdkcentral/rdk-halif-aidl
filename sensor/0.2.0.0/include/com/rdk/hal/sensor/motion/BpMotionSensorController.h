#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/sensor/motion/IMotionSensorController.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
class BpMotionSensorController : public ::android::BpInterface<IMotionSensorController> {
public:
  explicit BpMotionSensorController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpMotionSensorController() = default;
  ::android::binder::Status start(const ::com::rdk::hal::sensor::motion::StartConfig& config) override;
  ::android::binder::Status stop() override;
  ::android::binder::Status getStartConfig(::com::rdk::hal::sensor::motion::StartConfig* _aidl_return) override;
  ::android::binder::Status getLastEventInfo(::std::optional<::com::rdk::hal::sensor::motion::LastEventInfo>* _aidl_return) override;
  ::android::binder::Status getSensitivity(int32_t* _aidl_return) override;
  ::android::binder::Status setSensitivity(int32_t sensitivity, bool* _aidl_return) override;
  ::android::binder::Status setAutonomousDuringDeepSleep(bool enabled, bool* _aidl_return) override;
  ::android::binder::Status isAutonomousDuringDeepSleepEnabled(bool* _aidl_return) override;
  ::android::binder::Status setActiveWindows(const ::std::vector<::com::rdk::hal::sensor::motion::TimeWindow>& windows, bool* _aidl_return) override;
  ::android::binder::Status getActiveWindows(::std::vector<::com::rdk::hal::sensor::motion::TimeWindow>* _aidl_return) override;
  ::android::binder::Status clearActiveWindows(bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpMotionSensorController
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
