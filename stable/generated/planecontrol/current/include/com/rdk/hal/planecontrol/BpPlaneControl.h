#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/planecontrol/IPlaneControl.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
class BpPlaneControl : public ::android::BpInterface<IPlaneControl> {
public:
  explicit BpPlaneControl(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpPlaneControl() = default;
  ::android::binder::Status getCapabilities(::std::vector<::com::rdk::hal::planecontrol::Capabilities>* _aidl_return) override;
  ::android::binder::Status getNativeGraphicsWindowHandle(int32_t planeResourceIndex, int64_t* _aidl_return) override;
  ::android::binder::Status releaseNativeGraphicsWindowHandle(int32_t planeResourceIndex, int64_t nativeWindowHandle) override;
  ::android::binder::Status flipGraphicsBuffer(int32_t planeResourceIndex, bool* _aidl_return) override;
  ::android::binder::Status setVideoSourceDestinationPlaneMapping(const ::std::vector<::com::rdk::hal::planecontrol::SourcePlaneMapping>& listSourcePlaneMapping, bool* _aidl_return) override;
  ::android::binder::Status getVideoSourceDestinationPlaneMapping(::std::vector<::com::rdk::hal::planecontrol::SourcePlaneMapping>* _aidl_return) override;
  ::android::binder::Status getProperty(int32_t planeResourceIndex, ::com::rdk::hal::planecontrol::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) override;
  ::android::binder::Status setProperty(int32_t planeResourceIndex, ::com::rdk::hal::planecontrol::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) override;
  ::android::binder::Status getPropertyMulti(int32_t planeResourceIndex, const ::std::vector<::com::rdk::hal::planecontrol::Property>& properties, ::std::vector<::com::rdk::hal::planecontrol::PropertyKVPair>* propertyKVList, bool* _aidl_return) override;
  ::android::binder::Status setPropertyMultiAtomic(int32_t planeResourceIndex, const ::std::vector<::com::rdk::hal::planecontrol::PropertyKVPair>& propertyKVList, bool* _aidl_return) override;
  ::android::binder::Status registerListener(const ::android::sp<::com::rdk::hal::planecontrol::IPlaneControlListener>& listener, bool* _aidl_return) override;
  ::android::binder::Status unregisterListener(const ::android::sp<::com::rdk::hal::planecontrol::IPlaneControlListener>& listener, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpPlaneControl
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
