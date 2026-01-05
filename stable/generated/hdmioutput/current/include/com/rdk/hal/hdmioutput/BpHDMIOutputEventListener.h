#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/hdmioutput/IHDMIOutputEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
class BpHDMIOutputEventListener : public ::android::BpInterface<IHDMIOutputEventListener> {
public:
  explicit BpHDMIOutputEventListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHDMIOutputEventListener() = default;
  ::android::binder::Status onStateChanged(::com::rdk::hal::hdmioutput::State oldState, ::com::rdk::hal::hdmioutput::State newState) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpHDMIOutputEventListener
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
