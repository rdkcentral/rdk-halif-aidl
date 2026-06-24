#pragma once

#include <binder/IInterface.h>
#include <com/demo/hal/dashboard/IDashboard.h>

namespace com {
namespace demo {
namespace hal {
namespace dashboard {
class BnDashboard : public ::android::BnInterface<IDashboard> {
public:
  static constexpr uint32_t TRANSACTION_getDashboardInfo = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getActiveWarnings = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_resetDashboard = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnDashboard();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnDashboard

class IDashboardDelegator : public BnDashboard {
public:
  explicit IDashboardDelegator(::android::sp<IDashboard> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getDashboardInfo(::com::demo::hal::dashboard::DashboardInfo* _aidl_return) override {
    return _aidl_delegate->getDashboardInfo(_aidl_return);
  }
  ::android::binder::Status getActiveWarnings(::std::vector<::com::demo::hal::dashboard::DashboardWarning>* _aidl_return) override {
    return _aidl_delegate->getActiveWarnings(_aidl_return);
  }
  ::android::binder::Status resetDashboard() override {
    return _aidl_delegate->resetDashboard();
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnDashboard::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IDashboard> _aidl_delegate;
};  // class IDashboardDelegator
}  // namespace dashboard
}  // namespace hal
}  // namespace demo
}  // namespace com
