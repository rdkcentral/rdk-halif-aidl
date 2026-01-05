#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/videosink/IVideoSinkController.h>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
class BnVideoSinkController : public ::android::BnInterface<IVideoSinkController> {
public:
  static constexpr uint32_t TRANSACTION_setProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_setVideoDecoder = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getVideoDecoder = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_start = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_stop = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_queueVideoFrame = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_flush = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_discardFramesUntil = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnVideoSinkController();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnVideoSinkController

class IVideoSinkControllerDelegator : public BnVideoSinkController {
public:
  explicit IVideoSinkControllerDelegator(::android::sp<IVideoSinkController> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status setProperty(::com::rdk::hal::videosink::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) override {
    return _aidl_delegate->setProperty(property, propertyValue, _aidl_return);
  }
  ::android::binder::Status setVideoDecoder(const ::com::rdk::hal::videodecoder::IVideoDecoder::Id& videoDecoderId, bool* _aidl_return) override {
    return _aidl_delegate->setVideoDecoder(videoDecoderId, _aidl_return);
  }
  ::android::binder::Status getVideoDecoder(::com::rdk::hal::videodecoder::IVideoDecoder::Id* _aidl_return) override {
    return _aidl_delegate->getVideoDecoder(_aidl_return);
  }
  ::android::binder::Status start() override {
    return _aidl_delegate->start();
  }
  ::android::binder::Status stop() override {
    return _aidl_delegate->stop();
  }
  ::android::binder::Status queueVideoFrame(int64_t nsPresentationTime, int64_t frameBufferHandle, const ::com::rdk::hal::videodecoder::FrameMetadata& metadata, bool* _aidl_return) override {
    return _aidl_delegate->queueVideoFrame(nsPresentationTime, frameBufferHandle, metadata, _aidl_return);
  }
  ::android::binder::Status flush(bool holdLastFrame) override {
    return _aidl_delegate->flush(holdLastFrame);
  }
  ::android::binder::Status discardFramesUntil(int64_t nsPresentationTime) override {
    return _aidl_delegate->discardFramesUntil(nsPresentationTime);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnVideoSinkController::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IVideoSinkController> _aidl_delegate;
};  // class IVideoSinkControllerDelegator
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
