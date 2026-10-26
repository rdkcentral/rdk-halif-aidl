#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/panel/IPanelOutputControllerListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class BpPanelOutputControllerListener : public ::android::BpInterface<IPanelOutputControllerListener> {
public:
  explicit BpPanelOutputControllerListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpPanelOutputControllerListener() = default;
  ::android::binder::Status onPictureModeChanged(const ::std::string& pictureMode) override;
  ::android::binder::Status onPQParameterChanged(const ::std::string& pictureMode, const ::com::rdk::hal::panel::PanelSource& avSource, ::com::rdk::hal::videodecoder::DynamicRange dynamicRange, ::com::rdk::hal::panel::PQParameter pictureProperty, const ::com::rdk::hal::panel::PQParameterValue& picturePropertyValue) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpPanelOutputControllerListener
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
