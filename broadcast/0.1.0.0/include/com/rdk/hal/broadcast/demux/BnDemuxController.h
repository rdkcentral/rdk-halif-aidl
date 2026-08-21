#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/broadcast/demux/IDemuxController.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class BnDemuxController : public ::android::BnInterface<IDemuxController> {
public:
  static constexpr uint32_t TRANSACTION_openFilter = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_closeFilter = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnDemuxController();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnDemuxController

class IDemuxControllerDelegator : public BnDemuxController {
public:
  explicit IDemuxControllerDelegator(::android::sp<IDemuxController> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status openFilter(const ::com::rdk::hal::broadcast::demux::FilterParameters& parameters, ::std::optional<::com::rdk::hal::broadcast::demux::Filter>* _aidl_return) override {
    return _aidl_delegate->openFilter(parameters, _aidl_return);
  }
  ::android::binder::Status closeFilter(const ::com::rdk::hal::broadcast::demux::Filter& filter) override {
    return _aidl_delegate->closeFilter(filter);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnDemuxController::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IDemuxController> _aidl_delegate;
};  // class IDemuxControllerDelegator
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
