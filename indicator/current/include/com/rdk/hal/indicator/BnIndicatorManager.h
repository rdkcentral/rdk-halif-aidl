#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/indicator/IIndicatorManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace indicator {
class BnIndicatorManager : public ::android::BnInterface<IIndicatorManager> {
public:
  static constexpr uint32_t TRANSACTION_getIndicatorIds = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getIndicator = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnIndicatorManager();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnIndicatorManager

class IIndicatorManagerDelegator : public BnIndicatorManager {
public:
  explicit IIndicatorManagerDelegator(::android::sp<IIndicatorManager> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getIndicatorIds(::std::vector<::com::rdk::hal::indicator::IIndicator::Id>* _aidl_return) override {
    return _aidl_delegate->getIndicatorIds(_aidl_return);
  }
  ::android::binder::Status getIndicator(const ::com::rdk::hal::indicator::IIndicator::Id& indicatorId, ::android::sp<::com::rdk::hal::indicator::IIndicator>* _aidl_return) override {
    return _aidl_delegate->getIndicator(indicatorId, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnIndicatorManager::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IIndicatorManager> _aidl_delegate;
};  // class IIndicatorManagerDelegator
}  // namespace indicator
}  // namespace hal
}  // namespace rdk
}  // namespace com
