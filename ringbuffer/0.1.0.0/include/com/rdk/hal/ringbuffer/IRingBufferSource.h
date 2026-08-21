#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/ParcelFileDescriptor.h>
#include <binder/Status.h>
#include <com/rdk/hal/ringbuffer/RingBufferAcquireResult.h>
#include <com/rdk/hal/ringbuffer/RingBufferInfo.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
class IRingBufferSource : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(RingBufferSource)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  virtual ::android::binder::Status getFileDescriptor(::android::os::ParcelFileDescriptor* _aidl_return) = 0;
  virtual ::android::binder::Status getInfo(::com::rdk::hal::ringbuffer::RingBufferInfo* _aidl_return) = 0;
  virtual ::android::binder::Status setNotificationThreshold(int32_t bytes) = 0;
  virtual ::android::binder::Status acquire(int32_t bytes, ::std::optional<::com::rdk::hal::ringbuffer::RingBufferAcquireResult>* _aidl_return) = 0;
  virtual ::android::binder::Status release(const ::com::rdk::hal::ringbuffer::RingBufferAcquireResult::Id& id) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IRingBufferSource

class IRingBufferSourceDefault : public IRingBufferSource {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getFileDescriptor(::android::os::ParcelFileDescriptor* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getInfo(::com::rdk::hal::ringbuffer::RingBufferInfo* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setNotificationThreshold(int32_t /*bytes*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status acquire(int32_t /*bytes*/, ::std::optional<::com::rdk::hal::ringbuffer::RingBufferAcquireResult>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status release(const ::com::rdk::hal::ringbuffer::RingBufferAcquireResult::Id& /*id*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IRingBufferSourceDefault
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
