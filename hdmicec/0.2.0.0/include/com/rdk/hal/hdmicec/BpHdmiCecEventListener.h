#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/hdmicec/IHdmiCecEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
class BpHdmiCecEventListener : public ::android::BpInterface<IHdmiCecEventListener> {
public:
  explicit BpHdmiCecEventListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHdmiCecEventListener() = default;
  ::android::binder::Status onMessageReceived(const ::std::vector<uint8_t>& message) override;
  ::android::binder::Status onStateChanged(::com::rdk::hal::hdmicec::State oldState, ::com::rdk::hal::hdmicec::State newState) override;
  ::android::binder::Status onMessageSent(const ::std::vector<uint8_t>& message, ::com::rdk::hal::hdmicec::SendMessageStatus status) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpHdmiCecEventListener
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
