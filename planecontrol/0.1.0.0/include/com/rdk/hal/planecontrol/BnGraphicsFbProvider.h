#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/planecontrol/IGraphicsFbProvider.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
class BnGraphicsFbProvider : public ::android::BnInterface<IGraphicsFbProvider> {
public:
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_commitGraphicsFb = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_createGraphicsFb = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_destroyGraphicsFb = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getNativeDisplayHandle = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_getEGLPlatformType = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnGraphicsFbProvider();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnGraphicsFbProvider

class IGraphicsFbProviderDelegator : public BnGraphicsFbProvider {
public:
  explicit IGraphicsFbProviderDelegator(::android::sp<IGraphicsFbProvider> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getCapabilities(::com::rdk::hal::planecontrol::GraphicsFbCapabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status commitGraphicsFb(int32_t graphicsFbId, bool* _aidl_return) override {
    return _aidl_delegate->commitGraphicsFb(graphicsFbId, _aidl_return);
  }
  ::android::binder::Status createGraphicsFb(int32_t width, int32_t height, ::com::rdk::hal::planecontrol::GraphicsFbInfo* outInfo, ::android::os::ParcelFileDescriptor* _aidl_return) override {
    return _aidl_delegate->createGraphicsFb(width, height, outInfo, _aidl_return);
  }
  ::android::binder::Status destroyGraphicsFb(int32_t graphicsFbId) override {
    return _aidl_delegate->destroyGraphicsFb(graphicsFbId);
  }
  ::android::binder::Status getNativeDisplayHandle(int64_t* _aidl_return) override {
    return _aidl_delegate->getNativeDisplayHandle(_aidl_return);
  }
  ::android::binder::Status getEGLPlatformType(int32_t* _aidl_return) override {
    return _aidl_delegate->getEGLPlatformType(_aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnGraphicsFbProvider::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IGraphicsFbProvider> _aidl_delegate;
};  // class IGraphicsFbProviderDelegator
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
