#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/demo/hal/dashboard/DashboardInfo.h>
#include <com/demo/hal/dashboard/DashboardWarning.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace demo {
namespace hal {
namespace dashboard {
class IDashboard : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(Dashboard)
  static const int32_t VERSION = 2;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  virtual ::android::binder::Status getDashboardInfo(::com::demo::hal::dashboard::DashboardInfo* _aidl_return) = 0;
  virtual ::android::binder::Status getActiveWarnings(::std::vector<::com::demo::hal::dashboard::DashboardWarning>* _aidl_return) = 0;
  virtual ::android::binder::Status resetDashboard() = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IDashboard

class IDashboardDefault : public IDashboard {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getDashboardInfo(::com::demo::hal::dashboard::DashboardInfo* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getActiveWarnings(::std::vector<::com::demo::hal::dashboard::DashboardWarning>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status resetDashboard() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IDashboardDefault
}  // namespace dashboard
}  // namespace hal
}  // namespace demo
}  // namespace com
