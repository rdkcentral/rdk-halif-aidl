#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/hdmioutput/IHDMIOutputControllerListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
class BpHDMIOutputControllerListener : public ::android::BpInterface<IHDMIOutputControllerListener> {
public:
  explicit BpHDMIOutputControllerListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHDMIOutputControllerListener() = default;
  ::android::binder::Status onHotPlugDetectStateChanged(bool state) override;
  ::android::binder::Status onFrameRateChanged() override;
  ::android::binder::Status onHDCPStatusChanged(::com::rdk::hal::hdmioutput::HDCPStatus hdcpStatus, ::com::rdk::hal::hdmioutput::HDCPProtocolVersion hdcpProtocolVersion) override;
  ::android::binder::Status onEDID(const ::std::vector<uint8_t>& edid) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpHDMIOutputControllerListener
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
