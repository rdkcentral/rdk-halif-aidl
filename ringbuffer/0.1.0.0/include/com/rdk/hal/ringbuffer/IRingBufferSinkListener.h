#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/ringbuffer/RingBufferErrorCode.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
class IRingBufferSinkListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(RingBufferSinkListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  virtual ::android::binder::Status onSpaceAvailable(int32_t bytes) = 0;
  virtual ::android::binder::Status onFlushRequested() = 0;
  virtual ::android::binder::Status onError(::com::rdk::hal::ringbuffer::RingBufferErrorCode code, const ::android::String16& message) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IRingBufferSinkListener

class IRingBufferSinkListenerDefault : public IRingBufferSinkListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onSpaceAvailable(int32_t /*bytes*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onFlushRequested() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onError(::com::rdk::hal::ringbuffer::RingBufferErrorCode /*code*/, const ::android::String16& /*message*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IRingBufferSinkListenerDefault
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
