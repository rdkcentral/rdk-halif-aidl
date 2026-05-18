#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/panel/IFactoryPanel.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class BnFactoryPanel : public ::android::BnInterface<IFactoryPanel> {
public:
  static constexpr uint32_t TRANSACTION_setFactoryPanelConfiguration = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getFactoryPanelConfiguration = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_setFactoryWhiteBalanceCalibration = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getFactoryWhiteBalanceCalibration = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_setFactoryGammaTable = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_getFactoryGammaTable = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_setFactoryPeakBrightness = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_getFactoryPeakBrightness = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_setFactoryLocalDimming = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_setFactoryLocalDimmingTestMode = ::android::IBinder::FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_setFactoryLocalDimmingPixelCompensation = ::android::IBinder::FIRST_CALL_TRANSACTION + 10;
  static constexpr uint32_t TRANSACTION_getFactoryLocalDimmingPixelCompensation = ::android::IBinder::FIRST_CALL_TRANSACTION + 11;
  static constexpr uint32_t TRANSACTION_getFactoryBacklightHealth = ::android::IBinder::FIRST_CALL_TRANSACTION + 12;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnFactoryPanel();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnFactoryPanel

class IFactoryPanelDelegator : public BnFactoryPanel {
public:
  explicit IFactoryPanelDelegator(::android::sp<IFactoryPanel> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status setFactoryPanelConfiguration(int32_t panelId, bool* _aidl_return) override {
    return _aidl_delegate->setFactoryPanelConfiguration(panelId, _aidl_return);
  }
  ::android::binder::Status getFactoryPanelConfiguration(int32_t* _aidl_return) override {
    return _aidl_delegate->getFactoryPanelConfiguration(_aidl_return);
  }
  ::android::binder::Status setFactoryWhiteBalanceCalibration(int32_t colorTemperature, const ::com::rdk::hal::panel::WhiteBalance2PointSettings& whiteBalance, ::com::rdk::hal::panel::IFactoryPanel::SaveTo saveTo, bool* _aidl_return) override {
    return _aidl_delegate->setFactoryWhiteBalanceCalibration(colorTemperature, whiteBalance, saveTo, _aidl_return);
  }
  ::android::binder::Status getFactoryWhiteBalanceCalibration(int32_t colorTemperature, ::com::rdk::hal::panel::WhiteBalance2PointSettings* _aidl_return) override {
    return _aidl_delegate->getFactoryWhiteBalanceCalibration(colorTemperature, _aidl_return);
  }
  ::android::binder::Status setFactoryGammaTable(int32_t colorTemperature, const ::std::vector<int32_t>& red, const ::std::vector<int32_t>& green, const ::std::vector<int32_t>& blue, ::com::rdk::hal::panel::IFactoryPanel::SaveTo saveTo, bool* _aidl_return) override {
    return _aidl_delegate->setFactoryGammaTable(colorTemperature, red, green, blue, saveTo, _aidl_return);
  }
  ::android::binder::Status getFactoryGammaTable(int32_t colorTemperature, ::std::vector<int32_t>* red, ::std::vector<int32_t>* green, ::std::vector<int32_t>* blue) override {
    return _aidl_delegate->getFactoryGammaTable(colorTemperature, red, green, blue);
  }
  ::android::binder::Status setFactoryPeakBrightness(int32_t dimmingLevel, int32_t nits, bool* _aidl_return) override {
    return _aidl_delegate->setFactoryPeakBrightness(dimmingLevel, nits, _aidl_return);
  }
  ::android::binder::Status getFactoryPeakBrightness(int32_t dimmingLevel, int32_t* _aidl_return) override {
    return _aidl_delegate->getFactoryPeakBrightness(dimmingLevel, _aidl_return);
  }
  ::android::binder::Status setFactoryLocalDimming(const ::std::vector<::com::rdk::hal::panel::IFactoryPanel::LocalDimmingZone>& zones, int32_t durationMs, bool* _aidl_return) override {
    return _aidl_delegate->setFactoryLocalDimming(zones, durationMs, _aidl_return);
  }
  ::android::binder::Status setFactoryLocalDimmingTestMode(int32_t mode, int32_t durationMs, bool* _aidl_return) override {
    return _aidl_delegate->setFactoryLocalDimmingTestMode(mode, durationMs, _aidl_return);
  }
  ::android::binder::Status setFactoryLocalDimmingPixelCompensation(bool enabled, bool* _aidl_return) override {
    return _aidl_delegate->setFactoryLocalDimmingPixelCompensation(enabled, _aidl_return);
  }
  ::android::binder::Status getFactoryLocalDimmingPixelCompensation(bool* _aidl_return) override {
    return _aidl_delegate->getFactoryLocalDimmingPixelCompensation(_aidl_return);
  }
  ::android::binder::Status getFactoryBacklightHealth(int32_t* _aidl_return) override {
    return _aidl_delegate->getFactoryBacklightHealth(_aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnFactoryPanel::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IFactoryPanel> _aidl_delegate;
};  // class IFactoryPanelDelegator
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
