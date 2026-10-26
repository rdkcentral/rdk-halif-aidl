#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/hdmicec/IHdmiCecController.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
class BpHdmiCecController : public ::android::BpInterface<IHdmiCecController> {
public:
  explicit BpHdmiCecController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHdmiCecController() = default;
  ::android::binder::Status addLogicalAddresses(const ::std::vector<int32_t>& logicalAddresses, bool* _aidl_return) override;
  ::android::binder::Status removeLogicalAddresses(const ::std::vector<int32_t>& logicalAddresses, bool* _aidl_return) override;
  ::android::binder::Status sendMessage(const ::std::vector<uint8_t>& message, ::com::rdk::hal::hdmicec::SendMessageStatus* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpHdmiCecController
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
