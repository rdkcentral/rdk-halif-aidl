#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSource.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSourceListener.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class IMpeg2TsDataFilter : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(Mpeg2TsDataFilter)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  virtual ::android::binder::Status setPids(const ::std::vector<int32_t>& pids) = 0;
  virtual ::android::binder::Status setAllPids() = 0;
  virtual ::android::binder::Status maxPids(int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status registerConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSourceListener>& listener, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>* _aidl_return) = 0;
  virtual ::android::binder::Status unregisterConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>& consumer) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IMpeg2TsDataFilter

class IMpeg2TsDataFilterDefault : public IMpeg2TsDataFilter {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status setPids(const ::std::vector<int32_t>& /*pids*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setAllPids() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status maxPids(int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSourceListener>& /*listener*/, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>& /*consumer*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IMpeg2TsDataFilterDefault
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
