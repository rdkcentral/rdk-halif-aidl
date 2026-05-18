#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/drm/IDrmFactory.h>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class BnDrmFactory : public ::android::BnInterface<IDrmFactory> {
public:
  static constexpr uint32_t TRANSACTION_createDrmPlugin = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_createCryptoPlugin = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getSupportedCryptoSchemes = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnDrmFactory();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnDrmFactory

class IDrmFactoryDelegator : public BnDrmFactory {
public:
  explicit IDrmFactoryDelegator(::android::sp<IDrmFactory> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status createDrmPlugin(const ::com::rdk::hal::drm::Uuid& uuid, const ::android::String16& appPackageName, ::android::sp<::com::rdk::hal::drm::IDrmPlugin>* _aidl_return) override {
    return _aidl_delegate->createDrmPlugin(uuid, appPackageName, _aidl_return);
  }
  ::android::binder::Status createCryptoPlugin(const ::com::rdk::hal::drm::Uuid& uuid, const ::std::vector<uint8_t>& initData, ::android::sp<::com::rdk::hal::drm::ICryptoPlugin>* _aidl_return) override {
    return _aidl_delegate->createCryptoPlugin(uuid, initData, _aidl_return);
  }
  ::android::binder::Status getSupportedCryptoSchemes(::com::rdk::hal::drm::CryptoSchemes* _aidl_return) override {
    return _aidl_delegate->getSupportedCryptoSchemes(_aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnDrmFactory::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IDrmFactory> _aidl_delegate;
};  // class IDrmFactoryDelegator
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
