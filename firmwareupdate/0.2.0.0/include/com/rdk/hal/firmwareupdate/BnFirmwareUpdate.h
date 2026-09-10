#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/firmwareupdate/IFirmwareUpdate.h>

namespace com {
namespace rdk {
namespace hal {
namespace firmwareupdate {
class BnFirmwareUpdate : public ::android::BnInterface<IFirmwareUpdate> {
public:
  static constexpr uint32_t TRANSACTION_updateFirmwareFromFile = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnFirmwareUpdate();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnFirmwareUpdate

class IFirmwareUpdateDelegator : public BnFirmwareUpdate {
public:
  explicit IFirmwareUpdateDelegator(::android::sp<IFirmwareUpdate> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status updateFirmwareFromFile(const ::std::string& filename, const ::android::sp<::com::rdk::hal::firmwareupdate::IFirmwareUpdateListener>& listener, bool* _aidl_return) override {
    return _aidl_delegate->updateFirmwareFromFile(filename, listener, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnFirmwareUpdate::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IFirmwareUpdate> _aidl_delegate;
};  // class IFirmwareUpdateDelegator
}  // namespace firmwareupdate
}  // namespace hal
}  // namespace rdk
}  // namespace com
