#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/panel/IPanelOutput.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class BpPanelOutput : public ::android::BpInterface<IPanelOutput> {
public:
  explicit BpPanelOutput(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpPanelOutput() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::panel::Capabilities* _aidl_return) override;
  ::android::binder::Status getFactoryInterface(::android::sp<::com::rdk::hal::panel::IFactoryPanel>* _aidl_return) override;
  ::android::binder::Status setEnabled(bool enabled) override;
  ::android::binder::Status getEnabled(bool* _aidl_return) override;
  ::android::binder::Status setPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& configurations, bool* _aidl_return) override;
  ::android::binder::Status getPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>* returnedConfigurations, bool* _aidl_return) override;
  ::android::binder::Status getDefaultPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>* defaultConfigurations, bool* _aidl_return) override;
  ::android::binder::Status setPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>& configurations, bool* _aidl_return) override;
  ::android::binder::Status getPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>* returnedConfigurations, bool* _aidl_return) override;
  ::android::binder::Status getDefaultPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>* defaultConfigurations, bool* _aidl_return) override;
  ::android::binder::Status getPQParameterCapabilities(::com::rdk::hal::panel::PQParameter pqParameter, ::com::rdk::hal::panel::PQParameterCapabilities* _aidl_return) override;
  ::android::binder::Status setRefreshRate(double refreshRateHz, bool* _aidl_return) override;
  ::android::binder::Status getRefreshRate(double* _aidl_return) override;
  ::android::binder::Status setFrameRateMatching(bool enabled, bool* _aidl_return) override;
  ::android::binder::Status getFrameRateMatching(bool* _aidl_return) override;
  ::android::binder::Status setVideoSourceOverride(::com::rdk::hal::AVSource source) override;
  ::android::binder::Status getVideoSourceOverride(::com::rdk::hal::AVSource* _aidl_return) override;
  ::android::binder::Status getVideoSource(::com::rdk::hal::AVSource* _aidl_return) override;
  ::android::binder::Status getVideoFormat(::com::rdk::hal::videodecoder::DynamicRange* _aidl_return) override;
  ::android::binder::Status getVideoFrameRate(std::array<int32_t, 2>* _aidl_return) override;
  ::android::binder::Status getVideoResolution(std::array<int32_t, 2>* _aidl_return) override;
  ::android::binder::Status set2PointWhiteBalance(int32_t colorTemperature, const ::com::rdk::hal::panel::WhiteBalance2PointSettings& whiteBalance, bool* _aidl_return) override;
  ::android::binder::Status get2PointWhiteBalance(int32_t colorTemperature, ::com::rdk::hal::panel::WhiteBalance2PointSettings* _aidl_return) override;
  ::android::binder::Status setMultiPointWhiteBalance(int32_t colorTemperature, const ::com::rdk::hal::panel::WhiteBalanceMultiPointSettings& whiteBalance, bool* _aidl_return) override;
  ::android::binder::Status getMultiPointWhiteBalance(int32_t colorTemperature, ::com::rdk::hal::panel::WhiteBalanceMultiPointSettings* _aidl_return) override;
  ::android::binder::Status fadeDisplay(int32_t start, int32_t end, int32_t durationMs, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpPanelOutput
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
