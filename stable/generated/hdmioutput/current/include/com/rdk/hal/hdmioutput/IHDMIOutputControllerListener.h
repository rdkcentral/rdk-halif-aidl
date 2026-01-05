#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmioutput/HDCPProtocolVersion.h>
#include <com/rdk/hal/hdmioutput/HDCPStatus.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
class IHDMIOutputControllerListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIOutputControllerListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "1e04b7a2abd81e9534138733782be7e186590068";
  static constexpr char* HASHVALUE = "1e04b7a2abd81e9534138733782be7e186590068";
  virtual ::android::binder::Status onHotPlugDetectStateChanged(bool state) = 0;
  virtual ::android::binder::Status onFrameRateChanged() = 0;
  virtual ::android::binder::Status onHDCPStatusChanged(::com::rdk::hal::hdmioutput::HDCPStatus hdcpStatus, ::com::rdk::hal::hdmioutput::HDCPProtocolVersion hdcpProtocolVersion) = 0;
  virtual ::android::binder::Status onEDID(const ::std::vector<uint8_t>& edid) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHDMIOutputControllerListener

class IHDMIOutputControllerListenerDefault : public IHDMIOutputControllerListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onHotPlugDetectStateChanged(bool /*state*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onFrameRateChanged() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onHDCPStatusChanged(::com::rdk::hal::hdmioutput::HDCPStatus /*hdcpStatus*/, ::com::rdk::hal::hdmioutput::HDCPProtocolVersion /*hdcpProtocolVersion*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onEDID(const ::std::vector<uint8_t>& /*edid*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHDMIOutputControllerListenerDefault
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
