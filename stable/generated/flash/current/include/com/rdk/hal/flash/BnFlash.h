#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/flash/IFlash.h>

namespace com {
namespace rdk {
namespace hal {
namespace flash {
class BnFlash : public ::android::BnInterface<IFlash> {
public:
  static constexpr uint32_t TRANSACTION_flashImageFromFile = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnFlash();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnFlash

class IFlashDelegator : public BnFlash {
public:
  explicit IFlashDelegator(::android::sp<IFlash> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status flashImageFromFile(const ::std::string& filename, const ::android::sp<::com::rdk::hal::flash::IFlashListener>& listener, bool* _aidl_return) override {
    return _aidl_delegate->flashImageFromFile(filename, listener, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnFlash::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IFlash> _aidl_delegate;
};  // class IFlashDelegator
}  // namespace flash
}  // namespace hal
}  // namespace rdk
}  // namespace com
