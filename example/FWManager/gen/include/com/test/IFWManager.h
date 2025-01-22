#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/test/FirmwareStatus.h>
#include <com/test/IFirmwareUpdateStateListener.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace test {
class IFWManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(FWManager)
  virtual ::android::binder::Status getFirmwareVersion(::android::String16* _aidl_return) = 0;
  virtual ::android::binder::Status getCurrentBootBank(int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status triggerFirmwareUpdateCheck(bool* _aidl_return) = 0;
  virtual ::android::binder::Status getFirmwareUpdateState(::com::test::FirmwareStatus* _aidl_return) = 0;
  virtual ::android::binder::Status registerDeviceStateFirmwareUpdateStateChanged(const ::android::sp<::com::test::IFirmwareUpdateStateListener>& listener) = 0;
};  // class IFWManager

class IFWManagerDefault : public IFWManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getFirmwareVersion(::android::String16* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCurrentBootBank(int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status triggerFirmwareUpdateCheck(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getFirmwareUpdateState(::com::test::FirmwareStatus* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerDeviceStateFirmwareUpdateStateChanged(const ::android::sp<::com::test::IFirmwareUpdateStateListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
};  // class IFWManagerDefault
}  // namespace test
}  // namespace com
