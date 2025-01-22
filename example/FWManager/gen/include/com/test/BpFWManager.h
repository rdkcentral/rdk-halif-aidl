#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/test/IFWManager.h>

namespace com {
namespace test {
class BpFWManager : public ::android::BpInterface<IFWManager> {
public:
  explicit BpFWManager(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpFWManager() = default;
  ::android::binder::Status getFirmwareVersion(::android::String16* _aidl_return) override;
  ::android::binder::Status getCurrentBootBank(int32_t* _aidl_return) override;
  ::android::binder::Status triggerFirmwareUpdateCheck(bool* _aidl_return) override;
  ::android::binder::Status getFirmwareUpdateState(::com::test::FirmwareStatus* _aidl_return) override;
  ::android::binder::Status registerDeviceStateFirmwareUpdateStateChanged(const ::android::sp<::com::test::IFirmwareUpdateStateListener>& listener) override;
};  // class BpFWManager
}  // namespace test
}  // namespace com
