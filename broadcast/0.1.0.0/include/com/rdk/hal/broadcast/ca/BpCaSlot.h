#pragma once

#include <mutex>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/broadcast/ca/ICaSlot.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace ca {
class BpCaSlot : public ::android::BpInterface<ICaSlot> {
public:
  explicit BpCaSlot(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpCaSlot() = default;
  ::android::binder::Status getId(::com::rdk::hal::broadcast::ca::ICaSlot::Id* _aidl_return) override;
  ::android::binder::Status getCapabilities(::com::rdk::hal::broadcast::ca::CaCapabilities* _aidl_return) override;
  ::android::binder::Status setPower(bool enabled) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpCaSlot
}  // namespace ca
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
