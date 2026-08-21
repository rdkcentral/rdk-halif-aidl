#pragma once

#include <mutex>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/broadcast/demux/IDemux.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class BpDemux : public ::android::BpInterface<IDemux> {
public:
  explicit BpDemux(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpDemux() = default;
  ::android::binder::Status getId(::com::rdk::hal::broadcast::demux::IDemux::Id* _aidl_return) override;
  ::android::binder::Status isConnected(bool* _aidl_return) override;
  ::android::binder::Status getCapabilities(::com::rdk::hal::broadcast::demux::DemuxCapabilities* _aidl_return) override;
  ::android::binder::Status connect(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>& provider, ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxController>* _aidl_return) override;
  ::android::binder::Status disconnect(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxController>& controller, ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>* _aidl_return) override;
  ::android::binder::Status createSoftwareInput(::std::optional<::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id>* _aidl_return) override;
  ::android::binder::Status destroySoftwareInput(const ::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id& id) override;
  ::android::binder::Status acquireSoftwareInput(const ::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id& id, ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput>* _aidl_return) override;
  ::android::binder::Status releaseSoftwareInput(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput>& input) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpDemux
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
