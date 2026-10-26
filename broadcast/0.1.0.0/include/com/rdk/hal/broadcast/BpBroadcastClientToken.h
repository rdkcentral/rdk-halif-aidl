#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/broadcast/IBroadcastClientToken.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
class BpBroadcastClientToken : public ::android::BpInterface<IBroadcastClientToken> {
public:
  explicit BpBroadcastClientToken(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpBroadcastClientToken() = default;
  ::android::binder::Status getWhoAmI(::std::string* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpBroadcastClientToken
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
