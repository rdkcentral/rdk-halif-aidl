#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/hdmicec/IHdmiCec.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
class BpHdmiCec : public ::android::BpInterface<IHdmiCec> {
public:
  explicit BpHdmiCec(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHdmiCec() = default;
  ::android::binder::Status getState(::com::rdk::hal::hdmicec::State* _aidl_return) override;
  ::android::binder::Status getProperty(::com::rdk::hal::hdmicec::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) override;
  ::android::binder::Status getLogicalAddresses(::std::vector<int32_t>* _aidl_return) override;
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecEventListener>& cecControllerListener, ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecController>* _aidl_return) override;
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecController>& hdmiCecController, bool* _aidl_return) override;
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecEventListener>& cecEventListener, bool* _aidl_return) override;
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecEventListener>& cecEventListener, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpHdmiCec
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
