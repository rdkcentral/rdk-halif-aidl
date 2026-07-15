#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/planecontrol/IPlaneControlListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
class BpPlaneControlListener : public ::android::BpInterface<IPlaneControlListener> {
public:
  explicit BpPlaneControlListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpPlaneControlListener() = default;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpPlaneControlListener
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
