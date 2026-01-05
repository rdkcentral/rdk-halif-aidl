#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmicec/SendMessageStatus.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
class IHdmiCecController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HdmiCecController)
  static const int32_t VERSION = 1;
  const std::string HASH = "5790bea2dfbdfc34cbbe010cecda4694d0bd432d";
  static constexpr char* HASHVALUE = "5790bea2dfbdfc34cbbe010cecda4694d0bd432d";
  virtual ::android::binder::Status addLogicalAddresses(const ::std::vector<int32_t>& logicalAddresses, bool* _aidl_return) = 0;
  virtual ::android::binder::Status removeLogicalAddresses(const ::std::vector<int32_t>& logicalAddresses, bool* _aidl_return) = 0;
  virtual ::android::binder::Status sendMessage(const ::std::vector<uint8_t>& message, ::com::rdk::hal::hdmicec::SendMessageStatus* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHdmiCecController

class IHdmiCecControllerDefault : public IHdmiCecController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status addLogicalAddresses(const ::std::vector<int32_t>& /*logicalAddresses*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status removeLogicalAddresses(const ::std::vector<int32_t>& /*logicalAddresses*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status sendMessage(const ::std::vector<uint8_t>& /*message*/, ::com::rdk::hal::hdmicec::SendMessageStatus* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHdmiCecControllerDefault
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
