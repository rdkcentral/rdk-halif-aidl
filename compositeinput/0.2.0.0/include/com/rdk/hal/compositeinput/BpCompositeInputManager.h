#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/compositeinput/ICompositeInputManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
class BpCompositeInputManager : public ::android::BpInterface<ICompositeInputManager> {
public:
  explicit BpCompositeInputManager(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCompositeInputManager() = default;
  ::android::binder::Status getPlatformCapabilities(::com::rdk::hal::compositeinput::PlatformCapabilities* _aidl_return) override;
  ::android::binder::Status getPortIds(::std::vector<int32_t>* _aidl_return) override;
  ::android::binder::Status getPort(int32_t portId, ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputPort>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpCompositeInputManager
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
