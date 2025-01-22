#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/test/FirmwareStatus.h>
#include <utils/StrongPointer.h>

namespace com {
namespace test {
class IFirmwareUpdateStateListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(FirmwareUpdateStateListener)
  virtual ::android::binder::Status onFirmwareUpdateStateChanged(const ::com::test::FirmwareStatus& status) = 0;
};  // class IFirmwareUpdateStateListener

class IFirmwareUpdateStateListenerDefault : public IFirmwareUpdateStateListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onFirmwareUpdateStateChanged(const ::com::test::FirmwareStatus& /*status*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
};  // class IFirmwareUpdateStateListenerDefault
}  // namespace test
}  // namespace com
