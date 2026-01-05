#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/hdmiinput/IHDMIInputControllerListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
class BnHDMIInputControllerListener : public ::android::BnInterface<IHDMIInputControllerListener> {
public:
  static constexpr uint32_t TRANSACTION_onConnectionStateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onSignalStateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_onVideoFormatChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_onVRRChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_onAVIInfoFrame = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_onAudioInfoFrame = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_onSPDInfoFrame = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_onDRMInfoFrame = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_onVendorSpecificInfoFrame = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_onHDCPStatusChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnHDMIInputControllerListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnHDMIInputControllerListener

class IHDMIInputControllerListenerDelegator : public BnHDMIInputControllerListener {
public:
  explicit IHDMIInputControllerListenerDelegator(::android::sp<IHDMIInputControllerListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onConnectionStateChanged(bool connectionState) override {
    return _aidl_delegate->onConnectionStateChanged(connectionState);
  }
  ::android::binder::Status onSignalStateChanged(::com::rdk::hal::hdmiinput::SignalState signalState) override {
    return _aidl_delegate->onSignalStateChanged(signalState);
  }
  ::android::binder::Status onVideoFormatChanged(::com::rdk::hal::hdmiinput::VIC vic) override {
    return _aidl_delegate->onVideoFormatChanged(vic);
  }
  ::android::binder::Status onVRRChanged(bool vrrActive, bool M_CONST, bool fastVActive, double frameRate) override {
    return _aidl_delegate->onVRRChanged(vrrActive, M_CONST, fastVActive, frameRate);
  }
  ::android::binder::Status onAVIInfoFrame(const ::std::vector<uint8_t>& data) override {
    return _aidl_delegate->onAVIInfoFrame(data);
  }
  ::android::binder::Status onAudioInfoFrame(const ::std::vector<uint8_t>& data) override {
    return _aidl_delegate->onAudioInfoFrame(data);
  }
  ::android::binder::Status onSPDInfoFrame(const ::std::vector<uint8_t>& data) override {
    return _aidl_delegate->onSPDInfoFrame(data);
  }
  ::android::binder::Status onDRMInfoFrame(const ::std::vector<uint8_t>& data) override {
    return _aidl_delegate->onDRMInfoFrame(data);
  }
  ::android::binder::Status onVendorSpecificInfoFrame(const ::std::vector<uint8_t>& data) override {
    return _aidl_delegate->onVendorSpecificInfoFrame(data);
  }
  ::android::binder::Status onHDCPStatusChanged(::com::rdk::hal::hdmiinput::HDCPStatus hdcpStatus, ::com::rdk::hal::hdmiinput::HDCPProtocolVersion hdcpProtocolVersion) override {
    return _aidl_delegate->onHDCPStatusChanged(hdcpStatus, hdcpProtocolVersion);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnHDMIInputControllerListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IHDMIInputControllerListener> _aidl_delegate;
};  // class IHDMIInputControllerListenerDelegator
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
