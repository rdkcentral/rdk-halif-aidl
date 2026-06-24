#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/videodecoder/IVideoDecoderManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
class BnVideoDecoderManager : public ::android::BnInterface<IVideoDecoderManager> {
public:
  static constexpr uint32_t TRANSACTION_getVideoDecoderIds = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getSupportedOperationalModes = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getVideoDecoder = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnVideoDecoderManager();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnVideoDecoderManager

class IVideoDecoderManagerDelegator : public BnVideoDecoderManager {
public:
  explicit IVideoDecoderManagerDelegator(::android::sp<IVideoDecoderManager> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getVideoDecoderIds(::std::vector<::com::rdk::hal::videodecoder::IVideoDecoder::Id>* _aidl_return) override {
    return _aidl_delegate->getVideoDecoderIds(_aidl_return);
  }
  ::android::binder::Status getSupportedOperationalModes(::std::vector<::com::rdk::hal::videodecoder::OperationalMode>* _aidl_return) override {
    return _aidl_delegate->getSupportedOperationalModes(_aidl_return);
  }
  ::android::binder::Status getVideoDecoder(const ::com::rdk::hal::videodecoder::IVideoDecoder::Id& videoDecoderId, ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoder>* _aidl_return) override {
    return _aidl_delegate->getVideoDecoder(videoDecoderId, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnVideoDecoderManager::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IVideoDecoderManager> _aidl_delegate;
};  // class IVideoDecoderManagerDelegator
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
