#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/compositeinput/PortProperty.h>
#include <com/rdk/hal/compositeinput/PropertyKVPair.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
class ICompositeInputController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CompositeInputController)
  static const int32_t VERSION = 1;
  const std::string HASH = "bbad93fa82be1d9624c46072ad235ac4ae274556";
  static constexpr char* HASHVALUE = "bbad93fa82be1d9624c46072ad235ac4ae274556";
  virtual ::android::binder::Status start() = 0;
  virtual ::android::binder::Status stop() = 0;
  virtual ::android::binder::Status setProperty(::com::rdk::hal::compositeinput::PortProperty property, const ::com::rdk::hal::PropertyValue& value) = 0;
  virtual ::android::binder::Status setPropertyMulti(const ::std::vector<::com::rdk::hal::compositeinput::PropertyKVPair>& properties) = 0;
  virtual ::android::binder::Status resetMetrics() = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ICompositeInputController

class ICompositeInputControllerDefault : public ICompositeInputController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status start() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setProperty(::com::rdk::hal::compositeinput::PortProperty /*property*/, const ::com::rdk::hal::PropertyValue& /*value*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPropertyMulti(const ::std::vector<::com::rdk::hal::compositeinput::PropertyKVPair>& /*properties*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status resetMetrics() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ICompositeInputControllerDefault
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
