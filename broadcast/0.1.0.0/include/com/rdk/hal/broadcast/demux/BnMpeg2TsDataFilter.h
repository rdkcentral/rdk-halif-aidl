#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/broadcast/demux/IMpeg2TsDataFilter.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class BnMpeg2TsDataFilter : public ::android::BnInterface<IMpeg2TsDataFilter> {
public:
  static constexpr uint32_t TRANSACTION_setPids = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_setAllPids = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_maxPids = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_registerConsumer = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_unregisterConsumer = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnMpeg2TsDataFilter();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnMpeg2TsDataFilter

class IMpeg2TsDataFilterDelegator : public BnMpeg2TsDataFilter {
public:
  explicit IMpeg2TsDataFilterDelegator(::android::sp<IMpeg2TsDataFilter> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status setPids(const ::std::vector<int32_t>& pids) override {
    return _aidl_delegate->setPids(pids);
  }
  ::android::binder::Status setAllPids() override {
    return _aidl_delegate->setAllPids();
  }
  ::android::binder::Status maxPids(int32_t* _aidl_return) override {
    return _aidl_delegate->maxPids(_aidl_return);
  }
  ::android::binder::Status registerConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSourceListener>& listener, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>* _aidl_return) override {
    return _aidl_delegate->registerConsumer(listener, _aidl_return);
  }
  ::android::binder::Status unregisterConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>& consumer) override {
    return _aidl_delegate->unregisterConsumer(consumer);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnMpeg2TsDataFilter::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IMpeg2TsDataFilter> _aidl_delegate;
};  // class IMpeg2TsDataFilterDelegator
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
