#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/cryptoengine/ICryptoEngine.h>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
class BpCryptoEngine : public ::android::BpInterface<ICryptoEngine> {
public:
  explicit BpCryptoEngine(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCryptoEngine() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::cryptoengine::EngineCapabilities* _aidl_return) override;
  ::android::binder::Status open(::android::sp<::com::rdk::hal::cryptoengine::ICryptoEngineController>* _aidl_return) override;
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::cryptoengine::ICryptoEngineController>& controller, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpCryptoEngine
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
