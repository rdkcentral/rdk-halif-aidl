#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/panel/IPanelOutputController.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class BpPanelOutputController : public ::android::BpInterface<IPanelOutputController> {
public:
  explicit BpPanelOutputController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpPanelOutputController() = default;
  ::android::binder::Status start(bool* _aidl_return) override;
  ::android::binder::Status getState(::com::rdk::hal::panel::State* _aidl_return) override;
  ::android::binder::Status stop(bool* _aidl_return) override;
  ::android::binder::Status setEnabled(bool enabled) override;
  ::android::binder::Status getEnabled(bool* _aidl_return) override;
  ::android::binder::Status setPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& configurations, bool* _aidl_return) override;
  ::android::binder::Status getPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>* returnedConfigurations, bool* _aidl_return) override;
  ::android::binder::Status getDefaultPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>* defaultConfigurations, bool* _aidl_return) override;
  ::android::binder::Status setPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>& configurations, ::com::rdk::hal::panel::ErrorCode* _aidl_return) override;
  ::android::binder::Status getPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterSelector>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>* returnedConfigurations, bool* _aidl_return) override;
  ::android::binder::Status getDefaultPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterSelector>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>* defaultConfigurations, bool* _aidl_return) override;
  ::android::binder::Status getPQParameterCapabilities(::com::rdk::hal::panel::PQParameter pqParameter, ::com::rdk::hal::panel::PQParameterCapabilities* _aidl_return) override;
  ::android::binder::Status setRefreshRate(double refreshRateHz, bool* _aidl_return) override;
  ::android::binder::Status getRefreshRate(double* _aidl_return) override;
  ::android::binder::Status setFrameRateMatching(bool enabled, bool* _aidl_return) override;
  ::android::binder::Status getFrameRateMatching(bool* _aidl_return) override;
  ::android::binder::Status setVideoSourceOverride(const ::com::rdk::hal::panel::PanelSource& source) override;
  ::android::binder::Status getVideoSourceOverride(::com::rdk::hal::panel::PanelSource* _aidl_return) override;
  ::android::binder::Status getVideoSource(::com::rdk::hal::panel::PanelSource* _aidl_return) override;
  ::android::binder::Status getDynamicRange(::com::rdk::hal::videodecoder::DynamicRange* _aidl_return) override;
  ::android::binder::Status getVideoFrameRate(std::array<int32_t, 2>* _aidl_return) override;
  ::android::binder::Status getVideoResolution(std::array<int32_t, 2>* _aidl_return) override;
  ::android::binder::Status enableCalibrationMode(bool enabled, bool* _aidl_return) override;
  ::android::binder::Status getCalibrationMode(bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpPanelOutputController
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
