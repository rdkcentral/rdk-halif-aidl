#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/deepsleep/IDeepSleep.h>

namespace com {
namespace rdk {
namespace hal {
namespace deepsleep {
class BnDeepSleep : public ::android::BnInterface<IDeepSleep> {
public:
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_enterDeepSleep = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_setWakeUpTimer = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getWakeUpTimer = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnDeepSleep();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnDeepSleep

class IDeepSleepDelegator : public BnDeepSleep {
public:
  explicit IDeepSleepDelegator(::android::sp<IDeepSleep> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getCapabilities(::com::rdk::hal::deepsleep::Capabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status enterDeepSleep(const ::std::vector<::com::rdk::hal::deepsleep::WakeUpTrigger>& triggersToWakeUpon, ::std::vector<::com::rdk::hal::deepsleep::WakeUpTrigger>* wokeUpByTriggers, ::std::optional<::com::rdk::hal::deepsleep::KeyCode>* keyCode, bool* _aidl_return) override {
    return _aidl_delegate->enterDeepSleep(triggersToWakeUpon, wokeUpByTriggers, keyCode, _aidl_return);
  }
  ::android::binder::Status setWakeUpTimer(int32_t seconds, bool* _aidl_return) override {
    return _aidl_delegate->setWakeUpTimer(seconds, _aidl_return);
  }
  ::android::binder::Status getWakeUpTimer(int32_t* _aidl_return) override {
    return _aidl_delegate->getWakeUpTimer(_aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnDeepSleep::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IDeepSleep> _aidl_delegate;
};  // class IDeepSleepDelegator
}  // namespace deepsleep
}  // namespace hal
}  // namespace rdk
}  // namespace com
