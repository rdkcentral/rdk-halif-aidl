#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/compositeinput/ICompositeInputController.h>
#include <com/rdk/hal/compositeinput/ICompositeInputControllerListener.h>
#include <com/rdk/hal/compositeinput/ICompositeInputEventListener.h>
#include <com/rdk/hal/compositeinput/Port.h>
#include <com/rdk/hal/compositeinput/PortCapabilities.h>
#include <com/rdk/hal/compositeinput/PortProperty.h>
#include <com/rdk/hal/compositeinput/PortStatus.h>
#include <com/rdk/hal/compositeinput/PropertyKVPair.h>
#include <com/rdk/hal/compositeinput/State.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
class ICompositeInputPort : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CompositeInputPort)
  static const int32_t VERSION = 1;
  const std::string HASH = "bbad93fa82be1d9624c46072ad235ac4ae274556";
  static constexpr char* HASHVALUE = "bbad93fa82be1d9624c46072ad235ac4ae274556";
  virtual ::android::binder::Status getId(int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status getPortInfo(::com::rdk::hal::compositeinput::Port* _aidl_return) = 0;
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::compositeinput::PortCapabilities* _aidl_return) = 0;
  virtual ::android::binder::Status getState(::com::rdk::hal::compositeinput::State* _aidl_return) = 0;
  virtual ::android::binder::Status getStatus(::com::rdk::hal::compositeinput::PortStatus* _aidl_return) = 0;
  virtual ::android::binder::Status getProperty(::com::rdk::hal::compositeinput::PortProperty property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) = 0;
  virtual ::android::binder::Status getPropertyMulti(const ::std::vector<::com::rdk::hal::compositeinput::PortProperty>& properties, ::std::vector<::com::rdk::hal::compositeinput::PropertyKVPair>* _aidl_return) = 0;
  virtual ::android::binder::Status open(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputControllerListener>& listener, ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputController>* _aidl_return) = 0;
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputController>& controller, bool* _aidl_return) = 0;
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputEventListener>& listener) = 0;
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputEventListener>& listener) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ICompositeInputPort

class ICompositeInputPortDefault : public ICompositeInputPort {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getId(int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPortInfo(::com::rdk::hal::compositeinput::Port* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::compositeinput::PortCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getState(::com::rdk::hal::compositeinput::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getStatus(::com::rdk::hal::compositeinput::PortStatus* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::compositeinput::PortProperty /*property*/, ::std::optional<::com::rdk::hal::PropertyValue>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPropertyMulti(const ::std::vector<::com::rdk::hal::compositeinput::PortProperty>& /*properties*/, ::std::vector<::com::rdk::hal::compositeinput::PropertyKVPair>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputControllerListener>& /*listener*/, ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputController>& /*controller*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputEventListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputEventListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ICompositeInputPortDefault
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
