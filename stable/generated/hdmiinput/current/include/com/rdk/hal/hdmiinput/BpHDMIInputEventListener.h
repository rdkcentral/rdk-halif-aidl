#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/hdmiinput/IHDMIInputEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
class BpHDMIInputEventListener : public ::android::BpInterface<IHDMIInputEventListener> {
public:
  explicit BpHDMIInputEventListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHDMIInputEventListener() = default;
  ::android::binder::Status onStateChanged(::com::rdk::hal::hdmiinput::State oldState, ::com::rdk::hal::hdmiinput::State newState) override;
  ::android::binder::Status onEDIDChange(const ::std::vector<uint8_t>& edid) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpHDMIInputEventListener
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
