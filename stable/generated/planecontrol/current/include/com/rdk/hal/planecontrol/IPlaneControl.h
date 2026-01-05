#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/planecontrol/Capabilities.h>
#include <com/rdk/hal/planecontrol/IPlaneControlListener.h>
#include <com/rdk/hal/planecontrol/Property.h>
#include <com/rdk/hal/planecontrol/PropertyKVPair.h>
#include <com/rdk/hal/planecontrol/SourcePlaneMapping.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
class IPlaneControl : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PlaneControl)
  static const int32_t VERSION = 1;
  const std::string HASH = "bed7512d891c70602f0bd173dd855823d7382423";
  static constexpr char* HASHVALUE = "bed7512d891c70602f0bd173dd855823d7382423";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getCapabilities(::std::vector<::com::rdk::hal::planecontrol::Capabilities>* _aidl_return) = 0;
  virtual ::android::binder::Status getNativeGraphicsWindowHandle(int32_t planeResourceIndex, int64_t* _aidl_return) = 0;
  virtual ::android::binder::Status releaseNativeGraphicsWindowHandle(int32_t planeResourceIndex, int64_t nativeWindowHandle) = 0;
  virtual ::android::binder::Status flipGraphicsBuffer(int32_t planeResourceIndex, bool* _aidl_return) = 0;
  virtual ::android::binder::Status setVideoSourceDestinationPlaneMapping(const ::std::vector<::com::rdk::hal::planecontrol::SourcePlaneMapping>& listSourcePlaneMapping, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getVideoSourceDestinationPlaneMapping(::std::vector<::com::rdk::hal::planecontrol::SourcePlaneMapping>* _aidl_return) = 0;
  virtual ::android::binder::Status getProperty(int32_t planeResourceIndex, ::com::rdk::hal::planecontrol::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) = 0;
  virtual ::android::binder::Status setProperty(int32_t planeResourceIndex, ::com::rdk::hal::planecontrol::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getPropertyMulti(int32_t planeResourceIndex, const ::std::vector<::com::rdk::hal::planecontrol::Property>& properties, ::std::vector<::com::rdk::hal::planecontrol::PropertyKVPair>* propertyKVList, bool* _aidl_return) = 0;
  virtual ::android::binder::Status setPropertyMultiAtomic(int32_t planeResourceIndex, const ::std::vector<::com::rdk::hal::planecontrol::PropertyKVPair>& propertyKVList, bool* _aidl_return) = 0;
  virtual ::android::binder::Status registerListener(const ::android::sp<::com::rdk::hal::planecontrol::IPlaneControlListener>& listener, bool* _aidl_return) = 0;
  virtual ::android::binder::Status unregisterListener(const ::android::sp<::com::rdk::hal::planecontrol::IPlaneControlListener>& listener, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IPlaneControl

class IPlaneControlDefault : public IPlaneControl {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::std::vector<::com::rdk::hal::planecontrol::Capabilities>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getNativeGraphicsWindowHandle(int32_t /*planeResourceIndex*/, int64_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status releaseNativeGraphicsWindowHandle(int32_t /*planeResourceIndex*/, int64_t /*nativeWindowHandle*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status flipGraphicsBuffer(int32_t /*planeResourceIndex*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setVideoSourceDestinationPlaneMapping(const ::std::vector<::com::rdk::hal::planecontrol::SourcePlaneMapping>& /*listSourcePlaneMapping*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoSourceDestinationPlaneMapping(::std::vector<::com::rdk::hal::planecontrol::SourcePlaneMapping>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(int32_t /*planeResourceIndex*/, ::com::rdk::hal::planecontrol::Property /*property*/, ::std::optional<::com::rdk::hal::PropertyValue>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setProperty(int32_t /*planeResourceIndex*/, ::com::rdk::hal::planecontrol::Property /*property*/, const ::com::rdk::hal::PropertyValue& /*propertyValue*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPropertyMulti(int32_t /*planeResourceIndex*/, const ::std::vector<::com::rdk::hal::planecontrol::Property>& /*properties*/, ::std::vector<::com::rdk::hal::planecontrol::PropertyKVPair>* /*propertyKVList*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPropertyMultiAtomic(int32_t /*planeResourceIndex*/, const ::std::vector<::com::rdk::hal::planecontrol::PropertyKVPair>& /*propertyKVList*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerListener(const ::android::sp<::com::rdk::hal::planecontrol::IPlaneControlListener>& /*listener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterListener(const ::android::sp<::com::rdk::hal::planecontrol::IPlaneControlListener>& /*listener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IPlaneControlDefault
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
