#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/demo/hal/dashboard/IDashboard.h>

namespace com {
namespace demo {
namespace hal {
namespace dashboard {
class BpDashboard : public ::android::BpInterface<IDashboard> {
public:
  explicit BpDashboard(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpDashboard() = default;
  ::android::binder::Status getDashboardInfo(::com::demo::hal::dashboard::DashboardInfo* _aidl_return) override;
  ::android::binder::Status getActiveWarnings(::std::vector<::com::demo::hal::dashboard::DashboardWarning>* _aidl_return) override;
  ::android::binder::Status resetDashboard() override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpDashboard
}  // namespace dashboard
}  // namespace hal
}  // namespace demo
}  // namespace com
