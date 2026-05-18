#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/drm/IDrmPlugin.h>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class BpDrmPlugin : public ::android::BpInterface<IDrmPlugin> {
public:
  explicit BpDrmPlugin(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpDrmPlugin() = default;
  ::android::binder::Status closeSession(const ::std::vector<uint8_t>& sessionId) override;
  ::android::binder::Status decrypt(const ::std::vector<uint8_t>& sessionId, const ::std::vector<uint8_t>& keyId, const ::std::vector<uint8_t>& input, const ::std::vector<uint8_t>& iv, ::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status encrypt(const ::std::vector<uint8_t>& sessionId, const ::std::vector<uint8_t>& keyId, const ::std::vector<uint8_t>& input, const ::std::vector<uint8_t>& iv, ::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status getHdcpLevels(::com::rdk::hal::drm::HdcpLevels* _aidl_return) override;
  ::android::binder::Status getKeyRequest(const ::std::vector<uint8_t>& scope, const ::std::vector<uint8_t>& initData, const ::android::String16& mimeType, ::com::rdk::hal::drm::KeyType keyType, const ::std::vector<::com::rdk::hal::drm::KeyValue>& optionalParameters, ::com::rdk::hal::drm::KeyRequest* _aidl_return) override;
  ::android::binder::Status getMetrics(::std::vector<::com::rdk::hal::drm::DrmMetricGroup>* _aidl_return) override;
  ::android::binder::Status getNumberOfSessions(::com::rdk::hal::drm::NumberOfSessions* _aidl_return) override;
  ::android::binder::Status getPropertyByteArray(const ::android::String16& propertyName, ::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status getPropertyString(const ::android::String16& propertyName, ::android::String16* _aidl_return) override;
  ::android::binder::Status getProvisionRequest(const ::android::String16& certificateType, const ::android::String16& certificateAuthority, ::com::rdk::hal::drm::ProvisionRequest* _aidl_return) override;
  ::android::binder::Status getSecurityLevel(const ::std::vector<uint8_t>& sessionId, ::com::rdk::hal::drm::SecurityLevel* _aidl_return) override;
  ::android::binder::Status openSession(::com::rdk::hal::drm::SecurityLevel securityLevel, ::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status provideKeyResponse(const ::std::vector<uint8_t>& scope, const ::std::vector<uint8_t>& response, ::com::rdk::hal::drm::KeySetId* _aidl_return) override;
  ::android::binder::Status provideProvisionResponse(const ::std::vector<uint8_t>& response, ::com::rdk::hal::drm::ProvideProvisionResponseResult* _aidl_return) override;
  ::android::binder::Status queryKeyStatus(const ::std::vector<uint8_t>& sessionId, ::std::vector<::com::rdk::hal::drm::KeyValue>* _aidl_return) override;
  ::android::binder::Status removeKeys(const ::std::vector<uint8_t>& sessionId) override;
  ::android::binder::Status requiresSecureDecoder(const ::android::String16& mime, ::com::rdk::hal::drm::SecurityLevel level, bool* _aidl_return) override;
  ::android::binder::Status setCipherAlgorithm(const ::std::vector<uint8_t>& sessionId, const ::android::String16& algorithm) override;
  ::android::binder::Status setListener(const ::android::sp<::com::rdk::hal::drm::IDrmPluginListener>& listener) override;
  ::android::binder::Status setMacAlgorithm(const ::std::vector<uint8_t>& sessionId, const ::android::String16& algorithm) override;
  ::android::binder::Status setPlaybackId(const ::std::vector<uint8_t>& sessionId, const ::android::String16& playbackId) override;
  ::android::binder::Status setPropertyByteArray(const ::android::String16& propertyName, const ::std::vector<uint8_t>& value) override;
  ::android::binder::Status setPropertyString(const ::android::String16& propertyName, const ::android::String16& value) override;
  ::android::binder::Status sign(const ::std::vector<uint8_t>& sessionId, const ::std::vector<uint8_t>& keyId, const ::std::vector<uint8_t>& message, ::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status signRSA(const ::std::vector<uint8_t>& sessionId, const ::android::String16& algorithm, const ::std::vector<uint8_t>& message, const ::std::vector<uint8_t>& wrappedKey, ::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status verify(const ::std::vector<uint8_t>& sessionId, const ::std::vector<uint8_t>& keyId, const ::std::vector<uint8_t>& message, const ::std::vector<uint8_t>& signature, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpDrmPlugin
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
