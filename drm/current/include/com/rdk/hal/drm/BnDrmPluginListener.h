#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/drm/IDrmPluginListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class BnDrmPluginListener : public ::android::BnInterface<IDrmPluginListener> {
public:
  static constexpr uint32_t TRANSACTION_onEvent = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onExpirationUpdate = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_onKeysChange = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_onSessionLostState = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnDrmPluginListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnDrmPluginListener

class IDrmPluginListenerDelegator : public BnDrmPluginListener {
public:
  explicit IDrmPluginListenerDelegator(::android::sp<IDrmPluginListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onEvent(::com::rdk::hal::drm::EventType eventType, const ::std::vector<uint8_t>& sessionId, const ::std::vector<uint8_t>& data) override {
    return _aidl_delegate->onEvent(eventType, sessionId, data);
  }
  ::android::binder::Status onExpirationUpdate(const ::std::vector<uint8_t>& sessionId, int64_t expiryTimeInMS) override {
    return _aidl_delegate->onExpirationUpdate(sessionId, expiryTimeInMS);
  }
  ::android::binder::Status onKeysChange(const ::std::vector<uint8_t>& sessionId, const ::std::vector<::com::rdk::hal::drm::KeyStatus>& keyStatusList, bool hasNewUsableKey) override {
    return _aidl_delegate->onKeysChange(sessionId, keyStatusList, hasNewUsableKey);
  }
  ::android::binder::Status onSessionLostState(const ::std::vector<uint8_t>& sessionId) override {
    return _aidl_delegate->onSessionLostState(sessionId);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnDrmPluginListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IDrmPluginListener> _aidl_delegate;
};  // class IDrmPluginListenerDelegator
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
