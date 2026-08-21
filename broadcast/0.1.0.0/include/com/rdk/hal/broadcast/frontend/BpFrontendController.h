#pragma once

#include <mutex>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/broadcast/frontend/IFrontendController.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class BpFrontendController : public ::android::BpInterface<IFrontendController> {
public:
  explicit BpFrontendController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpFrontendController() = default;
  ::android::binder::Status tune(const ::com::rdk::hal::broadcast::frontend::TuneParameters& tuneParams) override;
  ::android::binder::Status stopTune() override;
  ::android::binder::Status getTuneStatus(::com::rdk::hal::broadcast::frontend::TuneStatus* _aidl_return) override;
  ::android::binder::Status getSignalInfo(const ::std::vector<::com::rdk::hal::broadcast::frontend::SignalInfoProperty>& properties, ::std::vector<::com::rdk::hal::broadcast::frontend::IFrontendController::SignalInfoReturn>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpFrontendController
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
