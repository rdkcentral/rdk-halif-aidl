#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace avbuffer {
class IAVBufferSpaceListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AVBufferSpaceListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "c62a3479ce54c9d91be8a5a959a39b40ce7296b8";
  static constexpr char* HASHVALUE = "c62a3479ce54c9d91be8a5a959a39b40ce7296b8";
  virtual ::android::binder::Status onSpaceAvailable() = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAVBufferSpaceListener

class IAVBufferSpaceListenerDefault : public IAVBufferSpaceListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onSpaceAvailable() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAVBufferSpaceListenerDefault
}  // namespace avbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
