#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/planecontrol/IGraphicsFbProviderListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
class BpGraphicsFbProviderListener : public ::android::BpInterface<IGraphicsFbProviderListener> {
public:
  explicit BpGraphicsFbProviderListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpGraphicsFbProviderListener() = default;
  ::android::binder::Status onGraphicsFbReleased(int32_t oldGraphicsFbId, int64_t elapsedRealtimeNanos) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpGraphicsFbProviderListener
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
