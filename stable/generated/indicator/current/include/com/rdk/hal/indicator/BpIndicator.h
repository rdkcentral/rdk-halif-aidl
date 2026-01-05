#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/indicator/IIndicator.h>

namespace com {
namespace rdk {
namespace hal {
namespace indicator {
class BpIndicator : public ::android::BpInterface<IIndicator> {
public:
  explicit BpIndicator(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpIndicator() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::indicator::Capabilities* _aidl_return) override;
  ::android::binder::Status set(const ::android::String16& state, bool* _aidl_return) override;
  ::android::binder::Status get(::android::String16* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpIndicator
}  // namespace indicator
}  // namespace hal
}  // namespace rdk
}  // namespace com
