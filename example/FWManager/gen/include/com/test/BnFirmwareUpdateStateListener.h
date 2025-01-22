#pragma once

#include <binder/IInterface.h>
#include <com/test/IFirmwareUpdateStateListener.h>

namespace com {
namespace test {
class BnFirmwareUpdateStateListener : public ::android::BnInterface<IFirmwareUpdateStateListener> {
public:
  static constexpr uint32_t TRANSACTION_onFirmwareUpdateStateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  explicit BnFirmwareUpdateStateListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
};  // class BnFirmwareUpdateStateListener

class IFirmwareUpdateStateListenerDelegator : public BnFirmwareUpdateStateListener {
public:
  explicit IFirmwareUpdateStateListenerDelegator(::android::sp<IFirmwareUpdateStateListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onFirmwareUpdateStateChanged(const ::com::test::FirmwareStatus& status) override {
    return _aidl_delegate->onFirmwareUpdateStateChanged(status);
  }
private:
  ::android::sp<IFirmwareUpdateStateListener> _aidl_delegate;
};  // class IFirmwareUpdateStateListenerDelegator
}  // namespace test
}  // namespace com
