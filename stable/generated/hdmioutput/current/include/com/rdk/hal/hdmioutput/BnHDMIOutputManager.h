#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/hdmioutput/IHDMIOutputManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
class BnHDMIOutputManager : public ::android::BnInterface<IHDMIOutputManager> {
public:
  static constexpr uint32_t TRANSACTION_getCapabilities = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getHDMIOutputIds = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getHDMIOutput = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnHDMIOutputManager();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnHDMIOutputManager

class IHDMIOutputManagerDelegator : public BnHDMIOutputManager {
public:
  explicit IHDMIOutputManagerDelegator(::android::sp<IHDMIOutputManager> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getCapabilities(::com::rdk::hal::hdmioutput::PlatformCapabilities* _aidl_return) override {
    return _aidl_delegate->getCapabilities(_aidl_return);
  }
  ::android::binder::Status getHDMIOutputIds(::std::vector<::com::rdk::hal::hdmioutput::IHDMIOutput::Id>* _aidl_return) override {
    return _aidl_delegate->getHDMIOutputIds(_aidl_return);
  }
  ::android::binder::Status getHDMIOutput(const ::com::rdk::hal::hdmioutput::IHDMIOutput::Id& hdmiOutputId, ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutput>* _aidl_return) override {
    return _aidl_delegate->getHDMIOutput(hdmiOutputId, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnHDMIOutputManager::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IHDMIOutputManager> _aidl_delegate;
};  // class IHDMIOutputManagerDelegator
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
