#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/demo/hal/car/ICarStatusListener.h>

namespace com {
namespace demo {
namespace hal {
namespace car {
class BpCarStatusListener : public ::android::BpInterface<ICarStatusListener> {
public:
  explicit BpCarStatusListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCarStatusListener() = default;
  ::android::binder::Status onCarStatusChanged(const ::com::demo::hal::car::CarStatus& newStatus) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpCarStatusListener
}  // namespace car
}  // namespace hal
}  // namespace demo
}  // namespace com
