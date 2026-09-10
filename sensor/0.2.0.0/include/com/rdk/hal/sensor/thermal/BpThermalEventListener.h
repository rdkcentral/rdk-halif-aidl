#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/sensor/thermal/IThermalEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace thermal {
class BpThermalEventListener : public ::android::BpInterface<IThermalEventListener> {
public:
  explicit BpThermalEventListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpThermalEventListener() = default;
  ::android::binder::Status onThermalStateChange(const ::com::rdk::hal::sensor::thermal::ActionEvent& event) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpThermalEventListener
}  // namespace thermal
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
