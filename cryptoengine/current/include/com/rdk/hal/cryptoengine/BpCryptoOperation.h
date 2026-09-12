#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/cryptoengine/ICryptoOperation.h>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
class BpCryptoOperation : public ::android::BpInterface<ICryptoOperation> {
public:
  explicit BpCryptoOperation(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCryptoOperation() = default;
  ::android::binder::Status update(const ::std::vector<uint8_t>& input, ::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status finish(const ::std::optional<::std::vector<uint8_t>>& input, ::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status abort() override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpCryptoOperation
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
