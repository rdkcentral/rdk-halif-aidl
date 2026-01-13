#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/flash/IFlashListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace flash {
class BnFlashListener : public ::android::BnInterface<IFlashListener> {
public:
  static constexpr uint32_t TRANSACTION_onProgress = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onCompleted = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnFlashListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnFlashListener

class IFlashListenerDelegator : public BnFlashListener {
public:
  explicit IFlashListenerDelegator(::android::sp<IFlashListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onProgress(int32_t percentComplete) override {
    return _aidl_delegate->onProgress(percentComplete);
  }
  ::android::binder::Status onCompleted(::com::rdk::hal::flash::FlashImageResult result, const ::std::string& report) override {
    return _aidl_delegate->onCompleted(result, report);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnFlashListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IFlashListener> _aidl_delegate;
};  // class IFlashListenerDelegator
}  // namespace flash
}  // namespace hal
}  // namespace rdk
}  // namespace com
