#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/drm/IDrmPluginListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class BpDrmPluginListener : public ::android::BpInterface<IDrmPluginListener> {
public:
  explicit BpDrmPluginListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpDrmPluginListener() = default;
  ::android::binder::Status onEvent(::com::rdk::hal::drm::EventType eventType, const ::std::vector<uint8_t>& sessionId, const ::std::vector<uint8_t>& data) override;
  ::android::binder::Status onExpirationUpdate(const ::std::vector<uint8_t>& sessionId, int64_t expiryTimeInMS) override;
  ::android::binder::Status onKeysChange(const ::std::vector<uint8_t>& sessionId, const ::std::vector<::com::rdk::hal::drm::KeyStatus>& keyStatusList, bool hasNewUsableKey) override;
  ::android::binder::Status onSessionLostState(const ::std::vector<uint8_t>& sessionId) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpDrmPluginListener
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
