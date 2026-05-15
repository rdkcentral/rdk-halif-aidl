#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/sensor/motion/LastEventInfo.h>
#include <com/rdk/hal/sensor/motion/StartConfig.h>
#include <com/rdk/hal/sensor/motion/TimeWindow.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
class IMotionSensorController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(MotionSensorController)
  static const int32_t VERSION = 1;
  const std::string HASH = "fe60d3f4495ff4af10cfa3bdd049282660d60367";
  static constexpr char* HASHVALUE = "fe60d3f4495ff4af10cfa3bdd049282660d60367";
  virtual ::android::binder::Status start(const ::com::rdk::hal::sensor::motion::StartConfig& config) = 0;
  virtual ::android::binder::Status stop() = 0;
  virtual ::android::binder::Status getStartConfig(::com::rdk::hal::sensor::motion::StartConfig* _aidl_return) = 0;
  virtual ::android::binder::Status getLastEventInfo(::std::optional<::com::rdk::hal::sensor::motion::LastEventInfo>* _aidl_return) = 0;
  virtual ::android::binder::Status getSensitivity(int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status setSensitivity(int32_t sensitivity, bool* _aidl_return) = 0;
  virtual ::android::binder::Status setAutonomousDuringDeepSleep(bool enabled, bool* _aidl_return) = 0;
  virtual ::android::binder::Status isAutonomousDuringDeepSleepEnabled(bool* _aidl_return) = 0;
  virtual ::android::binder::Status setActiveWindows(const ::std::vector<::com::rdk::hal::sensor::motion::TimeWindow>& windows, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getActiveWindows(::std::vector<::com::rdk::hal::sensor::motion::TimeWindow>* _aidl_return) = 0;
  virtual ::android::binder::Status clearActiveWindows(bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IMotionSensorController

class IMotionSensorControllerDefault : public IMotionSensorController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status start(const ::com::rdk::hal::sensor::motion::StartConfig& /*config*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getStartConfig(::com::rdk::hal::sensor::motion::StartConfig* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getLastEventInfo(::std::optional<::com::rdk::hal::sensor::motion::LastEventInfo>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getSensitivity(int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setSensitivity(int32_t /*sensitivity*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setAutonomousDuringDeepSleep(bool /*enabled*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status isAutonomousDuringDeepSleepEnabled(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setActiveWindows(const ::std::vector<::com::rdk::hal::sensor::motion::TimeWindow>& /*windows*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getActiveWindows(::std::vector<::com::rdk::hal::sensor::motion::TimeWindow>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status clearActiveWindows(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IMotionSensorControllerDefault
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
