#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/videodecoder/IVideoDecoderController.h>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
class BnVideoDecoderController : public ::android::BnInterface<IVideoDecoderController> {
public:
  static constexpr uint32_t TRANSACTION_start = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_stop = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_setProperty = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_decodeBufferWithMetadata = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_flush = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_signalDiscontinuity = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_parseCodecSpecificData = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_setMasteringDisplayInfo = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_setContentLightLevel = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_setColorimetry = ::android::IBinder::FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_setStreamResolution = ::android::IBinder::FIRST_CALL_TRANSACTION + 10;
  static constexpr uint32_t TRANSACTION_setFrameRate = ::android::IBinder::FIRST_CALL_TRANSACTION + 11;
  static constexpr uint32_t TRANSACTION_setDolbyVisionLayerFlags = ::android::IBinder::FIRST_CALL_TRANSACTION + 12;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnVideoDecoderController();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnVideoDecoderController

class IVideoDecoderControllerDelegator : public BnVideoDecoderController {
public:
  explicit IVideoDecoderControllerDelegator(::android::sp<IVideoDecoderController> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status start() override {
    return _aidl_delegate->start();
  }
  ::android::binder::Status stop() override {
    return _aidl_delegate->stop();
  }
  ::android::binder::Status setProperty(::com::rdk::hal::videodecoder::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) override {
    return _aidl_delegate->setProperty(property, propertyValue, _aidl_return);
  }
  ::android::binder::Status decodeBufferWithMetadata(int64_t bufferHandle, const ::com::rdk::hal::videodecoder::InputBufferMetadata& metadata, bool* _aidl_return) override {
    return _aidl_delegate->decodeBufferWithMetadata(bufferHandle, metadata, _aidl_return);
  }
  ::android::binder::Status flush(bool reset) override {
    return _aidl_delegate->flush(reset);
  }
  ::android::binder::Status signalDiscontinuity() override {
    return _aidl_delegate->signalDiscontinuity();
  }
  ::android::binder::Status parseCodecSpecificData(::com::rdk::hal::videodecoder::CSDVideoFormat csdVideoFormat, const ::std::vector<uint8_t>& codecData, bool* _aidl_return) override {
    return _aidl_delegate->parseCodecSpecificData(csdVideoFormat, codecData, _aidl_return);
  }
  ::android::binder::Status setMasteringDisplayInfo(const ::std::optional<::com::rdk::hal::videodecoder::MasteringDisplayInfo>& info) override {
    return _aidl_delegate->setMasteringDisplayInfo(info);
  }
  ::android::binder::Status setContentLightLevel(const ::std::optional<::com::rdk::hal::videodecoder::ContentLightLevel>& info) override {
    return _aidl_delegate->setContentLightLevel(info);
  }
  ::android::binder::Status setColorimetry(::com::rdk::hal::videodecoder::Colorimetry colorimetry) override {
    return _aidl_delegate->setColorimetry(colorimetry);
  }
  ::android::binder::Status setStreamResolution(int32_t width, int32_t height) override {
    return _aidl_delegate->setStreamResolution(width, height);
  }
  ::android::binder::Status setFrameRate(int32_t numerator, int32_t denominator) override {
    return _aidl_delegate->setFrameRate(numerator, denominator);
  }
  ::android::binder::Status setDolbyVisionLayerFlags(bool blPresent, bool elPresent) override {
    return _aidl_delegate->setDolbyVisionLayerFlags(blPresent, elPresent);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnVideoDecoderController::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IVideoDecoderController> _aidl_delegate;
};  // class IVideoDecoderControllerDelegator
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
