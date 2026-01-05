#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/panel/IFactoryPanel.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class BpFactoryPanel : public ::android::BpInterface<IFactoryPanel> {
public:
  explicit BpFactoryPanel(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpFactoryPanel() = default;
  ::android::binder::Status setFactoryPanelConfiguration(int32_t panelId, bool* _aidl_return) override;
  ::android::binder::Status getFactoryPanelConfiguration(int32_t* _aidl_return) override;
  ::android::binder::Status setFactoryWhiteBalanceCalibration(int32_t colorTemperature, const ::com::rdk::hal::panel::WhiteBalance2PointSettings& whiteBalance, ::com::rdk::hal::panel::IFactoryPanel::SaveTo saveTo, bool* _aidl_return) override;
  ::android::binder::Status getFactoryWhiteBalanceCalibration(int32_t colorTemperature, ::com::rdk::hal::panel::WhiteBalance2PointSettings* _aidl_return) override;
  ::android::binder::Status setFactoryGammaTable(int32_t colorTemperature, const ::std::vector<int32_t>& red, const ::std::vector<int32_t>& green, const ::std::vector<int32_t>& blue, ::com::rdk::hal::panel::IFactoryPanel::SaveTo saveTo, bool* _aidl_return) override;
  ::android::binder::Status getFactoryGammaTable(int32_t colorTemperature, ::std::vector<int32_t>* red, ::std::vector<int32_t>* green, ::std::vector<int32_t>* blue) override;
  ::android::binder::Status setFactoryPeakBrightness(int32_t dimmingLevel, int32_t nits, bool* _aidl_return) override;
  ::android::binder::Status getFactoryPeakBrightness(int32_t dimmingLevel, int32_t* _aidl_return) override;
  ::android::binder::Status setFactoryLocalDimming(const ::std::vector<::com::rdk::hal::panel::IFactoryPanel::LocalDimmingZone>& zones, int32_t durationMs, bool* _aidl_return) override;
  ::android::binder::Status setFactoryLocalDimmingTestMode(int32_t mode, int32_t durationMs, bool* _aidl_return) override;
  ::android::binder::Status setFactoryLocalDimmingPixelCompensation(bool enabled, bool* _aidl_return) override;
  ::android::binder::Status getFactoryLocalDimmingPixelCompensation(bool* _aidl_return) override;
  ::android::binder::Status getFactoryBacklightHealth(int32_t* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpFactoryPanel
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
