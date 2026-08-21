#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/broadcast/demux/IClockFilter.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class BnClockFilter : public ::android::BnInterface<IClockFilter> {
public:
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnClockFilter();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnClockFilter

class IClockFilterDelegator : public BnClockFilter {
public:
  explicit IClockFilterDelegator(::android::sp<IClockFilter> &impl) : _aidl_delegate(impl) {}

  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnClockFilter::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IClockFilter> _aidl_delegate;
};  // class IClockFilterDelegator
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
