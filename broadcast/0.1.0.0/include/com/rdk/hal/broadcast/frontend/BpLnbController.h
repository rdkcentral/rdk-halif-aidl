#pragma once

#include <mutex>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/broadcast/frontend/ILnbController.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class BpLnbController : public ::android::BpInterface<ILnbController> {
public:
  explicit BpLnbController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpLnbController() = default;
  ::android::binder::Status setVoltage(::com::rdk::hal::broadcast::frontend::LnbVoltage voltage) override;
  ::android::binder::Status setTone(::com::rdk::hal::broadcast::frontend::LnbTone tone) override;
  ::android::binder::Status isOverloaded(bool* _aidl_return) override;
  ::android::binder::Status sendDiseqc(const ::std::vector<uint8_t>& command) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpLnbController
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
