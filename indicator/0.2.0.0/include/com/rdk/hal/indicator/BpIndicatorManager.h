#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/indicator/IIndicatorManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace indicator {
class BpIndicatorManager : public ::android::BpInterface<IIndicatorManager> {
public:
  explicit BpIndicatorManager(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpIndicatorManager() = default;
  ::android::binder::Status getIndicatorIds(::std::vector<::com::rdk::hal::indicator::IIndicator::Id>* _aidl_return) override;
  ::android::binder::Status getIndicator(const ::com::rdk::hal::indicator::IIndicator::Id& indicatorId, ::android::sp<::com::rdk::hal::indicator::IIndicator>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpIndicatorManager
}  // namespace indicator
}  // namespace hal
}  // namespace rdk
}  // namespace com
