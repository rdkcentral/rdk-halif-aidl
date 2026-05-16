#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/drm/DrmMetricGroup.h>
#include <com/rdk/hal/drm/HdcpLevels.h>
#include <com/rdk/hal/drm/IDrmPluginListener.h>
#include <com/rdk/hal/drm/KeyRequest.h>
#include <com/rdk/hal/drm/KeySetId.h>
#include <com/rdk/hal/drm/KeyType.h>
#include <com/rdk/hal/drm/KeyValue.h>
#include <com/rdk/hal/drm/NumberOfSessions.h>
#include <com/rdk/hal/drm/ProvideProvisionResponseResult.h>
#include <com/rdk/hal/drm/ProvisionRequest.h>
#include <com/rdk/hal/drm/SecurityLevel.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class IDrmPlugin : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DrmPlugin)
  static const int32_t VERSION = 1;
  const std::string HASH = "77c954ed1bda58039abf0dd6e283f0d896a0cf5d";
  static constexpr char* HASHVALUE = "77c954ed1bda58039abf0dd6e283f0d896a0cf5d";
  virtual ::android::binder::Status closeSession(const ::std::vector<uint8_t>& sessionId) = 0;
  virtual ::android::binder::Status decrypt(const ::std::vector<uint8_t>& sessionId, const ::std::vector<uint8_t>& keyId, const ::std::vector<uint8_t>& input, const ::std::vector<uint8_t>& iv, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::android::binder::Status encrypt(const ::std::vector<uint8_t>& sessionId, const ::std::vector<uint8_t>& keyId, const ::std::vector<uint8_t>& input, const ::std::vector<uint8_t>& iv, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::android::binder::Status getHdcpLevels(::com::rdk::hal::drm::HdcpLevels* _aidl_return) = 0;
  virtual ::android::binder::Status getKeyRequest(const ::std::vector<uint8_t>& scope, const ::std::vector<uint8_t>& initData, const ::android::String16& mimeType, ::com::rdk::hal::drm::KeyType keyType, const ::std::vector<::com::rdk::hal::drm::KeyValue>& optionalParameters, ::com::rdk::hal::drm::KeyRequest* _aidl_return) = 0;
  virtual ::android::binder::Status getMetrics(::std::vector<::com::rdk::hal::drm::DrmMetricGroup>* _aidl_return) = 0;
  virtual ::android::binder::Status getNumberOfSessions(::com::rdk::hal::drm::NumberOfSessions* _aidl_return) = 0;
  virtual ::android::binder::Status getPropertyByteArray(const ::android::String16& propertyName, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::android::binder::Status getPropertyString(const ::android::String16& propertyName, ::android::String16* _aidl_return) = 0;
  virtual ::android::binder::Status getProvisionRequest(const ::android::String16& certificateType, const ::android::String16& certificateAuthority, ::com::rdk::hal::drm::ProvisionRequest* _aidl_return) = 0;
  virtual ::android::binder::Status getSecurityLevel(const ::std::vector<uint8_t>& sessionId, ::com::rdk::hal::drm::SecurityLevel* _aidl_return) = 0;
  virtual ::android::binder::Status openSession(::com::rdk::hal::drm::SecurityLevel securityLevel, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::android::binder::Status provideKeyResponse(const ::std::vector<uint8_t>& scope, const ::std::vector<uint8_t>& response, ::com::rdk::hal::drm::KeySetId* _aidl_return) = 0;
  virtual ::android::binder::Status provideProvisionResponse(const ::std::vector<uint8_t>& response, ::com::rdk::hal::drm::ProvideProvisionResponseResult* _aidl_return) = 0;
  virtual ::android::binder::Status queryKeyStatus(const ::std::vector<uint8_t>& sessionId, ::std::vector<::com::rdk::hal::drm::KeyValue>* _aidl_return) = 0;
  virtual ::android::binder::Status removeKeys(const ::std::vector<uint8_t>& sessionId) = 0;
  virtual ::android::binder::Status requiresSecureDecoder(const ::android::String16& mime, ::com::rdk::hal::drm::SecurityLevel level, bool* _aidl_return) = 0;
  virtual ::android::binder::Status setCipherAlgorithm(const ::std::vector<uint8_t>& sessionId, const ::android::String16& algorithm) = 0;
  virtual ::android::binder::Status setListener(const ::android::sp<::com::rdk::hal::drm::IDrmPluginListener>& listener) = 0;
  virtual ::android::binder::Status setMacAlgorithm(const ::std::vector<uint8_t>& sessionId, const ::android::String16& algorithm) = 0;
  virtual ::android::binder::Status setPlaybackId(const ::std::vector<uint8_t>& sessionId, const ::android::String16& playbackId) = 0;
  virtual ::android::binder::Status setPropertyByteArray(const ::android::String16& propertyName, const ::std::vector<uint8_t>& value) = 0;
  virtual ::android::binder::Status setPropertyString(const ::android::String16& propertyName, const ::android::String16& value) = 0;
  virtual ::android::binder::Status sign(const ::std::vector<uint8_t>& sessionId, const ::std::vector<uint8_t>& keyId, const ::std::vector<uint8_t>& message, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::android::binder::Status signRSA(const ::std::vector<uint8_t>& sessionId, const ::android::String16& algorithm, const ::std::vector<uint8_t>& message, const ::std::vector<uint8_t>& wrappedKey, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::android::binder::Status verify(const ::std::vector<uint8_t>& sessionId, const ::std::vector<uint8_t>& keyId, const ::std::vector<uint8_t>& message, const ::std::vector<uint8_t>& signature, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IDrmPlugin

class IDrmPluginDefault : public IDrmPlugin {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status closeSession(const ::std::vector<uint8_t>& /*sessionId*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status decrypt(const ::std::vector<uint8_t>& /*sessionId*/, const ::std::vector<uint8_t>& /*keyId*/, const ::std::vector<uint8_t>& /*input*/, const ::std::vector<uint8_t>& /*iv*/, ::std::vector<uint8_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status encrypt(const ::std::vector<uint8_t>& /*sessionId*/, const ::std::vector<uint8_t>& /*keyId*/, const ::std::vector<uint8_t>& /*input*/, const ::std::vector<uint8_t>& /*iv*/, ::std::vector<uint8_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHdcpLevels(::com::rdk::hal::drm::HdcpLevels* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getKeyRequest(const ::std::vector<uint8_t>& /*scope*/, const ::std::vector<uint8_t>& /*initData*/, const ::android::String16& /*mimeType*/, ::com::rdk::hal::drm::KeyType /*keyType*/, const ::std::vector<::com::rdk::hal::drm::KeyValue>& /*optionalParameters*/, ::com::rdk::hal::drm::KeyRequest* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getMetrics(::std::vector<::com::rdk::hal::drm::DrmMetricGroup>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getNumberOfSessions(::com::rdk::hal::drm::NumberOfSessions* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPropertyByteArray(const ::android::String16& /*propertyName*/, ::std::vector<uint8_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPropertyString(const ::android::String16& /*propertyName*/, ::android::String16* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProvisionRequest(const ::android::String16& /*certificateType*/, const ::android::String16& /*certificateAuthority*/, ::com::rdk::hal::drm::ProvisionRequest* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getSecurityLevel(const ::std::vector<uint8_t>& /*sessionId*/, ::com::rdk::hal::drm::SecurityLevel* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status openSession(::com::rdk::hal::drm::SecurityLevel /*securityLevel*/, ::std::vector<uint8_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status provideKeyResponse(const ::std::vector<uint8_t>& /*scope*/, const ::std::vector<uint8_t>& /*response*/, ::com::rdk::hal::drm::KeySetId* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status provideProvisionResponse(const ::std::vector<uint8_t>& /*response*/, ::com::rdk::hal::drm::ProvideProvisionResponseResult* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status queryKeyStatus(const ::std::vector<uint8_t>& /*sessionId*/, ::std::vector<::com::rdk::hal::drm::KeyValue>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status removeKeys(const ::std::vector<uint8_t>& /*sessionId*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status requiresSecureDecoder(const ::android::String16& /*mime*/, ::com::rdk::hal::drm::SecurityLevel /*level*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setCipherAlgorithm(const ::std::vector<uint8_t>& /*sessionId*/, const ::android::String16& /*algorithm*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setListener(const ::android::sp<::com::rdk::hal::drm::IDrmPluginListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setMacAlgorithm(const ::std::vector<uint8_t>& /*sessionId*/, const ::android::String16& /*algorithm*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPlaybackId(const ::std::vector<uint8_t>& /*sessionId*/, const ::android::String16& /*playbackId*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPropertyByteArray(const ::android::String16& /*propertyName*/, const ::std::vector<uint8_t>& /*value*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPropertyString(const ::android::String16& /*propertyName*/, const ::android::String16& /*value*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status sign(const ::std::vector<uint8_t>& /*sessionId*/, const ::std::vector<uint8_t>& /*keyId*/, const ::std::vector<uint8_t>& /*message*/, ::std::vector<uint8_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status signRSA(const ::std::vector<uint8_t>& /*sessionId*/, const ::android::String16& /*algorithm*/, const ::std::vector<uint8_t>& /*message*/, const ::std::vector<uint8_t>& /*wrappedKey*/, ::std::vector<uint8_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status verify(const ::std::vector<uint8_t>& /*sessionId*/, const ::std::vector<uint8_t>& /*keyId*/, const ::std::vector<uint8_t>& /*message*/, const ::std::vector<uint8_t>& /*signature*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IDrmPluginDefault
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
