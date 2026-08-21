#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/broadcast/frontend/IFrontend.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class BnFrontend : public ::android::BnInterface<IFrontend> {
public:
  static constexpr uint32_t TRANSACTION_getId = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_isOpen = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getFrontendTypes = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_open = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_close = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_acquireDataProvider = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_releaseDataProvider = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_openLnb = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_closeLnb = ::android::IBinder::FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnFrontend();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnFrontend

class IFrontendDelegator : public BnFrontend {
public:
  explicit IFrontendDelegator(::android::sp<IFrontend> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getId(::com::rdk::hal::broadcast::frontend::IFrontend::Id* _aidl_return) override {
    return _aidl_delegate->getId(_aidl_return);
  }
  ::android::binder::Status isOpen(bool* _aidl_return) override {
    return _aidl_delegate->isOpen(_aidl_return);
  }
  ::android::binder::Status getFrontendTypes(::std::vector<::com::rdk::hal::broadcast::frontend::FrontendType>* _aidl_return) override {
    return _aidl_delegate->getFrontendTypes(_aidl_return);
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::broadcast::frontend::FrontendType frontendType, ::std::optional<::com::rdk::hal::broadcast::frontend::FrontendCapabilities>* _aidl_return) override {
    return _aidl_delegate->getCapabilities(frontendType, _aidl_return);
  }
  ::android::binder::Status open(::android::sp<::com::rdk::hal::broadcast::frontend::IFrontendController>* _aidl_return) override {
    return _aidl_delegate->open(_aidl_return);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::broadcast::frontend::IFrontendController>& controller) override {
    return _aidl_delegate->close(controller);
  }
  ::android::binder::Status acquireDataProvider(::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>* _aidl_return) override {
    return _aidl_delegate->acquireDataProvider(_aidl_return);
  }
  ::android::binder::Status releaseDataProvider(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>& provider) override {
    return _aidl_delegate->releaseDataProvider(provider);
  }
  ::android::binder::Status openLnb(::android::sp<::com::rdk::hal::broadcast::frontend::ILnbController>* _aidl_return) override {
    return _aidl_delegate->openLnb(_aidl_return);
  }
  ::android::binder::Status closeLnb(const ::android::sp<::com::rdk::hal::broadcast::frontend::ILnbController>& controller) override {
    return _aidl_delegate->closeLnb(controller);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnFrontend::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IFrontend> _aidl_delegate;
};  // class IFrontendDelegator
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
