#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/drm/IDrmPlugin.h>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class BnDrmPlugin : public ::android::BnInterface<IDrmPlugin> {
public:
  static constexpr uint32_t TRANSACTION_closeSession = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_decrypt = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_encrypt = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getHdcpLevels = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getKeyRequest = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_getMetrics = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getNumberOfSessions = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_getPropertyByteArray = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_getPropertyString = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_getProvisionRequest = ::android::IBinder::FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_getSecurityLevel = ::android::IBinder::FIRST_CALL_TRANSACTION + 10;
  static constexpr uint32_t TRANSACTION_openSession = ::android::IBinder::FIRST_CALL_TRANSACTION + 11;
  static constexpr uint32_t TRANSACTION_provideKeyResponse = ::android::IBinder::FIRST_CALL_TRANSACTION + 12;
  static constexpr uint32_t TRANSACTION_provideProvisionResponse = ::android::IBinder::FIRST_CALL_TRANSACTION + 13;
  static constexpr uint32_t TRANSACTION_queryKeyStatus = ::android::IBinder::FIRST_CALL_TRANSACTION + 14;
  static constexpr uint32_t TRANSACTION_removeKeys = ::android::IBinder::FIRST_CALL_TRANSACTION + 15;
  static constexpr uint32_t TRANSACTION_requiresSecureDecoder = ::android::IBinder::FIRST_CALL_TRANSACTION + 16;
  static constexpr uint32_t TRANSACTION_setCipherAlgorithm = ::android::IBinder::FIRST_CALL_TRANSACTION + 17;
  static constexpr uint32_t TRANSACTION_setListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 18;
  static constexpr uint32_t TRANSACTION_setMacAlgorithm = ::android::IBinder::FIRST_CALL_TRANSACTION + 19;
  static constexpr uint32_t TRANSACTION_setPlaybackId = ::android::IBinder::FIRST_CALL_TRANSACTION + 20;
  static constexpr uint32_t TRANSACTION_setPropertyByteArray = ::android::IBinder::FIRST_CALL_TRANSACTION + 21;
  static constexpr uint32_t TRANSACTION_setPropertyString = ::android::IBinder::FIRST_CALL_TRANSACTION + 22;
  static constexpr uint32_t TRANSACTION_sign = ::android::IBinder::FIRST_CALL_TRANSACTION + 23;
  static constexpr uint32_t TRANSACTION_signRSA = ::android::IBinder::FIRST_CALL_TRANSACTION + 24;
  static constexpr uint32_t TRANSACTION_verify = ::android::IBinder::FIRST_CALL_TRANSACTION + 25;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnDrmPlugin();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnDrmPlugin

