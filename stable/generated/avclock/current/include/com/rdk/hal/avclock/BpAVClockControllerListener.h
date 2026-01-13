#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/avclock/IAVClockControllerListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
class BpAVClockControllerListener : public ::android::BpInterface<IAVClockControllerListener> {
public:
  explicit BpAVClockControllerListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAVClockControllerListener() = default;
  ::android::binder::Status onStateChanged(::com::rdk::hal::State oldState, ::com::rdk::hal::State newState) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAVClockControllerListener
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
