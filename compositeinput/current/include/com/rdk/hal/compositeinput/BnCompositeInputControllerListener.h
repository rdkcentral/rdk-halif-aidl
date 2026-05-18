#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/compositeinput/ICompositeInputControllerListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
class BnCompositeInputControllerListener : public ::android::BnInterface<ICompositeInputControllerListener> {
public:
  static constexpr uint32_t TRANSACTION_onConnectionChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onSignalStatusChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_onVideoModeChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnCompositeInputControllerListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnCompositeInputControllerListener

class ICompositeInputControllerListenerDelegator : public BnCompositeInputControllerListener {
public:
  explicit ICompositeInputControllerListenerDelegator(::android::sp<ICompositeInputControllerListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onConnectionChanged(bool connected) override {
    return _aidl_delegate->onConnectionChanged(connected);
  }
  ::android::binder::Status onSignalStatusChanged(::com::rdk::hal::compositeinput::SignalStatus signalStatus) override {
    return _aidl_delegate->onSignalStatusChanged(signalStatus);
  }
  ::android::binder::Status onVideoModeChanged(const ::com::rdk::hal::compositeinput::VideoResolution& resolution) override {
    return _aidl_delegate->onVideoModeChanged(resolution);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnCompositeInputControllerListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<ICompositeInputControllerListener> _aidl_delegate;
};  // class ICompositeInputControllerListenerDelegator
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
