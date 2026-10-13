#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/cryptoengine/ICryptoEngineController.h>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
class BnCryptoEngineController : public ::android::BnInterface<ICryptoEngineController> {
public:
  static constexpr uint32_t TRANSACTION_begin = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_computeDigest = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_computeHmac = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_encrypt = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_decrypt = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_generateRandom = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnCryptoEngineController();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnCryptoEngineController

class ICryptoEngineControllerDelegator : public BnCryptoEngineController {
public:
  explicit ICryptoEngineControllerDelegator(::android::sp<ICryptoEngineController> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status begin(::com::rdk::hal::cryptoengine::KeyPurpose purpose, const ::com::rdk::hal::cryptoengine::CryptoConfig& config, ::android::sp<::com::rdk::hal::cryptoengine::ICryptoOperation>* _aidl_return) override {
    return _aidl_delegate->begin(purpose, config, _aidl_return);
  }
  ::android::binder::Status computeDigest(::com::rdk::hal::cryptoengine::Digest digest, const ::std::vector<uint8_t>& data, ::std::vector<uint8_t>* _aidl_return) override {
    return _aidl_delegate->computeDigest(digest, data, _aidl_return);
  }
  ::android::binder::Status computeHmac(::com::rdk::hal::cryptoengine::Digest digest, const ::std::vector<uint8_t>& key, const ::std::vector<uint8_t>& data, ::std::vector<uint8_t>* _aidl_return) override {
    return _aidl_delegate->computeHmac(digest, key, data, _aidl_return);
  }
  ::android::binder::Status encrypt(const ::com::rdk::hal::cryptoengine::CryptoConfig& config, const ::std::vector<uint8_t>& plaintext, ::std::vector<uint8_t>* _aidl_return) override {
    return _aidl_delegate->encrypt(config, plaintext, _aidl_return);
  }
  ::android::binder::Status decrypt(const ::com::rdk::hal::cryptoengine::CryptoConfig& config, const ::std::vector<uint8_t>& ciphertext, ::std::vector<uint8_t>* _aidl_return) override {
    return _aidl_delegate->decrypt(config, ciphertext, _aidl_return);
  }
  ::android::binder::Status generateRandom(int32_t length, ::std::vector<uint8_t>* _aidl_return) override {
    return _aidl_delegate->generateRandom(length, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnCryptoEngineController::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<ICryptoEngineController> _aidl_delegate;
};  // class ICryptoEngineControllerDelegator
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
