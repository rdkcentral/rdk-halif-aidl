#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/panel/IPanelOutputController.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class BnPanelOutputController : public ::android::BnInterface<IPanelOutputController> {
public:
  static constexpr uint32_t TRANSACTION_start = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getState = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_stop = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_setEnabled = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getEnabled = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_setPictureModes = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getPictureModes = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_getDefaultPictureModes = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_setPQParameters = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_getPQParameters = ::android::IBinder::FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_getDefaultPQParameters = ::android::IBinder::FIRST_CALL_TRANSACTION + 10;
  static constexpr uint32_t TRANSACTION_getPQParameterCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 11;
  static constexpr uint32_t TRANSACTION_setRefreshRate = ::android::IBinder::FIRST_CALL_TRANSACTION + 12;
  static constexpr uint32_t TRANSACTION_getRefreshRate = ::android::IBinder::FIRST_CALL_TRANSACTION + 13;
  static constexpr uint32_t TRANSACTION_setFrameRateMatching = ::android::IBinder::FIRST_CALL_TRANSACTION + 14;
  static constexpr uint32_t TRANSACTION_getFrameRateMatching = ::android::IBinder::FIRST_CALL_TRANSACTION + 15;
  static constexpr uint32_t TRANSACTION_setVideoSourceOverride = ::android::IBinder::FIRST_CALL_TRANSACTION + 16;
  static constexpr uint32_t TRANSACTION_getVideoSourceOverride = ::android::IBinder::FIRST_CALL_TRANSACTION + 17;
  static constexpr uint32_t TRANSACTION_getVideoSource = ::android::IBinder::FIRST_CALL_TRANSACTION + 18;
  static constexpr uint32_t TRANSACTION_getDynamicRange = ::android::IBinder::FIRST_CALL_TRANSACTION + 19;
  static constexpr uint32_t TRANSACTION_getVideoFrameRate = ::android::IBinder::FIRST_CALL_TRANSACTION + 20;
  static constexpr uint32_t TRANSACTION_getVideoResolution = ::android::IBinder::FIRST_CALL_TRANSACTION + 21;
  static constexpr uint32_t TRANSACTION_enableCalibrationMode = ::android::IBinder::FIRST_CALL_TRANSACTION + 22;
  static constexpr uint32_t TRANSACTION_getCalibrationMode = ::android::IBinder::FIRST_CALL_TRANSACTION + 23;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnPanelOutputController();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnPanelOutputController

class IPanelOutputControllerDelegator : public BnPanelOutputController {
public:
  explicit IPanelOutputControllerDelegator(::android::sp<IPanelOutputController> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status start(bool* _aidl_return) override {
    return _aidl_delegate->start(_aidl_return);
  }
  ::android::binder::Status getState(::com::rdk::hal::panel::State* _aidl_return) override {
    return _aidl_delegate->getState(_aidl_return);
  }
  ::android::binder::Status stop(bool* _aidl_return) override {
    return _aidl_delegate->stop(_aidl_return);
  }
  ::android::binder::Status setEnabled(bool enabled) override {
    return _aidl_delegate->setEnabled(enabled);
  }
  ::android::binder::Status getEnabled(bool* _aidl_return) override {
    return _aidl_delegate->getEnabled(_aidl_return);
  }
  ::android::binder::Status setPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& configurations, bool* _aidl_return) override {
    return _aidl_delegate->setPictureModes(configurations, _aidl_return);
  }
  ::android::binder::Status getPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>* returnedConfigurations, bool* _aidl_return) override {
    return _aidl_delegate->getPictureModes(requestedConfigurations, returnedConfigurations, _aidl_return);
  }
  ::android::binder::Status getDefaultPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>* defaultConfigurations, bool* _aidl_return) override {
    return _aidl_delegate->getDefaultPictureModes(requestedConfigurations, defaultConfigurations, _aidl_return);
  }
  ::android::binder::Status setPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>& configurations, ::com::rdk::hal::panel::ErrorCode* _aidl_return) override {
    return _aidl_delegate->setPQParameters(configurations, _aidl_return);
  }
  ::android::binder::Status getPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterSelector>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>* returnedConfigurations, bool* _aidl_return) override {
    return _aidl_delegate->getPQParameters(requestedConfigurations, returnedConfigurations, _aidl_return);
  }
  ::android::binder::Status getDefaultPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterSelector>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>* defaultConfigurations, bool* _aidl_return) override {
    return _aidl_delegate->getDefaultPQParameters(requestedConfigurations, defaultConfigurations, _aidl_return);
  }
  ::android::binder::Status getPQParameterCapabilities(::com::rdk::hal::panel::PQParameter pqParameter, ::com::rdk::hal::panel::PQParameterCapabilities* _aidl_return) override {
    return _aidl_delegate->getPQParameterCapabilities(pqParameter, _aidl_return);
  }
  ::android::binder::Status setRefreshRate(double refreshRateHz, bool* _aidl_return) override {
    return _aidl_delegate->setRefreshRate(refreshRateHz, _aidl_return);
  }
  ::android::binder::Status getRefreshRate(double* _aidl_return) override {
    return _aidl_delegate->getRefreshRate(_aidl_return);
  }
  ::android::binder::Status setFrameRateMatching(bool enabled, bool* _aidl_return) override {
    return _aidl_delegate->setFrameRateMatching(enabled, _aidl_return);
  }
  ::android::binder::Status getFrameRateMatching(bool* _aidl_return) override {
    return _aidl_delegate->getFrameRateMatching(_aidl_return);
  }
  ::android::binder::Status setVideoSourceOverride(const ::com::rdk::hal::panel::PanelSource& source) override {
    return _aidl_delegate->setVideoSourceOverride(source);
  }
  ::android::binder::Status getVideoSourceOverride(::com::rdk::hal::panel::PanelSource* _aidl_return) override {
    return _aidl_delegate->getVideoSourceOverride(_aidl_return);
  }
  ::android::binder::Status getVideoSource(::com::rdk::hal::panel::PanelSource* _aidl_return) override {
    return _aidl_delegate->getVideoSource(_aidl_return);
  }
  ::android::binder::Status getDynamicRange(::com::rdk::hal::videodecoder::DynamicRange* _aidl_return) override {
    return _aidl_delegate->getDynamicRange(_aidl_return);
  }
  ::android::binder::Status getVideoFrameRate(std::array<int32_t, 2>* _aidl_return) override {
    return _aidl_delegate->getVideoFrameRate(_aidl_return);
  }
  ::android::binder::Status getVideoResolution(std::array<int32_t, 2>* _aidl_return) override {
    return _aidl_delegate->getVideoResolution(_aidl_return);
  }
  ::android::binder::Status enableCalibrationMode(bool enabled, bool* _aidl_return) override {
    return _aidl_delegate->enableCalibrationMode(enabled, _aidl_return);
  }
  ::android::binder::Status getCalibrationMode(bool* _aidl_return) override {
    return _aidl_delegate->getCalibrationMode(_aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnPanelOutputController::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IPanelOutputController> _aidl_delegate;
};  // class IPanelOutputControllerDelegator
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
