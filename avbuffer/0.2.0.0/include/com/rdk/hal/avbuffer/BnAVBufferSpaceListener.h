#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/avbuffer/IAVBufferSpaceListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace avbuffer {
class BnAVBufferSpaceListener : public ::android::BnInterface<IAVBufferSpaceListener> {
public:
  static constexpr uint32_t TRANSACTION_onSpaceAvailable = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAVBufferSpaceListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAVBufferSpaceListener

class IAVBufferSpaceListenerDelegator : public BnAVBufferSpaceListener {
public:
  explicit IAVBufferSpaceListenerDelegator(::android::sp<IAVBufferSpaceListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onSpaceAvailable() override {
    return _aidl_delegate->onSpaceAvailable();
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAVBufferSpaceListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAVBufferSpaceListener> _aidl_delegate;
};  // class IAVBufferSpaceListenerDelegator
}  // namespace avbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
