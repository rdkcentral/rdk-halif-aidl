#pragma once

#include <array>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/AVSource.h>
#include <com/rdk/hal/panel/Capabilities.h>
#include <com/rdk/hal/panel/IFactoryPanel.h>
#include <com/rdk/hal/panel/PQParameter.h>
#include <com/rdk/hal/panel/PQParameterCapabilities.h>
#include <com/rdk/hal/panel/PQParameterConfiguration.h>
#include <com/rdk/hal/panel/PictureModeConfiguration.h>
#include <com/rdk/hal/panel/WhiteBalance2PointSettings.h>
#include <com/rdk/hal/panel/WhiteBalanceMultiPointSettings.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class IPanelOutput : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PanelOutput)
  static const int32_t VERSION = 1;
  const std::string HASH = "cdc73f570c9b30e5c89acdbde61c0f2c8312ef91";
  static constexpr char* HASHVALUE = "cdc73f570c9b30e5c89acdbde61c0f2c8312ef91";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::panel::Capabilities* _aidl_return) = 0;
  virtual ::android::binder::Status getFactoryInterface(::android::sp<::com::rdk::hal::panel::IFactoryPanel>* _aidl_return) = 0;
  virtual ::android::binder::Status setEnabled(bool enabled) = 0;
  virtual ::android::binder::Status getEnabled(bool* _aidl_return) = 0;
  virtual ::android::binder::Status setPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& configurations, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>* returnedConfigurations, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getDefaultPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>* defaultConfigurations, bool* _aidl_return) = 0;
  virtual ::android::binder::Status setPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>& configurations, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>* returnedConfigurations, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getDefaultPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>* defaultConfigurations, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getPQParameterCapabilities(::com::rdk::hal::panel::PQParameter pqParameter, ::com::rdk::hal::panel::PQParameterCapabilities* _aidl_return) = 0;
  virtual ::android::binder::Status setRefreshRate(double refreshRateHz, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getRefreshRate(double* _aidl_return) = 0;
  virtual ::android::binder::Status setFrameRateMatching(bool enabled, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getFrameRateMatching(bool* _aidl_return) = 0;
  virtual ::android::binder::Status setVideoSourceOverride(::com::rdk::hal::AVSource source) = 0;
  virtual ::android::binder::Status getVideoSourceOverride(::com::rdk::hal::AVSource* _aidl_return) = 0;
  virtual ::android::binder::Status getVideoSource(::com::rdk::hal::AVSource* _aidl_return) = 0;
  virtual ::android::binder::Status getVideoFormat(::com::rdk::hal::videodecoder::DynamicRange* _aidl_return) = 0;
  virtual ::android::binder::Status getVideoFrameRate(std::array<int32_t, 2>* _aidl_return) = 0;
  virtual ::android::binder::Status getVideoResolution(std::array<int32_t, 2>* _aidl_return) = 0;
  virtual ::android::binder::Status set2PointWhiteBalance(int32_t colorTemperature, const ::com::rdk::hal::panel::WhiteBalance2PointSettings& whiteBalance, bool* _aidl_return) = 0;
  virtual ::android::binder::Status get2PointWhiteBalance(int32_t colorTemperature, ::com::rdk::hal::panel::WhiteBalance2PointSettings* _aidl_return) = 0;
  virtual ::android::binder::Status setMultiPointWhiteBalance(int32_t colorTemperature, const ::com::rdk::hal::panel::WhiteBalanceMultiPointSettings& whiteBalance, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getMultiPointWhiteBalance(int32_t colorTemperature, ::com::rdk::hal::panel::WhiteBalanceMultiPointSettings* _aidl_return) = 0;
  virtual ::android::binder::Status fadeDisplay(int32_t start, int32_t end, int32_t durationMs, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IPanelOutput

class IPanelOutputDefault : public IPanelOutput {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::panel::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getFactoryInterface(::android::sp<::com::rdk::hal::panel::IFactoryPanel>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setEnabled(bool /*enabled*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getEnabled(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& /*configurations*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& /*requestedConfigurations*/, ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>* /*returnedConfigurations*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getDefaultPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& /*requestedConfigurations*/, ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>* /*defaultConfigurations*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>& /*configurations*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>& /*requestedConfigurations*/, ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>* /*returnedConfigurations*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getDefaultPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>& /*requestedConfigurations*/, ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>* /*defaultConfigurations*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPQParameterCapabilities(::com::rdk::hal::panel::PQParameter /*pqParameter*/, ::com::rdk::hal::panel::PQParameterCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setRefreshRate(double /*refreshRateHz*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getRefreshRate(double* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setFrameRateMatching(bool /*enabled*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getFrameRateMatching(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setVideoSourceOverride(::com::rdk::hal::AVSource /*source*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoSourceOverride(::com::rdk::hal::AVSource* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoSource(::com::rdk::hal::AVSource* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoFormat(::com::rdk::hal::videodecoder::DynamicRange* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoFrameRate(std::array<int32_t, 2>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoResolution(std::array<int32_t, 2>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status set2PointWhiteBalance(int32_t /*colorTemperature*/, const ::com::rdk::hal::panel::WhiteBalance2PointSettings& /*whiteBalance*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status get2PointWhiteBalance(int32_t /*colorTemperature*/, ::com::rdk::hal::panel::WhiteBalance2PointSettings* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setMultiPointWhiteBalance(int32_t /*colorTemperature*/, const ::com::rdk::hal::panel::WhiteBalanceMultiPointSettings& /*whiteBalance*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getMultiPointWhiteBalance(int32_t /*colorTemperature*/, ::com::rdk::hal::panel::WhiteBalanceMultiPointSettings* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status fadeDisplay(int32_t /*start*/, int32_t /*end*/, int32_t /*durationMs*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IPanelOutputDefault
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
