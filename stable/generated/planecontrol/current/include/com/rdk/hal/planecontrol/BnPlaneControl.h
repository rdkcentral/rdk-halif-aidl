#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/planecontrol/IPlaneControl.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
class BnPlaneControl : public ::android::BnInterface<IPlaneControl> {
public:
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getNativeGraphicsWindowHandle = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_releaseNativeGraphicsWindowHandle = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_flipGraphicsBuffer = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_setVideoSourceDestinationPlaneMapping = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_getVideoSourceDestinationPlaneMapping = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_setProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_getPropertyMulti = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_setPropertyMultiAtomic = ::android::IBinder::FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_registerListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 10;
  static constexpr uint32_t TRANSACTION_unregisterListener = ::android::IBinder::FIRST_CALL_TRANSACTION + 11;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnPlaneControl();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnPlaneControl

class IPlaneControlDelegator : public BnPlaneControl {
public:
  explicit IPlaneControlDelegator(::android::sp<IPlaneControl> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getCapabilities(::std::vector<::com::rdk::hal::planecontrol::Capabilities>* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status getNativeGraphicsWindowHandle(int32_t planeResourceIndex, int64_t* _aidl_return) override {
    return _aidl_delegate->getNativeGraphicsWindowHandle(planeResourceIndex, _aidl_return);
  }
  ::android::binder::Status releaseNativeGraphicsWindowHandle(int32_t planeResourceIndex, int64_t nativeWindowHandle) override {
    return _aidl_delegate->releaseNativeGraphicsWindowHandle(planeResourceIndex, nativeWindowHandle);
  }
  ::android::binder::Status flipGraphicsBuffer(int32_t planeResourceIndex, bool* _aidl_return) override {
    return _aidl_delegate->flipGraphicsBuffer(planeResourceIndex, _aidl_return);
  }
  ::android::binder::Status setVideoSourceDestinationPlaneMapping(const ::std::vector<::com::rdk::hal::planecontrol::SourcePlaneMapping>& listSourcePlaneMapping, bool* _aidl_return) override {
    return _aidl_delegate->setVideoSourceDestinationPlaneMapping(listSourcePlaneMapping, _aidl_return);
  }
  ::android::binder::Status getVideoSourceDestinationPlaneMapping(::std::vector<::com::rdk::hal::planecontrol::SourcePlaneMapping>* _aidl_return) override {
    return _aidl_delegate->getVideoSourceDestinationPlaneMapping(_aidl_return);
  }
  ::android::binder::Status getProperty(int32_t planeResourceIndex, ::com::rdk::hal::planecontrol::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) override {
    return _aidl_delegate->getProperty(planeResourceIndex, property, _aidl_return);
  }
  ::android::binder::Status setProperty(int32_t planeResourceIndex, ::com::rdk::hal::planecontrol::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) override {
    return _aidl_delegate->setProperty(planeResourceIndex, property, propertyValue, _aidl_return);
  }
  ::android::binder::Status getPropertyMulti(int32_t planeResourceIndex, const ::std::vector<::com::rdk::hal::planecontrol::Property>& properties, ::std::vector<::com::rdk::hal::planecontrol::PropertyKVPair>* propertyKVList, bool* _aidl_return) override {
    return _aidl_delegate->getPropertyMulti(planeResourceIndex, properties, propertyKVList, _aidl_return);
  }
  ::android::binder::Status setPropertyMultiAtomic(int32_t planeResourceIndex, const ::std::vector<::com::rdk::hal::planecontrol::PropertyKVPair>& propertyKVList, bool* _aidl_return) override {
    return _aidl_delegate->setPropertyMultiAtomic(planeResourceIndex, propertyKVList, _aidl_return);
  }
  ::android::binder::Status registerListener(const ::android::sp<::com::rdk::hal::planecontrol::IPlaneControlListener>& listener, bool* _aidl_return) override {
    return _aidl_delegate->registerListener(listener, _aidl_return);
  }
  ::android::binder::Status unregisterListener(const ::android::sp<::com::rdk::hal::planecontrol::IPlaneControlListener>& listener, bool* _aidl_return) override {
    return _aidl_delegate->unregisterListener(listener, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnPlaneControl::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IPlaneControl> _aidl_delegate;
};  // class IPlaneControlDelegator
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
