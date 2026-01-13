#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/flash/IFlashListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace flash {
class BpFlashListener : public ::android::BpInterface<IFlashListener> {
public:
  explicit BpFlashListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpFlashListener() = default;
  ::android::binder::Status onProgress(int32_t percentComplete) override;
  ::android::binder::Status onCompleted(::com::rdk::hal::flash::FlashImageResult result, const ::std::string& report) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpFlashListener
}  // namespace flash
}  // namespace hal
}  // namespace rdk
}  // namespace com
