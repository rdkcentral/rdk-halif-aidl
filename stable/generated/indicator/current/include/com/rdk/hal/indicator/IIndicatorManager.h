#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/indicator/IIndicator.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace indicator {
class IIndicatorManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(IndicatorManager)
  static const int32_t VERSION = 1;
  const std::string HASH = "e54232b1ab8a4221dd237a4c69ba1d0321a1d5fd";
  static constexpr char* HASHVALUE = "e54232b1ab8a4221dd237a4c69ba1d0321a1d5fd";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getIndicatorIds(::std::vector<::com::rdk::hal::indicator::IIndicator::Id>* _aidl_return) = 0;
  virtual ::android::binder::Status getIndicator(const ::com::rdk::hal::indicator::IIndicator::Id& indicatorId, ::android::sp<::com::rdk::hal::indicator::IIndicator>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IIndicatorManager

class IIndicatorManagerDefault : public IIndicatorManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getIndicatorIds(::std::vector<::com::rdk::hal::indicator::IIndicator::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getIndicator(const ::com::rdk::hal::indicator::IIndicator::Id& /*indicatorId*/, ::android::sp<::com::rdk::hal::indicator::IIndicator>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IIndicatorManagerDefault
}  // namespace indicator
}  // namespace hal
}  // namespace rdk
}  // namespace com
