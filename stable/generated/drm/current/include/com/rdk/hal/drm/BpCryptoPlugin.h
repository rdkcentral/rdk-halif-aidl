#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/drm/ICryptoPlugin.h>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class BpCryptoPlugin : public ::android::BpInterface<ICryptoPlugin> {
public:
  explicit BpCryptoPlugin(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCryptoPlugin() = default;
  ::android::binder::Status decrypt(const ::com::rdk::hal::drm::DecryptArgs& args, int32_t* _aidl_return) override;
  ::android::binder::Status notifyResolution(int32_t width, int32_t height) override;
  ::android::binder::Status requiresSecureDecoderComponent(const ::android::String16& mime, bool* _aidl_return) override;
  ::android::binder::Status setMediaDrmSession(const ::std::vector<uint8_t>& sessionId) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpCryptoPlugin
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
