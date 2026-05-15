#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/avclock/ClockMode.h>
#include <com/rdk/hal/avclock/ClockTime.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
class IAVClockController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AVClockController)
  static const int32_t VERSION = 1;
  const std::string HASH = "d051db1ab923600cfd13f483cfb327fb70c083af";
  static constexpr char* HASHVALUE = "d051db1ab923600cfd13f483cfb327fb70c083af";
  virtual ::android::binder::Status start() = 0;
  virtual ::android::binder::Status stop() = 0;
  virtual ::android::binder::Status setClockMode(::com::rdk::hal::avclock::ClockMode clockMode, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getClockMode(::com::rdk::hal::avclock::ClockMode* _aidl_return) = 0;
  virtual ::android::binder::Status notifyPCRSample(int64_t pcrTimeNs, int64_t sampleTimestampNs, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getCurrentClockTime(::std::optional<::com::rdk::hal::avclock::ClockTime>* _aidl_return) = 0;
  virtual ::android::binder::Status setPlaybackRate(double rate, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getPlaybackRate(double* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAVClockController

class IAVClockControllerDefault : public IAVClockController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status start() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setClockMode(::com::rdk::hal::avclock::ClockMode /*clockMode*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getClockMode(::com::rdk::hal::avclock::ClockMode* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status notifyPCRSample(int64_t /*pcrTimeNs*/, int64_t /*sampleTimestampNs*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCurrentClockTime(::std::optional<::com::rdk::hal::avclock::ClockTime>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPlaybackRate(double /*rate*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPlaybackRate(double* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAVClockControllerDefault
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
