#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/firmwareupdate/IFirmwareUpdateListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace firmwareupdate {
class BpFirmwareUpdateListener : public ::android::BpInterface<IFirmwareUpdateListener> {
public:
  explicit BpFirmwareUpdateListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpFirmwareUpdateListener() = default;
  ::android::binder::Status onProgress(int32_t percentComplete) override;
  ::android::binder::Status onCompleted(::com::rdk::hal::firmwareupdate::FirmwareUpdateResult result, const ::std::string& report) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpFirmwareUpdateListener
}  // namespace firmwareupdate
}  // namespace hal
}  // namespace rdk
}  // namespace com
