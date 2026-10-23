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
 * @brief Callback interface for the producer side of IRingBuffer.
 *
 * This interface is oneway, so callbacks are dispatched asynchronously and the implementation does not wait for them
 * to return. Methods on IRingBufferSink or IRingBuffer must not be called from within a callback body; the producer
 * may call them once the callback has returned.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class IRingBufferSinkListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(RingBufferSinkListener)
  static const int32_t VERSION = 1000;
  const std::string HASH = "5a1f05ac0895c7939e525e8935437358f793e70c";
  static constexpr char* HASHVALUE = "5a1f05ac0895c7939e525e8935437358f793e70c";
  // @aidl-doc
  /**
   * @brief Called when there's space available in the ring buffer for the producer to write data.
   *
   * This callback is triggered when the number of bytes available for writing in the ring buffer is greater than or
   * equal to the notification threshold set by the producer using the IRingBufferSink::setNotificationThreshold
   * method.
   *
   * Once the threshold has been reached, the producer will not receive any further notifications until the free space
   * in the ring buffer drops below the threshold and then reaches or exceeds it again. This is to prevent flooding
   * the producer with notifications when the ring buffer is already full and the producer is not able to write any
   * data.
   *
   * @param bytes The number of bytes available for writing.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onSpaceAvailable(int32_t bytes) = 0;
  // @aidl-doc
  /**
   * @brief Called when the consumer side has requested a flush of the ring buffer.
   *
   * This can be used by the producer to flush any internal buffers or data sources to ensure no stale data will be
   * written to the ring buffer going forward.
   *
   * The producer should abandon any write in progress at the earliest opportunity: stop writing into the region it
   * currently holds, release it committing nothing, release(id, 0), and acquire a fresh region before writing new
   * data. The ring buffer must invalidate any data released by the producer through acquire results obtained before
   * or during a flush operation.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onFlushRequested() = 0;
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
  ::android::binder::Status onError(::com::rdk::hal::ringbuffer::RingBufferErrorCode /*code*/, const ::std::string& /*message*/) override {
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
