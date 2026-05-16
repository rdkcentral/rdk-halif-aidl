#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/videosink/IVideoSinkManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
class BnVideoSinkManager : public ::android::BnInterface<IVideoSinkManager> {
public:
  static constexpr uint32_t TRANSACTION_getVideoSinkIds = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getVideoSink = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnVideoSinkManager();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnVideoSinkManager

class IVideoSinkManagerDelegator : public BnVideoSinkManager {
public:
  explicit IVideoSinkManagerDelegator(::android::sp<IVideoSinkManager> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getVideoSinkIds(::std::vector<::com::rdk::hal::videosink::IVideoSink::Id>* _aidl_return) override {
    return _aidl_delegate->getVideoSinkIds(_aidl_return);
  }
  ::android::binder::Status getVideoSink(const ::com::rdk::hal::videosink::IVideoSink::Id& videoSinkId, ::android::sp<::com::rdk::hal::videosink::IVideoSink>* _aidl_return) override {
    return _aidl_delegate->getVideoSink(videoSinkId, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnVideoSinkManager::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IVideoSinkManager> _aidl_delegate;
};  // class IVideoSinkManagerDelegator
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
