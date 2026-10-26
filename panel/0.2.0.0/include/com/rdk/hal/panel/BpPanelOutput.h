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
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::panel::IPanelOutputControllerListener>& listener, ::android::sp<::com::rdk::hal::panel::IPanelOutputController>* _aidl_return) override;
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::panel::IPanelOutputController>& controller, bool* _aidl_return) override;
  ::android::binder::Status registerListener(const ::android::sp<::com::rdk::hal::panel::IPanelOutputEventListener>& listener, bool* _aidl_return) override;
  ::android::binder::Status unregisterListener(const ::android::sp<::com::rdk::hal::panel::IPanelOutputEventListener>& listener, bool* _aidl_return) override;
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
