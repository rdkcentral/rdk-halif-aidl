#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/hdmioutput/HDCPProtocolVersion.h>
#include <com/rdk/hal/hdmioutput/HDCPStatus.h>
#include <com/rdk/hal/hdmioutput/Property.h>
#include <com/rdk/hal/hdmioutput/PropertyKVPair.h>
#include <com/rdk/hal/hdmioutput/SPDInfoFrame.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
class IHDMIOutputController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIOutputController)
  static const int32_t VERSION = 1;
  const std::string HASH = "1e04b7a2abd81e9534138733782be7e186590068";
  static constexpr char* HASHVALUE = "1e04b7a2abd81e9534138733782be7e186590068";
  virtual ::android::binder::Status start() = 0;
  virtual ::android::binder::Status stop() = 0;
  virtual ::android::binder::Status getHotPlugDetectState(bool* _aidl_return) = 0;
  virtual ::android::binder::Status setProperty(::com::rdk::hal::hdmioutput::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) = 0;
  virtual ::android::binder::Status setPropertyMulti(const ::std::vector<::com::rdk::hal::hdmioutput::PropertyKVPair>& propertyKVList, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getHDCPCurrentVersion(::com::rdk::hal::hdmioutput::HDCPProtocolVersion* _aidl_return) = 0;
  virtual ::android::binder::Status getHDCPReceiverVersion(::com::rdk::hal::hdmioutput::HDCPProtocolVersion* _aidl_return) = 0;
  virtual ::android::binder::Status getHDCPStatus(::com::rdk::hal::hdmioutput::HDCPStatus* _aidl_return) = 0;
  virtual ::android::binder::Status setSPDInfoFrame(const ::std::optional<::com::rdk::hal::hdmioutput::SPDInfoFrame>& spdInfoFrame) = 0;
  virtual ::android::binder::Status getSPDInfoFrame(::std::optional<::com::rdk::hal::hdmioutput::SPDInfoFrame>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHDMIOutputController

class IHDMIOutputControllerDefault : public IHDMIOutputController {
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
  ::android::binder::Status getHotPlugDetectState(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setProperty(::com::rdk::hal::hdmioutput::Property /*property*/, const ::com::rdk::hal::PropertyValue& /*propertyValue*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPropertyMulti(const ::std::vector<::com::rdk::hal::hdmioutput::PropertyKVPair>& /*propertyKVList*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHDCPCurrentVersion(::com::rdk::hal::hdmioutput::HDCPProtocolVersion* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHDCPReceiverVersion(::com::rdk::hal::hdmioutput::HDCPProtocolVersion* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHDCPStatus(::com::rdk::hal::hdmioutput::HDCPStatus* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setSPDInfoFrame(const ::std::optional<::com::rdk::hal::hdmioutput::SPDInfoFrame>& /*spdInfoFrame*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getSPDInfoFrame(::std::optional<::com::rdk::hal::hdmioutput::SPDInfoFrame>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHDMIOutputControllerDefault
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
