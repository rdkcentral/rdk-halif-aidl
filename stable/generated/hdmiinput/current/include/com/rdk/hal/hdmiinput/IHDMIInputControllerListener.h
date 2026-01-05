#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmiinput/HDCPProtocolVersion.h>
#include <com/rdk/hal/hdmiinput/HDCPStatus.h>
#include <com/rdk/hal/hdmiinput/SignalState.h>
#include <com/rdk/hal/hdmiinput/VIC.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
class IHDMIInputControllerListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIInputControllerListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "82e8e5917a80b0598944ae1e7c36f1eba27fac32";
  static constexpr char* HASHVALUE = "82e8e5917a80b0598944ae1e7c36f1eba27fac32";
  virtual ::android::binder::Status onConnectionStateChanged(bool connectionState) = 0;
  virtual ::android::binder::Status onSignalStateChanged(::com::rdk::hal::hdmiinput::SignalState signalState) = 0;
  virtual ::android::binder::Status onVideoFormatChanged(::com::rdk::hal::hdmiinput::VIC vic) = 0;
  virtual ::android::binder::Status onVRRChanged(bool vrrActive, bool M_CONST, bool fastVActive, double frameRate) = 0;
  virtual ::android::binder::Status onAVIInfoFrame(const ::std::vector<uint8_t>& data) = 0;
  virtual ::android::binder::Status onAudioInfoFrame(const ::std::vector<uint8_t>& data) = 0;
  virtual ::android::binder::Status onSPDInfoFrame(const ::std::vector<uint8_t>& data) = 0;
  virtual ::android::binder::Status onDRMInfoFrame(const ::std::vector<uint8_t>& data) = 0;
  virtual ::android::binder::Status onVendorSpecificInfoFrame(const ::std::vector<uint8_t>& data) = 0;
  virtual ::android::binder::Status onHDCPStatusChanged(::com::rdk::hal::hdmiinput::HDCPStatus hdcpStatus, ::com::rdk::hal::hdmiinput::HDCPProtocolVersion hdcpProtocolVersion) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHDMIInputControllerListener

class IHDMIInputControllerListenerDefault : public IHDMIInputControllerListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onConnectionStateChanged(bool /*connectionState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onSignalStateChanged(::com::rdk::hal::hdmiinput::SignalState /*signalState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVideoFormatChanged(::com::rdk::hal::hdmiinput::VIC /*vic*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVRRChanged(bool /*vrrActive*/, bool /*M_CONST*/, bool /*fastVActive*/, double /*frameRate*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onAVIInfoFrame(const ::std::vector<uint8_t>& /*data*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onAudioInfoFrame(const ::std::vector<uint8_t>& /*data*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onSPDInfoFrame(const ::std::vector<uint8_t>& /*data*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onDRMInfoFrame(const ::std::vector<uint8_t>& /*data*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVendorSpecificInfoFrame(const ::std::vector<uint8_t>& /*data*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onHDCPStatusChanged(::com::rdk::hal::hdmiinput::HDCPStatus /*hdcpStatus*/, ::com::rdk::hal::hdmiinput::HDCPProtocolVersion /*hdcpProtocolVersion*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHDMIInputControllerListenerDefault
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
