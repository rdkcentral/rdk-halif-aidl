#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/hdmiinput/IHDMIInputControllerListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
class BpHDMIInputControllerListener : public ::android::BpInterface<IHDMIInputControllerListener> {
public:
  explicit BpHDMIInputControllerListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHDMIInputControllerListener() = default;
  ::android::binder::Status onConnectionStateChanged(bool connectionState) override;
  ::android::binder::Status onSignalStateChanged(::com::rdk::hal::hdmiinput::SignalState signalState) override;
  ::android::binder::Status onVideoFormatChanged(::com::rdk::hal::hdmiinput::VIC vic) override;
  ::android::binder::Status onVRRChanged(bool vrrActive, bool M_CONST, bool fastVActive, double frameRate) override;
  ::android::binder::Status onAVIInfoFrame(const ::std::vector<uint8_t>& data) override;
  ::android::binder::Status onAudioInfoFrame(const ::std::vector<uint8_t>& data) override;
  ::android::binder::Status onSPDInfoFrame(const ::std::vector<uint8_t>& data) override;
  ::android::binder::Status onDRMInfoFrame(const ::std::vector<uint8_t>& data) override;
  ::android::binder::Status onVendorSpecificInfoFrame(const ::std::vector<uint8_t>& data) override;
  ::android::binder::Status onHDCPStatusChanged(::com::rdk::hal::hdmiinput::HDCPStatus hdcpStatus, ::com::rdk::hal::hdmiinput::HDCPProtocolVersion hdcpProtocolVersion) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpHDMIInputControllerListener
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
