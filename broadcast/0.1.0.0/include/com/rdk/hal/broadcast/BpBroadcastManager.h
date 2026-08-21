#pragma once

#include <mutex>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/broadcast/IBroadcastManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
class BpBroadcastManager : public ::android::BpInterface<IBroadcastManager> {
public:
  explicit BpBroadcastManager(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpBroadcastManager() = default;
  ::android::binder::Status getImplementationVersion(::com::rdk::hal::broadcast::ImplementationVersion* _aidl_return) override;
  ::android::binder::Status getFrontendIds(::std::vector<::com::rdk::hal::broadcast::frontend::IFrontend::Id>* _aidl_return) override;
  ::android::binder::Status getFrontend(const ::com::rdk::hal::broadcast::frontend::IFrontend::Id& frontendId, ::android::sp<::com::rdk::hal::broadcast::frontend::IFrontend>* _aidl_return) override;
  ::android::binder::Status getDemuxIds(::std::vector<::com::rdk::hal::broadcast::demux::IDemux::Id>* _aidl_return) override;
  ::android::binder::Status getDemux(const ::com::rdk::hal::broadcast::demux::IDemux::Id& demuxId, ::android::sp<::com::rdk::hal::broadcast::demux::IDemux>* _aidl_return) override;
  ::android::binder::Status getCaSlotIds(::std::vector<::com::rdk::hal::broadcast::ca::ICaSlot::Id>* _aidl_return) override;
  ::android::binder::Status getCaSlot(const ::com::rdk::hal::broadcast::ca::ICaSlot::Id& slotId, ::android::sp<::com::rdk::hal::broadcast::ca::ICaSlot>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpBroadcastManager
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
