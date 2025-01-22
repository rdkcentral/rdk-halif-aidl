#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/test/IFirmwareUpdateStateListener.h>

namespace com {
namespace test {
class BpFirmwareUpdateStateListener : public ::android::BpInterface<IFirmwareUpdateStateListener> {
public:
  explicit BpFirmwareUpdateStateListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpFirmwareUpdateStateListener() = default;
  ::android::binder::Status onFirmwareUpdateStateChanged(const ::com::test::FirmwareStatus& status) override;
};  // class BpFirmwareUpdateStateListener
}  // namespace test
}  // namespace com
