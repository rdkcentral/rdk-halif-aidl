#pragma once

#include <binder/IInterface.h>
#include <com/test/IFWManager.h>

namespace com {
namespace test {
class BnFWManager : public ::android::BnInterface<IFWManager> {
public:
  static constexpr uint32_t TRANSACTION_getFirmwareVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 400;
  static constexpr uint32_t TRANSACTION_getCurrentBootBank = ::android::IBinder::FIRST_CALL_TRANSACTION + 401;
  static constexpr uint32_t TRANSACTION_triggerFirmwareUpdateCheck = ::android::IBinder::FIRST_CALL_TRANSACTION + 402;
  static constexpr uint32_t TRANSACTION_getFirmwareUpdateState = ::android::IBinder::FIRST_CALL_TRANSACTION + 403;
  static constexpr uint32_t TRANSACTION_registerDeviceStateFirmwareUpdateStateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 404;
  explicit BnFWManager();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnFWManager

class IFWManagerDelegator : public BnFWManager {
public:
  explicit IFWManagerDelegator(::android::sp<IFWManager> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getFirmwareVersion(::android::String16* _aidl_return) override {
    return _aidl_delegate->getFirmwareVersion(_aidl_return);
  }
  ::android::binder::Status getCurrentBootBank(int32_t* _aidl_return) override {
    return _aidl_delegate->getCurrentBootBank(_aidl_return);
  }
  ::android::binder::Status triggerFirmwareUpdateCheck(bool* _aidl_return) override {
    return _aidl_delegate->triggerFirmwareUpdateCheck(_aidl_return);
  }
  ::android::binder::Status getFirmwareUpdateState(::com::test::FirmwareStatus* _aidl_return) override {
    return _aidl_delegate->getFirmwareUpdateState(_aidl_return);
  }
  ::android::binder::Status registerDeviceStateFirmwareUpdateStateChanged(const ::android::sp<::com::test::IFirmwareUpdateStateListener>& listener) override {
    return _aidl_delegate->registerDeviceStateFirmwareUpdateStateChanged(listener);
  }
private:
  ::android::sp<IFWManager> _aidl_delegate;
};  // class IFWManagerDelegator
}  // namespace test
}  // namespace com
