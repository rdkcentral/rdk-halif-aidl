#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/compositeinput/ICompositeInputEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
class BpCompositeInputEventListener : public ::android::BpInterface<ICompositeInputEventListener> {
public:
  explicit BpCompositeInputEventListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCompositeInputEventListener() = default;
  ::android::binder::Status onStateChanged(::com::rdk::hal::compositeinput::State oldState, ::com::rdk::hal::compositeinput::State newState) override;
  ::android::binder::Status onPropertyChanged(::com::rdk::hal::compositeinput::PortProperty property, const ::com::rdk::hal::PropertyValue& value) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpCompositeInputEventListener
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
