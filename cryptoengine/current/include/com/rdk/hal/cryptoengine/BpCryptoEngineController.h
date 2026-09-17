#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/cryptoengine/ICryptoEngineController.h>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
class BpCryptoEngineController : public ::android::BpInterface<ICryptoEngineController> {
public:
  explicit BpCryptoEngineController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCryptoEngineController() = default;
  ::android::binder::Status begin(::com::rdk::hal::cryptoengine::KeyPurpose purpose, const ::com::rdk::hal::cryptoengine::CryptoConfig& config, ::android::sp<::com::rdk::hal::cryptoengine::ICryptoOperation>* _aidl_return) override;
  ::android::binder::Status computeDigest(::com::rdk::hal::cryptoengine::Digest digest, const ::std::vector<uint8_t>& data, ::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status computeHmac(::com::rdk::hal::cryptoengine::Digest digest, const ::std::vector<uint8_t>& key, const ::std::vector<uint8_t>& data, ::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status encrypt(const ::com::rdk::hal::cryptoengine::CryptoConfig& config, const ::std::vector<uint8_t>& plaintext, ::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status decrypt(const ::com::rdk::hal::cryptoengine::CryptoConfig& config, const ::std::vector<uint8_t>& ciphertext, ::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status generateRandom(int32_t length, ::std::vector<uint8_t>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpCryptoEngineController
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
