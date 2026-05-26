#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/compositeinput/ICompositeInputControllerListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
class BpCompositeInputControllerListener : public ::android::BpInterface<ICompositeInputControllerListener> {
public:
  explicit BpCompositeInputControllerListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCompositeInputControllerListener() = default;
  ::android::binder::Status onConnectionChanged(bool connected) override;
  ::android::binder::Status onSignalStatusChanged(::com::rdk::hal::compositeinput::SignalStatus signalStatus) override;
  ::android::binder::Status onVideoModeChanged(const ::com::rdk::hal::compositeinput::VideoResolution& resolution) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpCompositeInputControllerListener
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
