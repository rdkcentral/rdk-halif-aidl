#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/avclock/IAVClockManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
class BpAVClockManager : public ::android::BpInterface<IAVClockManager> {
public:
  explicit BpAVClockManager(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAVClockManager() = default;
  ::android::binder::Status getAVClockIds(::std::vector<::com::rdk::hal::avclock::IAVClock::Id>* _aidl_return) override;
  ::android::binder::Status getAVClock(const ::com::rdk::hal::avclock::IAVClock::Id& avClockId, ::android::sp<::com::rdk::hal::avclock::IAVClock>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAVClockManager
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
