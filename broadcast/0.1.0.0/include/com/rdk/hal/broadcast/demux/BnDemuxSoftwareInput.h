#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/broadcast/demux/IDemuxSoftwareInput.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class BnDemuxSoftwareInput : public ::android::BnInterface<IDemuxSoftwareInput> {
public:
  static constexpr uint32_t TRANSACTION_getId = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_openForWriting = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_closeForWriting = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_acquireDataProvider = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_releaseDataProvider = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnDemuxSoftwareInput();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnDemuxSoftwareInput

class IDemuxSoftwareInputDelegator : public BnDemuxSoftwareInput {
public:
  explicit IDemuxSoftwareInputDelegator(::android::sp<IDemuxSoftwareInput> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getId(::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id* _aidl_return) override {
    return _aidl_delegate->getId(_aidl_return);
  }
  ::android::binder::Status openForWriting(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSinkListener>& listener, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>* _aidl_return) override {
    return _aidl_delegate->openForWriting(listener, _aidl_return);
  }
  ::android::binder::Status closeForWriting(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>& bufferSink) override {
    return _aidl_delegate->closeForWriting(bufferSink);
  }
  ::android::binder::Status acquireDataProvider(::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>* _aidl_return) override {
    return _aidl_delegate->acquireDataProvider(_aidl_return);
  }
  ::android::binder::Status releaseDataProvider(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>& provider) override {
    return _aidl_delegate->releaseDataProvider(provider);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnDemuxSoftwareInput::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IDemuxSoftwareInput> _aidl_delegate;
};  // class IDemuxSoftwareInputDelegator
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
