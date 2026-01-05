#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/boot/IBoot.h>

namespace com {
namespace rdk {
namespace hal {
namespace boot {
class BnBoot : public ::android::BnInterface<IBoot> {
public:
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getBootReason = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_setBootReason = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_reboot = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getPowerSource = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnBoot();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnBoot

class IBootDelegator : public BnBoot {
public:
  explicit IBootDelegator(::android::sp<IBoot> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getCapabilities(::com::rdk::hal::boot::Capabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status getBootReason(::com::rdk::hal::boot::BootReason* _aidl_return) override {
    return _aidl_delegate->getBootReason(_aidl_return);
  }
  ::android::binder::Status setBootReason(::com::rdk::hal::boot::BootReason reason, const ::android::String16& reasonString) override {
    return _aidl_delegate->setBootReason(reason, reasonString);
  }
  ::android::binder::Status reboot(::com::rdk::hal::boot::ResetType resetType, const ::android::String16& reasonString) override {
    return _aidl_delegate->reboot(resetType, reasonString);
  }
  ::android::binder::Status getPowerSource(::com::rdk::hal::boot::PowerSource* _aidl_return) override {
    return _aidl_delegate->getPowerSource(_aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnBoot::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IBoot> _aidl_delegate;
};  // class IBootDelegator
}  // namespace boot
}  // namespace hal
}  // namespace rdk
}  // namespace com
