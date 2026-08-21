#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/LnbTone.h>
#include <com/rdk/hal/broadcast/frontend/LnbVoltage.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class ILnbController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(LnbController)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  virtual ::android::binder::Status setVoltage(::com::rdk::hal::broadcast::frontend::LnbVoltage voltage) = 0;
  virtual ::android::binder::Status setTone(::com::rdk::hal::broadcast::frontend::LnbTone tone) = 0;
  virtual ::android::binder::Status isOverloaded(bool* _aidl_return) = 0;
  virtual ::android::binder::Status sendDiseqc(const ::std::vector<uint8_t>& command) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ILnbController

class ILnbControllerDefault : public ILnbController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status setVoltage(::com::rdk::hal::broadcast::frontend::LnbVoltage /*voltage*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setTone(::com::rdk::hal::broadcast::frontend::LnbTone /*tone*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status isOverloaded(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status sendDiseqc(const ::std::vector<uint8_t>& /*command*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ILnbControllerDefault
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
