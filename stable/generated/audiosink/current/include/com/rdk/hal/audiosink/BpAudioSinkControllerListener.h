#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiosink/IAudioSinkControllerListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
class BpAudioSinkControllerListener : public ::android::BpInterface<IAudioSinkControllerListener> {
public:
  explicit BpAudioSinkControllerListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioSinkControllerListener() = default;
  ::android::binder::Status onStateChanged(::com::rdk::hal::State oldState, ::com::rdk::hal::State newState) override;
  ::android::binder::Status onFirstFrameRendered(int64_t nsPresentationTime) override;
  ::android::binder::Status onEndOfStream(int64_t nsPresentationTime) override;
  ::android::binder::Status onAudioUnderflow() override;
  ::android::binder::Status onAudioResumed(int64_t nsPresentationTime) override;
  ::android::binder::Status onFlushComplete() override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioSinkControllerListener
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
