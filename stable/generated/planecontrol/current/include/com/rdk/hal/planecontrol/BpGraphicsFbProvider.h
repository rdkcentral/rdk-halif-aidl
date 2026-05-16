#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/planecontrol/IGraphicsFbProvider.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
class BpGraphicsFbProvider : public ::android::BpInterface<IGraphicsFbProvider> {
public:
  explicit BpGraphicsFbProvider(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpGraphicsFbProvider() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::planecontrol::GraphicsFbCapabilities* _aidl_return) override;
  ::android::binder::Status commitGraphicsFb(int32_t graphicsFbId, bool* _aidl_return) override;
  ::android::binder::Status createGraphicsFb(int32_t width, int32_t height, ::com::rdk::hal::planecontrol::GraphicsFbInfo* outInfo, ::android::os::ParcelFileDescriptor* _aidl_return) override;
  ::android::binder::Status destroyGraphicsFb(int32_t graphicsFbId) override;
  ::android::binder::Status getNativeDisplayHandle(int64_t* _aidl_return) override;
  ::android::binder::Status getEGLPlatformType(int32_t* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpGraphicsFbProvider
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
