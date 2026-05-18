#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/drm/IDrmFactory.h>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
class BpDrmFactory : public ::android::BpInterface<IDrmFactory> {
public:
  explicit BpDrmFactory(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpDrmFactory() = default;
  ::android::binder::Status createDrmPlugin(const ::com::rdk::hal::drm::Uuid& uuid, const ::android::String16& appPackageName, ::android::sp<::com::rdk::hal::drm::IDrmPlugin>* _aidl_return) override;
  ::android::binder::Status createCryptoPlugin(const ::com::rdk::hal::drm::Uuid& uuid, const ::std::vector<uint8_t>& initData, ::android::sp<::com::rdk::hal::drm::ICryptoPlugin>* _aidl_return) override;
  ::android::binder::Status getSupportedCryptoSchemes(::com::rdk::hal::drm::CryptoSchemes* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpDrmFactory
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
