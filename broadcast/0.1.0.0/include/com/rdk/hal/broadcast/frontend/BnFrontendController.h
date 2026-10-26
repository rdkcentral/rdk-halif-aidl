#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/broadcast/frontend/IFrontendController.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class BnFrontendController : public ::android::BnInterface<IFrontendController> {
public:
  static constexpr uint32_t TRANSACTION_tune = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_stopTune = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getTuneStatus = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getSignalInfo = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnFrontendController();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnFrontendController

class IFrontendControllerDelegator : public BnFrontendController {
public:
  explicit IFrontendControllerDelegator(::android::sp<IFrontendController> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status tune(const ::com::rdk::hal::broadcast::frontend::TuneParameters& tuneParams) override {
    return _aidl_delegate->tune(tuneParams);
  }
  ::android::binder::Status stopTune() override {
    return _aidl_delegate->stopTune();
  }
  ::android::binder::Status getTuneStatus(::com::rdk::hal::broadcast::frontend::TuneStatus* _aidl_return) override {
    return _aidl_delegate->getTuneStatus(_aidl_return);
  }
  ::android::binder::Status getSignalInfo(const ::std::vector<::com::rdk::hal::broadcast::frontend::SignalInfoProperty>& properties, ::std::vector<::com::rdk::hal::broadcast::frontend::IFrontendController::SignalInfoReturn>* _aidl_return) override {
    return _aidl_delegate->getSignalInfo(properties, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnFrontendController::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IFrontendController> _aidl_delegate;
};  // class IFrontendControllerDelegator
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
