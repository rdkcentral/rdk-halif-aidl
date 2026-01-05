#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/avclock/IAVClock.h>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
class BpAVClock : public ::android::BpInterface<IAVClock> {
public:
  explicit BpAVClock(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAVClock() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::avclock::Capabilities* _aidl_return) override;
  ::android::binder::Status getState(::com::rdk::hal::State* _aidl_return) override;
  ::android::binder::Status getProperty(::com::rdk::hal::avclock::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) override;
  ::android::binder::Status setProperty(::com::rdk::hal::avclock::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) override;
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::avclock::IAVClockControllerListener>& avClockControllerListener, ::android::sp<::com::rdk::hal::avclock::IAVClockController>* _aidl_return) override;
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::avclock::IAVClockController>& avClockController, bool* _aidl_return) override;
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::avclock::IAVClockEventListener>& avClockEventListener, bool* _aidl_return) override;
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::avclock::IAVClockEventListener>& avClockEventListener, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAVClock
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
