#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/avclock/IAVClockControllerListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
class BnAVClockControllerListener : public ::android::BnInterface<IAVClockControllerListener> {
public:
  static constexpr uint32_t TRANSACTION_onStateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAVClockControllerListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAVClockControllerListener

class IAVClockControllerListenerDelegator : public BnAVClockControllerListener {
public:
  explicit IAVClockControllerListenerDelegator(::android::sp<IAVClockControllerListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onStateChanged(::com::rdk::hal::State oldState, ::com::rdk::hal::State newState) override {
    return _aidl_delegate->onStateChanged(oldState, newState);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAVClockControllerListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAVClockControllerListener> _aidl_delegate;
};  // class IAVClockControllerListenerDelegator
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
