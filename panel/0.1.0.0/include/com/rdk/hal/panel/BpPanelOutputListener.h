#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/panel/IPanelOutputListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class BpPanelOutputListener : public ::android::BpInterface<IPanelOutputListener> {
public:
  explicit BpPanelOutputListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpPanelOutputListener() = default;
  ::android::binder::Status onPictureModeChanged(const ::android::String16& pictureMode) override;
  ::android::binder::Status onVideoSourceChanged(::com::rdk::hal::AVSource avSource) override;
  ::android::binder::Status onVideoFormatChanged(::com::rdk::hal::videodecoder::DynamicRange dynamicRange) override;
  ::android::binder::Status onVideoFrameRateChanged(int32_t frameRateNumerator, int32_t frameRateDenominator) override;
  ::android::binder::Status onVideoResolutionChanged(int32_t width, int32_t height) override;
  ::android::binder::Status onRefreshRateChanged(double refreshRateHz) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpPanelOutputListener
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
