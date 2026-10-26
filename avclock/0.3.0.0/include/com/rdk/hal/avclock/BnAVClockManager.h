#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/avclock/IAVClockManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
class BnAVClockManager : public ::android::BnInterface<IAVClockManager> {
public:
  static constexpr uint32_t TRANSACTION_getAVClockIds = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getAVClock = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAVClockManager();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAVClockManager

class IAVClockManagerDelegator : public BnAVClockManager {
public:
  explicit IAVClockManagerDelegator(::android::sp<IAVClockManager> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getAVClockIds(::std::vector<::com::rdk::hal::avclock::IAVClock::Id>* _aidl_return) override {
    return _aidl_delegate->getAVClockIds(_aidl_return);
  }
  ::android::binder::Status getAVClock(const ::com::rdk::hal::avclock::IAVClock::Id& avClockId, ::android::sp<::com::rdk::hal::avclock::IAVClock>* _aidl_return) override {
    return _aidl_delegate->getAVClock(avClockId, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAVClockManager::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAVClockManager> _aidl_delegate;
};  // class IAVClockManagerDelegator
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
