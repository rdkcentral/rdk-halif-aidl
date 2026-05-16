#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/hdmioutput/IHDMIOutputManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
class BpHDMIOutputManager : public ::android::BpInterface<IHDMIOutputManager> {
public:
  explicit BpHDMIOutputManager(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHDMIOutputManager() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::hdmioutput::PlatformCapabilities* _aidl_return) override;
  ::android::binder::Status getHDMIOutputIds(::std::vector<::com::rdk::hal::hdmioutput::IHDMIOutput::Id>* _aidl_return) override;
  ::android::binder::Status getHDMIOutput(const ::com::rdk::hal::hdmioutput::IHDMIOutput::Id& hdmiOutputId, ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutput>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpHDMIOutputManager
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
