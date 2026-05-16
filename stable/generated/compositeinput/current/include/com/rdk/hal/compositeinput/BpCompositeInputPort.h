#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/compositeinput/ICompositeInputPort.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
class BpCompositeInputPort : public ::android::BpInterface<ICompositeInputPort> {
public:
  explicit BpCompositeInputPort(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCompositeInputPort() = default;
  ::android::binder::Status getId(int32_t* _aidl_return) override;
  ::android::binder::Status getPortInfo(::com::rdk::hal::compositeinput::Port* _aidl_return) override;
  ::android::binder::Status getCapabilities(::com::rdk::hal::compositeinput::PortCapabilities* _aidl_return) override;
  ::android::binder::Status getState(::com::rdk::hal::compositeinput::State* _aidl_return) override;
  ::android::binder::Status getStatus(::com::rdk::hal::compositeinput::PortStatus* _aidl_return) override;
  ::android::binder::Status getProperty(::com::rdk::hal::compositeinput::PortProperty property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) override;
  ::android::binder::Status getPropertyMulti(const ::std::vector<::com::rdk::hal::compositeinput::PortProperty>& properties, ::std::vector<::com::rdk::hal::compositeinput::PropertyKVPair>* _aidl_return) override;
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputControllerListener>& listener, ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputController>* _aidl_return) override;
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputController>& controller, bool* _aidl_return) override;
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputEventListener>& listener) override;
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputEventListener>& listener) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpCompositeInputPort
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
