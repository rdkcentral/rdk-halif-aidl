#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/broadcast/frontend/ILnbController.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class BnLnbController : public ::android::BnInterface<ILnbController> {
public:
  static constexpr uint32_t TRANSACTION_setVoltage = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_setTone = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_isOverloaded = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_sendDiseqc = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnLnbController();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnLnbController

class ILnbControllerDelegator : public BnLnbController {
public:
  explicit ILnbControllerDelegator(::android::sp<ILnbController> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status setVoltage(::com::rdk::hal::broadcast::frontend::LnbVoltage voltage) override {
    return _aidl_delegate->setVoltage(voltage);
  }
  ::android::binder::Status setTone(::com::rdk::hal::broadcast::frontend::LnbTone tone) override {
    return _aidl_delegate->setTone(tone);
  }
  ::android::binder::Status isOverloaded(bool* _aidl_return) override {
    return _aidl_delegate->isOverloaded(_aidl_return);
  }
  ::android::binder::Status sendDiseqc(const ::std::vector<uint8_t>& command) override {
    return _aidl_delegate->sendDiseqc(command);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnLnbController::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<ILnbController> _aidl_delegate;
};  // class ILnbControllerDelegator
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
