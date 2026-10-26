#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/broadcast/IBroadcastClientToken.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
class BnBroadcastClientToken : public ::android::BnInterface<IBroadcastClientToken> {
public:
  static constexpr uint32_t TRANSACTION_getWhoAmI = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnBroadcastClientToken();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnBroadcastClientToken

class IBroadcastClientTokenDelegator : public BnBroadcastClientToken {
public:
  explicit IBroadcastClientTokenDelegator(::android::sp<IBroadcastClientToken> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getWhoAmI(::std::string* _aidl_return) override {
    return _aidl_delegate->getWhoAmI(_aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnBroadcastClientToken::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IBroadcastClientToken> _aidl_delegate;
};  // class IBroadcastClientTokenDelegator
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
