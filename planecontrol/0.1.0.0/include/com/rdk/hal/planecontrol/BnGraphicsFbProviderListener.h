#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/planecontrol/IGraphicsFbProviderListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
class BnGraphicsFbProviderListener : public ::android::BnInterface<IGraphicsFbProviderListener> {
public:
  static constexpr uint32_t TRANSACTION_onGraphicsFbReleased = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnGraphicsFbProviderListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnGraphicsFbProviderListener

class IGraphicsFbProviderListenerDelegator : public BnGraphicsFbProviderListener {
public:
  explicit IGraphicsFbProviderListenerDelegator(::android::sp<IGraphicsFbProviderListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onGraphicsFbReleased(int32_t oldGraphicsFbId, int64_t elapsedRealtimeNanos) override {
    return _aidl_delegate->onGraphicsFbReleased(oldGraphicsFbId, elapsedRealtimeNanos);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnGraphicsFbProviderListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IGraphicsFbProviderListener> _aidl_delegate;
};  // class IGraphicsFbProviderListenerDelegator
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
