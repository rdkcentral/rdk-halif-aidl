#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/planecontrol/IPlaneControlListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
class BnPlaneControlListener : public ::android::BnInterface<IPlaneControlListener> {
public:
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnPlaneControlListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnPlaneControlListener

class IPlaneControlListenerDelegator : public BnPlaneControlListener {
public:
  explicit IPlaneControlListenerDelegator(::android::sp<IPlaneControlListener> &impl) : _aidl_delegate(impl) {}

  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnPlaneControlListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IPlaneControlListener> _aidl_delegate;
};  // class IPlaneControlListenerDelegator
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
