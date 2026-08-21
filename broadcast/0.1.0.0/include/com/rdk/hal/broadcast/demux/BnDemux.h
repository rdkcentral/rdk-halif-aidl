#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/broadcast/demux/IDemux.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class BnDemux : public ::android::BnInterface<IDemux> {
public:
  static constexpr uint32_t TRANSACTION_getId = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_isConnected = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_connect = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_disconnect = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_createSoftwareInput = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_destroySoftwareInput = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_acquireSoftwareInput = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_releaseSoftwareInput = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnDemux();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnDemux

class IDemuxDelegator : public BnDemux {
public:
  explicit IDemuxDelegator(::android::sp<IDemux> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getId(::com::rdk::hal::broadcast::demux::IDemux::Id* _aidl_return) override {
    return _aidl_delegate->getId(_aidl_return);
  }
  ::android::binder::Status isConnected(bool* _aidl_return) override {
    return _aidl_delegate->isConnected(_aidl_return);
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::broadcast::demux::DemuxCapabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status connect(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>& provider, ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxController>* _aidl_return) override {
    return _aidl_delegate->connect(provider, _aidl_return);
  }
  ::android::binder::Status disconnect(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxController>& controller, ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>* _aidl_return) override {
    return _aidl_delegate->disconnect(controller, _aidl_return);
  }
  ::android::binder::Status createSoftwareInput(::std::optional<::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id>* _aidl_return) override {
    return _aidl_delegate->createSoftwareInput(_aidl_return);
  }
  ::android::binder::Status destroySoftwareInput(const ::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id& id) override {
    return _aidl_delegate->destroySoftwareInput(id);
  }
  ::android::binder::Status acquireSoftwareInput(const ::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id& id, ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput>* _aidl_return) override {
    return _aidl_delegate->acquireSoftwareInput(id, _aidl_return);
  }
  ::android::binder::Status releaseSoftwareInput(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput>& input) override {
    return _aidl_delegate->releaseSoftwareInput(input);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnDemux::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IDemux> _aidl_delegate;
};  // class IDemuxDelegator
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
