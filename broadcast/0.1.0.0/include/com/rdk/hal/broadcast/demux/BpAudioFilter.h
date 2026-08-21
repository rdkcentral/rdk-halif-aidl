#pragma once

#include <mutex>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/broadcast/demux/IAudioFilter.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class BpAudioFilter : public ::android::BpInterface<IAudioFilter> {
public:
  explicit BpAudioFilter(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioFilter() = default;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioFilter
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
