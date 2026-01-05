#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/videodecoder/IVideoDecoderControllerListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
class BnVideoDecoderControllerListener : public ::android::BnInterface<IVideoDecoderControllerListener> {
public:
  static constexpr uint32_t TRANSACTION_onFrameOutput = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onUserDataOutput = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnVideoDecoderControllerListener();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnVideoDecoderControllerListener

class IVideoDecoderControllerListenerDelegator : public BnVideoDecoderControllerListener {
public:
  explicit IVideoDecoderControllerListenerDelegator(::android::sp<IVideoDecoderControllerListener> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status onFrameOutput(int64_t nsPresentationTime, int64_t frameBufferHandle, const ::std::optional<::com::rdk::hal::videodecoder::FrameMetadata>& metadata) override {
    return _aidl_delegate->onFrameOutput(nsPresentationTime, frameBufferHandle, metadata);
  }
  ::android::binder::Status onUserDataOutput(int64_t nsPresentationTime, const ::std::vector<uint8_t>& userData) override {
    return _aidl_delegate->onUserDataOutput(nsPresentationTime, userData);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnVideoDecoderControllerListener::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IVideoDecoderControllerListener> _aidl_delegate;
};  // class IVideoDecoderControllerListenerDelegator
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
