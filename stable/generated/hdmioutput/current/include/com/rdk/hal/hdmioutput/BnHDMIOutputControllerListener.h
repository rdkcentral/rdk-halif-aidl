#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/hdmioutput/IHDMIOutputControllerListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
class BnHDMIOutputControllerListener : public ::android::BnInterface<IHDMIOutputControllerListener> {
public:
  static constexpr uint32_t TRANSACTION_onHotPlugDetectStateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onFrameRateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_onHDCPStatusChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_onEDID = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnHDMIOutputControllerListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnHDMIOutputControllerListener

class IHDMIOutputControllerListenerDelegator : public BnHDMIOutputControllerListener {
public:
  explicit IHDMIOutputControllerListenerDelegator(::android::sp<IHDMIOutputControllerListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onHotPlugDetectStateChanged(bool state) override {
    return _aidl_delegate->onHotPlugDetectStateChanged(state);
  }
  ::android::binder::Status onFrameRateChanged() override {
    return _aidl_delegate->onFrameRateChanged();
  }
  ::android::binder::Status onHDCPStatusChanged(::com::rdk::hal::hdmioutput::HDCPStatus hdcpStatus, ::com::rdk::hal::hdmioutput::HDCPProtocolVersion hdcpProtocolVersion) override {
    return _aidl_delegate->onHDCPStatusChanged(hdcpStatus, hdcpProtocolVersion);
  }
  ::android::binder::Status onEDID(const ::std::vector<uint8_t>& edid) override {
    return _aidl_delegate->onEDID(edid);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnHDMIOutputControllerListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IHDMIOutputControllerListener> _aidl_delegate;
};  // class IHDMIOutputControllerListenerDelegator
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
