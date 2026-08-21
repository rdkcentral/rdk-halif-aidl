#pragma once

#include <mutex>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/broadcast/demux/IDemuxController.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class BpDemuxController : public ::android::BpInterface<IDemuxController> {
public:
  explicit BpDemuxController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpDemuxController() = default;
  ::android::binder::Status openFilter(const ::com::rdk::hal::broadcast::demux::FilterParameters& parameters, ::std::optional<::com::rdk::hal::broadcast::demux::Filter>* _aidl_return) override;
  ::android::binder::Status closeFilter(const ::com::rdk::hal::broadcast::demux::Filter& filter) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpDemuxController
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
