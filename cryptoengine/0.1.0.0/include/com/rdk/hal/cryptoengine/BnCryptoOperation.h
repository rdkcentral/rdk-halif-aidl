#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/cryptoengine/ICryptoOperation.h>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
class BnCryptoOperation : public ::android::BnInterface<ICryptoOperation> {
public:
  static constexpr uint32_t TRANSACTION_update = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_finish = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_abort = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnCryptoOperation();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnCryptoOperation

class ICryptoOperationDelegator : public BnCryptoOperation {
public:
  explicit ICryptoOperationDelegator(::android::sp<ICryptoOperation> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status update(const ::std::vector<uint8_t>& input, ::std::vector<uint8_t>* _aidl_return) override {
    return _aidl_delegate->update(input, _aidl_return);
  }
  ::android::binder::Status finish(const ::std::optional<::std::vector<uint8_t>>& input, ::std::vector<uint8_t>* _aidl_return) override {
    return _aidl_delegate->finish(input, _aidl_return);
  }
  ::android::binder::Status abort() override {
    return _aidl_delegate->abort();
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnCryptoOperation::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<ICryptoOperation> _aidl_delegate;
};  // class ICryptoOperationDelegator
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
