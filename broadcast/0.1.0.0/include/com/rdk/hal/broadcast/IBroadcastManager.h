#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/ImplementationVersion.h>
#include <com/rdk/hal/broadcast/ca/ICaSlot.h>
#include <com/rdk/hal/broadcast/demux/IDemux.h>
#include <com/rdk/hal/broadcast/frontend/IFrontend.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
class IBroadcastManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(BroadcastManager)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getImplementationVersion(::com::rdk::hal::broadcast::ImplementationVersion* _aidl_return) = 0;
  virtual ::android::binder::Status getFrontendIds(::std::vector<::com::rdk::hal::broadcast::frontend::IFrontend::Id>* _aidl_return) = 0;
  virtual ::android::binder::Status getFrontend(const ::com::rdk::hal::broadcast::frontend::IFrontend::Id& frontendId, ::android::sp<::com::rdk::hal::broadcast::frontend::IFrontend>* _aidl_return) = 0;
  virtual ::android::binder::Status getDemuxIds(::std::vector<::com::rdk::hal::broadcast::demux::IDemux::Id>* _aidl_return) = 0;
  virtual ::android::binder::Status getDemux(const ::com::rdk::hal::broadcast::demux::IDemux::Id& demuxId, ::android::sp<::com::rdk::hal::broadcast::demux::IDemux>* _aidl_return) = 0;
  virtual ::android::binder::Status getCaSlotIds(::std::vector<::com::rdk::hal::broadcast::ca::ICaSlot::Id>* _aidl_return) = 0;
  virtual ::android::binder::Status getCaSlot(const ::com::rdk::hal::broadcast::ca::ICaSlot::Id& slotId, ::android::sp<::com::rdk::hal::broadcast::ca::ICaSlot>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IBroadcastManager

class IBroadcastManagerDefault : public IBroadcastManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getImplementationVersion(::com::rdk::hal::broadcast::ImplementationVersion* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getFrontendIds(::std::vector<::com::rdk::hal::broadcast::frontend::IFrontend::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getFrontend(const ::com::rdk::hal::broadcast::frontend::IFrontend::Id& /*frontendId*/, ::android::sp<::com::rdk::hal::broadcast::frontend::IFrontend>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getDemuxIds(::std::vector<::com::rdk::hal::broadcast::demux::IDemux::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getDemux(const ::com::rdk::hal::broadcast::demux::IDemux::Id& /*demuxId*/, ::android::sp<::com::rdk::hal::broadcast::demux::IDemux>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCaSlotIds(::std::vector<::com::rdk::hal::broadcast::ca::ICaSlot::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCaSlot(const ::com::rdk::hal::broadcast::ca::ICaSlot::Id& /*slotId*/, ::android::sp<::com::rdk::hal::broadcast::ca::ICaSlot>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IBroadcastManagerDefault
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
