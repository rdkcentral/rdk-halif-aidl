#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/demo/hal/car/CarStatus.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace demo {
namespace hal {
namespace car {
class ICarStatusListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CarStatusListener)
  static const int32_t VERSION = 3;
  const std::string HASH = "28ca573b15863492751d159acf149320968aa09b";
  static constexpr char* HASHVALUE = "28ca573b15863492751d159acf149320968aa09b";
  virtual ::android::binder::Status onCarStatusChanged(const ::com::demo::hal::car::CarStatus& newStatus) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ICarStatusListener

class ICarStatusListenerDefault : public ICarStatusListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onCarStatusChanged(const ::com::demo::hal::car::CarStatus& /*newStatus*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ICarStatusListenerDefault
}  // namespace car
}  // namespace hal
}  // namespace demo
}  // namespace com
