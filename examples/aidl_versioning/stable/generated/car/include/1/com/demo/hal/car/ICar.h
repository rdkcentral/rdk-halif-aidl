#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/demo/hal/car/CarSpecs.h>
#include <com/demo/hal/car/CarStatus.h>
#include <com/demo/hal/car/ICarStatusListener.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace demo {
namespace hal {
namespace car {
class ICar : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(Car)
  static const int32_t VERSION = 1;
  const std::string HASH = "b417ce303247cfe1850758d7b704764bef281458";
  static constexpr char* HASHVALUE = "b417ce303247cfe1850758d7b704764bef281458";
  virtual ::android::binder::Status getCarSpecs(::com::demo::hal::car::CarSpecs* _aidl_return) = 0;
  virtual ::android::binder::Status getCarStatus(::com::demo::hal::car::CarStatus* _aidl_return) = 0;
  virtual ::android::binder::Status startCarEngine() = 0;
  virtual ::android::binder::Status stopCarEngine() = 0;
  virtual ::android::binder::Status registerCarStatusListener(const ::android::sp<::com::demo::hal::car::ICarStatusListener>& listener) = 0;
  virtual ::android::binder::Status unregisterCarStatusListener(const ::android::sp<::com::demo::hal::car::ICarStatusListener>& listener) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ICar

class ICarDefault : public ICar {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCarSpecs(::com::demo::hal::car::CarSpecs* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCarStatus(::com::demo::hal::car::CarStatus* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status startCarEngine() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stopCarEngine() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerCarStatusListener(const ::android::sp<::com::demo::hal::car::ICarStatusListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterCarStatusListener(const ::android::sp<::com::demo::hal::car::ICarStatusListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ICarDefault
}  // namespace car
}  // namespace hal
}  // namespace demo
}  // namespace com
