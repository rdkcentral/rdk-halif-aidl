#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/flash/IFlash.h>

namespace com {
namespace rdk {
namespace hal {
namespace flash {
class BpFlash : public ::android::BpInterface<IFlash> {
public:
  explicit BpFlash(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpFlash() = default;
  ::android::binder::Status flashImageFromFile(const ::std::string& filename, const ::android::sp<::com::rdk::hal::flash::IFlashListener>& listener, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpFlash
}  // namespace flash
}  // namespace hal
}  // namespace rdk
}  // namespace com
