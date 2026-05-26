#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/avclock/IAVClockController.h>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
class BnAVClockController : public ::android::BnInterface<IAVClockController> {
public:
  static constexpr uint32_t TRANSACTION_start = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_stop = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_setClockMode = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getClockMode = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_notifyPCRSample = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_getCurrentClockTime = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_setPlaybackRate = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_getPlaybackRate = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAVClockController();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAVClockController

class IAVClockControllerDelegator : public BnAVClockController {
public:
  explicit IAVClockControllerDelegator(::android::sp<IAVClockController> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status start() override {
    return _aidl_delegate->start();
  }
  ::android::binder::Status stop() override {
    return _aidl_delegate->stop();
  }
  ::android::binder::Status setClockMode(::com::rdk::hal::avclock::ClockMode clockMode, bool* _aidl_return) override {
    return _aidl_delegate->setClockMode(clockMode, _aidl_return);
  }
  ::android::binder::Status getClockMode(::com::rdk::hal::avclock::ClockMode* _aidl_return) override {
    return _aidl_delegate->getClockMode(_aidl_return);
  }
  ::android::binder::Status notifyPCRSample(int64_t pcrTimeNs, int64_t sampleTimestampNs, bool* _aidl_return) override {
    return _aidl_delegate->notifyPCRSample(pcrTimeNs, sampleTimestampNs, _aidl_return);
  }
  ::android::binder::Status getCurrentClockTime(::std::optional<::com::rdk::hal::avclock::ClockTime>* _aidl_return) override {
    return _aidl_delegate->getCurrentClockTime(_aidl_return);
  }
  ::android::binder::Status setPlaybackRate(double rate, bool* _aidl_return) override {
    return _aidl_delegate->setPlaybackRate(rate, _aidl_return);
  }
  ::android::binder::Status getPlaybackRate(double* _aidl_return) override {
    return _aidl_delegate->getPlaybackRate(_aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAVClockController::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAVClockController> _aidl_delegate;
};  // class IAVClockControllerDelegator
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
