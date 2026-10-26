#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/broadcast/demux/IAudioFilter.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class BnAudioFilter : public ::android::BnInterface<IAudioFilter> {
public:
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAudioFilter();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAudioFilter

class IAudioFilterDelegator : public BnAudioFilter {
public:
  explicit IAudioFilterDelegator(::android::sp<IAudioFilter> &impl) : _aidl_delegate(impl) {}

  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAudioFilter::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAudioFilter> _aidl_delegate;
};  // class IAudioFilterDelegator
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
