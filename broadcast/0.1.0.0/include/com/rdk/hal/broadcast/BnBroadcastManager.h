#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/broadcast/IBroadcastManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
class BnBroadcastManager : public ::android::BnInterface<IBroadcastManager> {
public:
  static constexpr uint32_t TRANSACTION_getImplementationVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getFrontendIds = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getFrontend = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getDemuxIds = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getDemux = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_getCaSlotIds = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_getCaSlot = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnBroadcastManager();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnBroadcastManager

class IBroadcastManagerDelegator : public BnBroadcastManager {
public:
  explicit IBroadcastManagerDelegator(::android::sp<IBroadcastManager> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getImplementationVersion(::com::rdk::hal::broadcast::ImplementationVersion* _aidl_return) override {
    return _aidl_delegate->getImplementationVersion(_aidl_return);
  }
  ::android::binder::Status getFrontendIds(::std::vector<::com::rdk::hal::broadcast::frontend::IFrontend::Id>* _aidl_return) override {
    return _aidl_delegate->getFrontendIds(_aidl_return);
  }
  ::android::binder::Status getFrontend(const ::com::rdk::hal::broadcast::frontend::IFrontend::Id& frontendId, ::android::sp<::com::rdk::hal::broadcast::frontend::IFrontend>* _aidl_return) override {
    return _aidl_delegate->getFrontend(frontendId, _aidl_return);
  }
  ::android::binder::Status getDemuxIds(::std::vector<::com::rdk::hal::broadcast::demux::IDemux::Id>* _aidl_return) override {
    return _aidl_delegate->getDemuxIds(_aidl_return);
  }
  ::android::binder::Status getDemux(const ::com::rdk::hal::broadcast::demux::IDemux::Id& demuxId, ::android::sp<::com::rdk::hal::broadcast::demux::IDemux>* _aidl_return) override {
    return _aidl_delegate->getDemux(demuxId, _aidl_return);
  }
  ::android::binder::Status getCaSlotIds(::std::vector<::com::rdk::hal::broadcast::ca::ICaSlot::Id>* _aidl_return) override {
    return _aidl_delegate->getCaSlotIds(_aidl_return);
  }
  ::android::binder::Status getCaSlot(const ::com::rdk::hal::broadcast::ca::ICaSlot::Id& slotId, ::android::sp<::com::rdk::hal::broadcast::ca::ICaSlot>* _aidl_return) override {
    return _aidl_delegate->getCaSlot(slotId, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnBroadcastManager::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IBroadcastManager> _aidl_delegate;
};  // class IBroadcastManagerDelegator
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
