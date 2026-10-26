#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/compositeinput/ICompositeInputController.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
class BpCompositeInputController : public ::android::BpInterface<ICompositeInputController> {
public:
  explicit BpCompositeInputController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCompositeInputController() = default;
  ::android::binder::Status start() override;
  ::android::binder::Status stop() override;
  ::android::binder::Status setProperty(::com::rdk::hal::compositeinput::PortProperty property, const ::com::rdk::hal::PropertyValue& value) override;
  ::android::binder::Status setPropertyMulti(const ::std::vector<::com::rdk::hal::compositeinput::PropertyKVPair>& properties) override;
  ::android::binder::Status resetMetrics() override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpCompositeInputController
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
