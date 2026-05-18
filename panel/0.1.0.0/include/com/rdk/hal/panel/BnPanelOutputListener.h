#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/panel/IPanelOutputListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class BnPanelOutputListener : public ::android::BnInterface<IPanelOutputListener> {
public:
  static constexpr uint32_t TRANSACTION_onPictureModeChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onVideoSourceChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_onVideoFormatChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_onVideoFrameRateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_onVideoResolutionChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_onRefreshRateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnPanelOutputListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnPanelOutputListener

class IPanelOutputListenerDelegator : public BnPanelOutputListener {
public:
  explicit IPanelOutputListenerDelegator(::android::sp<IPanelOutputListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onPictureModeChanged(const ::android::String16& pictureMode) override {
    return _aidl_delegate->onPictureModeChanged(pictureMode);
  }
  ::android::binder::Status onVideoSourceChanged(::com::rdk::hal::AVSource avSource) override {
    return _aidl_delegate->onVideoSourceChanged(avSource);
  }
  ::android::binder::Status onVideoFormatChanged(::com::rdk::hal::videodecoder::DynamicRange dynamicRange) override {
    return _aidl_delegate->onVideoFormatChanged(dynamicRange);
  }
  ::android::binder::Status onVideoFrameRateChanged(int32_t frameRateNumerator, int32_t frameRateDenominator) override {
    return _aidl_delegate->onVideoFrameRateChanged(frameRateNumerator, frameRateDenominator);
  }
  ::android::binder::Status onVideoResolutionChanged(int32_t width, int32_t height) override {
    return _aidl_delegate->onVideoResolutionChanged(width, height);
  }
  ::android::binder::Status onRefreshRateChanged(double refreshRateHz) override {
    return _aidl_delegate->onRefreshRateChanged(refreshRateHz);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnPanelOutputListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IPanelOutputListener> _aidl_delegate;
};  // class IPanelOutputListenerDelegator
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
