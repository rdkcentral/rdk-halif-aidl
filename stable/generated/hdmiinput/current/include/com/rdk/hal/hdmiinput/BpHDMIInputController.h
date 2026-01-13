#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/hdmiinput/IHDMIInputController.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
class BpHDMIInputController : public ::android::BpInterface<IHDMIInputController> {
public:
  explicit BpHDMIInputController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHDMIInputController() = default;
  ::android::binder::Status getConnectionState(bool* _aidl_return) override;
  ::android::binder::Status start() override;
  ::android::binder::Status stop() override;
  ::android::binder::Status setProperty(::com::rdk::hal::hdmiinput::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) override;
  ::android::binder::Status setPropertyMulti(const ::std::vector<::com::rdk::hal::hdmiinput::PropertyKVPair>& propertyKVList, bool* _aidl_return) override;
  ::android::binder::Status setEDID(const ::std::vector<uint8_t>& edid, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpHDMIInputController
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
