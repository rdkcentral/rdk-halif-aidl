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
// @aidl-doc
/**
 *  @brief     AV buffer space listener interface definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class IAVBufferSpaceListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AVBufferSpaceListener)
  static const int32_t VERSION = 2010;
  const std::string HASH = "e23536cdc5897ca90beb1b091801b131dd54541e";
  static constexpr char* HASHVALUE = "e23536cdc5897ca90beb1b091801b131dd54541e";
  // @aidl-doc
  /**
   * Callback in response to IAVBuffer.notifyWhenSpaceAvailable() when the
   * requested space for an allocation becomes available in the pool.
   *
   * @see IAVBuffer.notifyWhenSpaceAvailable()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
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
