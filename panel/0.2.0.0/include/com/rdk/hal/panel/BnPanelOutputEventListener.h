#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/panel/IPanelOutputEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class BnPanelOutputEventListener : public ::android::BnInterface<IPanelOutputEventListener> {
public:
  static constexpr uint32_t TRANSACTION_onVideoSourceChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onDynamicRangeChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_onVideoFrameRateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_onVideoResolutionChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_onRefreshRateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_onStateChanged = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnPanelOutputEventListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnPanelOutputEventListener

class IPanelOutputEventListenerDelegator : public BnPanelOutputEventListener {
public:
  explicit IPanelOutputEventListenerDelegator(::android::sp<IPanelOutputEventListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onVideoSourceChanged(const ::com::rdk::hal::panel::PanelSource& avSource) override {
    return _aidl_delegate->onVideoSourceChanged(avSource);
  }
  ::android::binder::Status onDynamicRangeChanged(::com::rdk::hal::videodecoder::DynamicRange dynamicRange) override {
    return _aidl_delegate->onDynamicRangeChanged(dynamicRange);
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
  ::android::binder::Status onStateChanged(::com::rdk::hal::panel::State oldState, ::com::rdk::hal::panel::State newState) override {
    return _aidl_delegate->onStateChanged(oldState, newState);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnPanelOutputEventListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IPanelOutputEventListener> _aidl_delegate;
};  // class IPanelOutputEventListenerDelegator
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
