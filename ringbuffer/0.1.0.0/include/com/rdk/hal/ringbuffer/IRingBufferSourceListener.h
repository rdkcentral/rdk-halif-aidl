#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/ringbuffer/RingBufferErrorCode.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
// @aidl-doc
/**
 * @brief Callback interface for the consumer side of IRingBuffer.
 *
 * This interface is oneway, so callbacks are dispatched asynchronously and the implementation does not wait for them
 * to return. Methods on IRingBufferSource or IRingBuffer must not be called from within a callback body; the consumer
 * may call them once the callback has returned.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class IRingBufferSourceListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(RingBufferSourceListener)
  static const int32_t VERSION = 1000;
  const std::string HASH = "5a1f05ac0895c7939e525e8935437358f793e70c";
  static constexpr char* HASHVALUE = "5a1f05ac0895c7939e525e8935437358f793e70c";
  // @aidl-doc
  /**
   * @brief Called when there's data available in the ring buffer for the consumer to read.
   *
   * This callback is triggered when the number of bytes available for reading in the ring buffer is greater than or
   * equal to the notification threshold set by the consumer using the IRingBufferSource::setNotificationThreshold
   * method.
   *
   * Once the threshold has been reached, the consumer will not receive any further notifications until the readable
   * space in the ring buffer drops below the threshold and then reaches or exceeds it again. This is to prevent
   * flooding the consumer with notifications when the ring buffer is already full and the consumer is not able to
   * read any data.
   *
   * @param bytes The number of bytes available for reading.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onDataAvailable(int32_t bytes) = 0;
  // @aidl-doc
  /**
   * @brief Called on error.
   *
   * @param code The error code indicating the type of error that occurred.
   * @param message A human-readable message providing more details about the error.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onError(::com::rdk::hal::ringbuffer::RingBufferErrorCode code, const ::std::string& message) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IRingBufferSourceListener

class IRingBufferSourceListenerDefault : public IRingBufferSourceListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onDataAvailable(int32_t /*bytes*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onError(::com::rdk::hal::ringbuffer::RingBufferErrorCode /*code*/, const ::std::string& /*message*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IRingBufferSourceListenerDefault
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
