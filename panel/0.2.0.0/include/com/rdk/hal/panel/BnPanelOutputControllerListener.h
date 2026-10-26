#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/panel/IPanelOutputControllerListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class BnPanelOutputControllerListener : public ::android::BnInterface<IPanelOutputControllerListener> {
public:
  static constexpr uint32_t TRANSACTION_onPictureModeChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onPQParameterChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnPanelOutputControllerListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnPanelOutputControllerListener

class IPanelOutputControllerListenerDelegator : public BnPanelOutputControllerListener {
public:
  explicit IPanelOutputControllerListenerDelegator(::android::sp<IPanelOutputControllerListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onPictureModeChanged(const ::std::string& pictureMode) override {
    return _aidl_delegate->onPictureModeChanged(pictureMode);
  }
  ::android::binder::Status onPQParameterChanged(const ::std::string& pictureMode, const ::com::rdk::hal::panel::PanelSource& avSource, ::com::rdk::hal::videodecoder::DynamicRange dynamicRange, ::com::rdk::hal::panel::PQParameter pictureProperty, const ::com::rdk::hal::panel::PQParameterValue& picturePropertyValue) override {
    return _aidl_delegate->onPQParameterChanged(pictureMode, avSource, dynamicRange, pictureProperty, picturePropertyValue);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnPanelOutputControllerListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IPanelOutputControllerListener> _aidl_delegate;
};  // class IPanelOutputControllerListenerDelegator
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
