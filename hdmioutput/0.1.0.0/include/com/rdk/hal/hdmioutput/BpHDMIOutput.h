#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/hdmioutput/IHDMIOutput.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
class BpHDMIOutput : public ::android::BpInterface<IHDMIOutput> {
public:
  explicit BpHDMIOutput(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHDMIOutput() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::hdmioutput::Capabilities* _aidl_return) override;
  ::android::binder::Status getProperty(::com::rdk::hal::hdmioutput::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) override;
  ::android::binder::Status getState(::com::rdk::hal::hdmioutput::State* _aidl_return) override;
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputControllerListener>& hdmiOutputControllerListener, ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputController>* _aidl_return) override;
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputController>& hdmiOutputController, bool* _aidl_return) override;
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputEventListener>& hdmiOutputEventListener, bool* _aidl_return) override;
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputEventListener>& hdmiOutputEventListener, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpHDMIOutput
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
