#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/firmwareupdate/IFirmwareUpdate.h>

namespace com {
namespace rdk {
namespace hal {
namespace firmwareupdate {
class BpFirmwareUpdate : public ::android::BpInterface<IFirmwareUpdate> {
public:
  explicit BpFirmwareUpdate(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpFirmwareUpdate() = default;
  ::android::binder::Status updateFirmwareFromFile(const ::std::string& filename, const ::android::sp<::com::rdk::hal::firmwareupdate::IFirmwareUpdateListener>& listener, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpFirmwareUpdate
}  // namespace firmwareupdate
}  // namespace hal
}  // namespace rdk
}  // namespace com
