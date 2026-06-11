#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiomixer/IAudioCapture.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BpAudioCapture : public ::android::BpInterface<IAudioCapture> {
public:
  explicit BpAudioCapture(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioCapture() = default;
  ::android::binder::Status getSharedMemory(::std::vector<int64_t>* sharedMemorySizeBytes, ::android::os::ParcelFileDescriptor* _aidl_return) override;
  ::android::binder::Status releaseSharedMemory() override;
  ::android::binder::Status start() override;
  ::android::binder::Status stop() override;
  ::android::binder::Status releaseData(int64_t offsetBytes, int32_t lengthBytes) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioCapture
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
