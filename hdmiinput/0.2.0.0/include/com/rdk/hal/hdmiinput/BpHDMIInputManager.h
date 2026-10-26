#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/hdmiinput/IHDMIInputManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
class BpHDMIInputManager : public ::android::BpInterface<IHDMIInputManager> {
public:
  explicit BpHDMIInputManager(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHDMIInputManager() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::hdmiinput::PlatformCapabilities* _aidl_return) override;
  ::android::binder::Status getHDMIInputIds(::std::vector<::com::rdk::hal::hdmiinput::IHDMIInput::Id>* _aidl_return) override;
  ::android::binder::Status getHDMIInput(const ::com::rdk::hal::hdmiinput::IHDMIInput::Id& hdmiInputId, ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInput>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpHDMIInputManager
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
