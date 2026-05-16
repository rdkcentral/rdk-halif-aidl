#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
class IHDMIInputController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIInputController)
  static const int32_t VERSION = 1;
  const std::string HASH = "7946019ce36bd9a8290f938cebf478d23b12f11c";
  static constexpr char* HASHVALUE = "7946019ce36bd9a8290f938cebf478d23b12f11c";
  virtual ::android::binder::Status getConnectionState(bool* _aidl_return) = 0;
  virtual ::android::binder::Status start() = 0;
  virtual ::android::binder::Status stop() = 0;
  virtual ::android::binder::Status setEDID(const ::std::vector<uint8_t>& edid, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHDMIInputController

class IHDMIInputControllerDefault : public IHDMIInputController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getConnectionState(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status start() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setEDID(const ::std::vector<uint8_t>& /*edid*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHDMIInputControllerDefault
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
