#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/panel/IPanelOutputEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class BpPanelOutputEventListener : public ::android::BpInterface<IPanelOutputEventListener> {
public:
  explicit BpPanelOutputEventListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpPanelOutputEventListener() = default;
  ::android::binder::Status onVideoSourceChanged(const ::com::rdk::hal::panel::PanelSource& avSource) override;
  ::android::binder::Status onDynamicRangeChanged(::com::rdk::hal::videodecoder::DynamicRange dynamicRange) override;
  ::android::binder::Status onVideoFrameRateChanged(int32_t frameRateNumerator, int32_t frameRateDenominator) override;
  ::android::binder::Status onVideoResolutionChanged(int32_t width, int32_t height) override;
  ::android::binder::Status onRefreshRateChanged(double refreshRateHz) override;
  ::android::binder::Status onStateChanged(::com::rdk::hal::panel::State oldState, ::com::rdk::hal::panel::State newState) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpPanelOutputEventListener
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