class IDrmPluginDelegator : public BnDrmPlugin {
public:
  explicit IDrmPluginDelegator(::android::sp<IDrmPlugin> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status closeSession(const ::std::vector<uint8_t>& sessionId) override {
    return _aidl_delegate->closeSession(sessionId);
  }
  ::android::binder::Status decrypt(const ::std::vector<uint8_t>& sessionId, const ::std::vector<uint8_t>& keyId, const ::std::vector<uint8_t>& input, const ::std::vector<uint8_t>& iv, ::std::vector<uint8_t>* _aidl_return) override {
    return _aidl_delegate->decrypt(sessionId, keyId, input, iv, _aidl_return);
  }
  ::android::binder::Status encrypt(const ::std::vector<uint8_t>& sessionId, const ::std::vector<uint8_t>& keyId, const ::std::vector<uint8_t>& input, const ::std::vector<uint8_t>& iv, ::std::vector<uint8_t>* _aidl_return) override {
    return _aidl_delegate->encrypt(sessionId, keyId, input, iv, _aidl_return);
  }
  ::android::binder::Status getHdcpLevels(::com::rdk::hal::drm::HdcpLevels* _aidl_return) override {
    return _aidl_delegate->getHdcpLevels(_aidl_return);
  }
  ::android::binder::Status getKeyRequest(const ::std::vector<uint8_t>& scope, const ::std::vector<uint8_t>& initData, const ::android::String16& mimeType, ::com::rdk::hal::drm::KeyType keyType, const ::std::vector<::com::rdk::hal::drm::KeyValue>& optionalParameters, ::com::rdk::hal::drm::KeyRequest* _aidl_return) override {
    return _aidl_delegate->getKeyRequest(scope, initData, mimeType, keyType, optionalParameters, _aidl_return);
  }
  ::android::binder::Status getMetrics(::std::vector<::com::rdk::hal::drm::DrmMetricGroup>* _aidl_return) override {
    return _aidl_delegate->getMetrics(_aidl_return);
  }
  ::android::binder::Status getNumberOfSessions(::com::rdk::hal::drm::NumberOfSessions* _aidl_return) override {
    return _aidl_delegate->getNumberOfSessions(_aidl_return);
  }
  ::android::binder::Status getPropertyByteArray(const ::android::String16& propertyName, ::std::vector<uint8_t>* _aidl_return) override {
    return _aidl_delegate->getPropertyByteArray(propertyName, _aidl_return);
  }
  ::android::binder::Status getPropertyString(const ::android::String16& propertyName, ::android::String16* _aidl_return) override {
    return _aidl_delegate->getPropertyString(propertyName, _aidl_return);
  }
  ::android::binder::Status getProvisionRequest(const ::android::String16& certificateType, const ::android::String16& certificateAuthority, ::com::rdk::hal::drm::ProvisionRequest* _aidl_return) override {
    return _aidl_delegate->getProvisionRequest(certificateType, certificateAuthority, _aidl_return);
  }
  ::android::binder::Status getSecurityLevel(const ::std::vector<uint8_t>& sessionId, ::com::rdk::hal::drm::SecurityLevel* _aidl_return) override {
    return _aidl_delegate->getSecurityLevel(sessionId, _aidl_return);
  }
  ::android::binder::Status openSession(::com::rdk::hal::drm::SecurityLevel securityLevel, ::std::vector<uint8_t>* _aidl_return) override {
    return _aidl_delegate->openSession(securityLevel, _aidl_return);
  }
  ::android::binder::Status provideKeyResponse(const ::std::vector<uint8_t>& scope, const ::std::vector<uint8_t>& response, ::com::rdk::hal::drm::KeySetId* _aidl_return) override {
    return _aidl_delegate->provideKeyResponse(scope, response, _aidl_return);
  }
  ::android::binder::Status provideProvisionResponse(const ::std::vector<uint8_t>& response, ::com::rdk::hal::drm::ProvideProvisionResponseResult* _aidl_return) override {
    return _aidl_delegate->provideProvisionResponse(response, _aidl_return);
  }
  ::android::binder::Status queryKeyStatus(const ::std::vector<uint8_t>& sessionId, ::std::vector<::com::rdk::hal::drm::KeyValue>* _aidl_return) override {
    return _aidl_delegate->queryKeyStatus(sessionId, _aidl_return);
  }
  ::android::binder::Status removeKeys(const ::std::vector<uint8_t>& sessionId) override {
    return _aidl_delegate->removeKeys(sessionId);
  }
  ::android::binder::Status requiresSecureDecoder(const ::android::String16& mime, ::com::rdk::hal::drm::SecurityLevel level, bool* _aidl_return) override {
    return _aidl_delegate->requiresSecureDecoder(mime, level, _aidl_return);
  }
  ::android::binder::Status setCipherAlgorithm(const ::std::vector<uint8_t>& sessionId, const ::android::String16& algorithm) override {
    return _aidl_delegate->setCipherAlgorithm(sessionId, algorithm);
  }
  ::android::binder::Status setListener(const ::android::sp<::com::rdk::hal::drm::IDrmPluginListener>& listener) override {
    return _aidl_delegate->setListener(listener);
  }
  ::android::binder::Status setMacAlgorithm(const ::std::vector<uint8_t>& sessionId, const ::android::String16& algorithm) override {
    return _aidl_delegate->setMacAlgorithm(sessionId, algorithm);
  }
  ::android::binder::Status setPlaybackId(const ::std::vector<uint8_t>& sessionId, const ::android::String16& playbackId) override {
    return _aidl_delegate->setPlaybackId(sessionId, playbackId);
  }
  ::android::binder::Status setPropertyByteArray(const ::android::String16& propertyName, const ::std::vector<uint8_t>& value) override {
    return _aidl_delegate->setPropertyByteArray(propertyName, value);
  }
  ::android::binder::Status setPropertyString(const ::android::String16& propertyName, const ::android::String16& value) override {
    return _aidl_delegate->setPropertyString(propertyName, value);
  }
  ::android::binder::Status sign(const ::std::vector<uint8_t>& sessionId, const ::std::vector<uint8_t>& keyId, const ::std::vector<uint8_t>& message, ::std::vector<uint8_t>* _aidl_return) override {
    return _aidl_delegate->sign(sessionId, keyId, message, _aidl_return);
  }
  ::android::binder::Status signRSA(const ::std::vector<uint8_t>& sessionId, const ::android::String16& algorithm, const ::std::vector<uint8_t>& message, const ::std::vector<uint8_t>& wrappedKey, ::std::vector<uint8_t>* _aidl_return) override {
    return _aidl_delegate->signRSA(sessionId, algorithm, message, wrappedKey, _aidl_return);
  }
  ::android::binder::Status verify(const ::std::vector<uint8_t>& sessionId, const ::std::vector<uint8_t>& keyId, const ::std::vector<uint8_t>& message, const ::std::vector<uint8_t>& signature, bool* _aidl_return) override {
    return _aidl_delegate->verify(sessionId, keyId, message, signature, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnDrmPlugin::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IDrmPlugin> _aidl_delegate;
};  // class IDrmPluginDelegator
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
