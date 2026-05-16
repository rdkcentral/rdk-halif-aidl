#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/indicator/IIndicator.h>

namespace com {
namespace rdk {
namespace hal {
namespace indicator {
class BnIndicator : public ::android::BnInterface<IIndicator> {
public:
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_set = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_get = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnIndicator();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnIndicator

class IIndicatorDelegator : public BnIndicator {
public:
  explicit IIndicatorDelegator(::android::sp<IIndicator> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getCapabilities(::com::rdk::hal::indicator::Capabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status set(const ::android::String16& state, bool* _aidl_return) override {
    return _aidl_delegate->set(state, _aidl_return);
  }
  ::android::binder::Status get(::android::String16* _aidl_return) override {
    return _aidl_delegate->get(_aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnIndicator::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IIndicator> _aidl_delegate;
};  // class IIndicatorDelegator
}  // namespace indicator
}  // namespace hal
}  // namespace rdk
}  // namespace com
