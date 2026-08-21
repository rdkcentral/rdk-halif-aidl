#pragma once

#include <mutex>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/broadcast/frontend/IFrontend.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class BpFrontend : public ::android::BpInterface<IFrontend> {
public:
  explicit BpFrontend(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpFrontend() = default;
  ::android::binder::Status getId(::com::rdk::hal::broadcast::frontend::IFrontend::Id* _aidl_return) override;
  ::android::binder::Status isOpen(bool* _aidl_return) override;
  ::android::binder::Status getFrontendTypes(::std::vector<::com::rdk::hal::broadcast::frontend::FrontendType>* _aidl_return) override;
  ::android::binder::Status getCapabilities(::com::rdk::hal::broadcast::frontend::FrontendType frontendType, ::std::optional<::com::rdk::hal::broadcast::frontend::FrontendCapabilities>* _aidl_return) override;
  ::android::binder::Status open(::android::sp<::com::rdk::hal::broadcast::frontend::IFrontendController>* _aidl_return) override;
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::broadcast::frontend::IFrontendController>& controller) override;
  ::android::binder::Status acquireDataProvider(::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>* _aidl_return) override;
  ::android::binder::Status releaseDataProvider(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>& provider) override;
  ::android::binder::Status openLnb(::android::sp<::com::rdk::hal::broadcast::frontend::ILnbController>* _aidl_return) override;
  ::android::binder::Status closeLnb(const ::android::sp<::com::rdk::hal::broadcast::frontend::ILnbController>& controller) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpFrontend
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
