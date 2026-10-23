#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/broadcast/demux/IVideoFilter.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class BnVideoFilter : public ::android::BnInterface<IVideoFilter> {
public:
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnVideoFilter();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnVideoFilter

class IVideoFilterDelegator : public BnVideoFilter {
public:
  explicit IVideoFilterDelegator(::android::sp<IVideoFilter> &impl) : _aidl_delegate(impl) {}

  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnVideoFilter::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IVideoFilter> _aidl_delegate;
};  // class IVideoFilterDelegator
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
