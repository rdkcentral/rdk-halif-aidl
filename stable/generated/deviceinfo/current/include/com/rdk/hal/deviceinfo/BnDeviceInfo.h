#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/deviceinfo/IDeviceInfo.h>

namespace com {
namespace rdk {
namespace hal {
namespace deviceinfo {
class BnDeviceInfo : public ::android::BnInterface<IDeviceInfo> {
public:
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnDeviceInfo();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnDeviceInfo

class IDeviceInfoDelegator : public BnDeviceInfo {
public:
  explicit IDeviceInfoDelegator(::android::sp<IDeviceInfo> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getCapabilities(::com::rdk::hal::deviceinfo::Capabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status getProperty(const ::android::String16& propertyKey, ::std::optional<::com::rdk::hal::deviceinfo::Property>* _aidl_return) override {
    return _aidl_delegate->getProperty(propertyKey, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnDeviceInfo::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IDeviceInfo> _aidl_delegate;
};  // class IDeviceInfoDelegator
}  // namespace deviceinfo
}  // namespace hal
}  // namespace rdk
}  // namespace com
