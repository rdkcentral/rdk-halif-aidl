#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/drm/ICryptoPlugin.h>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class BnCryptoPlugin : public ::android::BnInterface<ICryptoPlugin> {
public:
  static constexpr uint32_t TRANSACTION_decrypt = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_notifyResolution = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_requiresSecureDecoderComponent = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_setMediaDrmSession = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnCryptoPlugin();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnCryptoPlugin

class ICryptoPluginDelegator : public BnCryptoPlugin {
public:
  explicit ICryptoPluginDelegator(::android::sp<ICryptoPlugin> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status decrypt(const ::com::rdk::hal::drm::DecryptArgs& args, int32_t* _aidl_return) override {
    return _aidl_delegate->decrypt(args, _aidl_return);
  }
  ::android::binder::Status notifyResolution(int32_t width, int32_t height) override {
    return _aidl_delegate->notifyResolution(width, height);
  }
  ::android::binder::Status requiresSecureDecoderComponent(const ::android::String16& mime, bool* _aidl_return) override {
    return _aidl_delegate->requiresSecureDecoderComponent(mime, _aidl_return);
  }
  ::android::binder::Status setMediaDrmSession(const ::std::vector<uint8_t>& sessionId) override {
    return _aidl_delegate->setMediaDrmSession(sessionId);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnCryptoPlugin::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<ICryptoPlugin> _aidl_delegate;
};  // class ICryptoPluginDelegator
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
