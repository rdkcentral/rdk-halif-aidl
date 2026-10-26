#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/broadcast/ca/ICaSlot.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace ca {
class BnCaSlot : public ::android::BnInterface<ICaSlot> {
public:
  static constexpr uint32_t TRANSACTION_getId = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_setPower = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnCaSlot();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnCaSlot

class ICaSlotDelegator : public BnCaSlot {
public:
  explicit ICaSlotDelegator(::android::sp<ICaSlot> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getId(::com::rdk::hal::broadcast::ca::ICaSlot::Id* _aidl_return) override {
    return _aidl_delegate->getId(_aidl_return);
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::broadcast::ca::CaCapabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status setPower(bool enabled) override {
    return _aidl_delegate->setPower(enabled);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnCaSlot::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<ICaSlot> _aidl_delegate;
};  // class ICaSlotDelegator
}  // namespace ca
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
