#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/videosink/IVideoSinkManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
class BpVideoSinkManager : public ::android::BpInterface<IVideoSinkManager> {
public:
  explicit BpVideoSinkManager(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpVideoSinkManager() = default;
  ::android::binder::Status getVideoSinkIds(::std::vector<::com::rdk::hal::videosink::IVideoSink::Id>* _aidl_return) override;
  ::android::binder::Status getVideoSink(const ::com::rdk::hal::videosink::IVideoSink::Id& videoSinkId, ::android::sp<::com::rdk::hal::videosink::IVideoSink>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpVideoSinkManager
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
