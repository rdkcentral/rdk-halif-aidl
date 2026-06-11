#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/bootreason/IBootReason.h>

namespace com {
namespace rdk {
namespace hal {
namespace bootreason {
class BnBootReason : public ::android::BnInterface<IBootReason> {
public:
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getBootCause = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_setBootCause = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_reboot = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getPowerSource = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnBootReason();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnBootReason

class IBootReasonDelegator : public BnBootReason {
public:
  explicit IBootReasonDelegator(::android::sp<IBootReason> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getCapabilities(::com::rdk::hal::bootreason::Capabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status getBootCause(::com::rdk::hal::bootreason::BootCause* _aidl_return) override {
    return _aidl_delegate->getBootCause(_aidl_return);
  }
  ::android::binder::Status setBootCause(::com::rdk::hal::bootreason::BootCause cause, const ::android::String16& reasonString) override {
    return _aidl_delegate->setBootCause(cause, reasonString);
  }
  ::android::binder::Status reboot(::com::rdk::hal::bootreason::ResetType resetType, const ::android::String16& reasonString) override {
    return _aidl_delegate->reboot(resetType, reasonString);
  }
  ::android::binder::Status getPowerSource(::com::rdk::hal::bootreason::PowerSource* _aidl_return) override {
    return _aidl_delegate->getPowerSource(_aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnBootReason::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IBootReason> _aidl_delegate;
};  // class IBootReasonDelegator
}  // namespace bootreason
}  // namespace hal
}  // namespace rdk
}  // namespace com
