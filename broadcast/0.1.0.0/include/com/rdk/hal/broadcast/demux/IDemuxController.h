#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/demux/Filter.h>
#include <com/rdk/hal/broadcast/demux/FilterParameters.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class IDemuxController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DemuxController)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  virtual ::android::binder::Status openFilter(const ::com::rdk::hal::broadcast::demux::FilterParameters& parameters, ::std::optional<::com::rdk::hal::broadcast::demux::Filter>* _aidl_return) = 0;
  virtual ::android::binder::Status closeFilter(const ::com::rdk::hal::broadcast::demux::Filter& filter) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IDemuxController

class IDemuxControllerDefault : public IDemuxController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status openFilter(const ::com::rdk::hal::broadcast::demux::FilterParameters& /*parameters*/, ::std::optional<::com::rdk::hal::broadcast::demux::Filter>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status closeFilter(const ::com::rdk::hal::broadcast::demux::Filter& /*filter*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IDemuxControllerDefault
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
