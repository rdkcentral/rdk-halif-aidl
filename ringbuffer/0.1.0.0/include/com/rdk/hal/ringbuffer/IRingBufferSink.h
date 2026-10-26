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
// @aidl-doc
/**
 * @brief Producer side of IRingBuffer.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class IRingBufferSink : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(RingBufferSink)
  static const int32_t VERSION = 1000;
  const std::string HASH = "5a1f05ac0895c7939e525e8935437358f793e70c";
  static constexpr char* HASHVALUE = "5a1f05ac0895c7939e525e8935437358f793e70c";
  // @aidl-doc
  /**
   * @brief Get the underlying file descriptor for the ring buffer.
   *
   * The returned descriptor is a duplicate owned by the caller, which is responsible for closing it. Calling this
   * method more than once yields independent descriptors, each of which must be closed.
   *
   * The descriptor remains valid until the caller closes it, but the memory it refers to is only meaningful while
   * this producer is registered. After unregisterProducer(), or after the implementation has released the
   * registration because the producer died, the descriptor must no longer be used to read or write buffer contents:
   * the region may have been reused by a new producer. Unmap and close it as part of unregistering.
   *
   * @param[out] _aidl_return The file descriptor backing the ring buffer, to be mapped or read by the producer.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getFileDescriptor(::android::os::ParcelFileDescriptor* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Get information about the ring buffer.
   *
   * The result is a snapshot taken while the call was serviced, not a live view. The consumer runs concurrently, so
   * availableForReading may already be out of date by the time the caller inspects it and is advisory only — useful
   * for metrics or coarse decisions, but never as the basis for a write. acquire() is the authoritative operation,
   * and the bytes field of its result is the only trustworthy statement of what the caller may access. The size and
   * overflow behaviour are stable while a client is registered.
   *
   * @param[out] _aidl_return A snapshot of the ring buffer size, readable byte count and overflow behaviour.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getInfo(::com::rdk::hal::ringbuffer::RingBufferInfo* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Set the minimum number of bytes that will cause a notification.
   *
   * The producer will be notified through the IRingBufferSinkListener::onSpaceAvailable callback when the number of
   * bytes available for writing in the ring buffer is greater than or equal to the specified threshold. Once that
   * callback has returned, the producer can call acquire() to acquire the available bytes for writing. If the number
   * of bytes available for writing is already greater than or equal to the specified threshold when this method is
   * called, the producer will be notified immediately through the onSpaceAvailable callback.
   *
   * The notification threshold can be set to 0 to disable notifications.
   *
   * The default value is one, i.e. the producer will be notified as soon as there is at least one byte available for
   * writing in the ring buffer.
   *
   * @param bytes The minimum number of bytes that will cause a notification.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT If the provided threshold is less than 0 or greater
   *                                                        than the size of the ring buffer.
   */
  virtual ::android::binder::Status setNotificationThreshold(int32_t bytes) = 0;
  // @aidl-doc
  /**
   * @brief Acquire bytes for writing.
   *
   * @note If the underlying IRingBuffer is set to OverflowBehaviour.OVERFLOWING, this method will return
   * immediately with the number of bytes requested, limited by the number of continuous bytes available. It will
   * thus override data which has not yet been read by the consumer if the producer writes data faster than the
   * consumer reading it.
   *
   * @note The producer is not allowed to call this method again before releasing the bytes acquired in the previous
   * call to acquire. This is to prevent fragmentation of the ring buffer and to ensure that the producer can always
   * write to a contiguous block of memory.
   *
   * @param bytes The number of bytes to acquire for writing.
   * @param[out] _aidl_return A RingBufferAcquireResult containing the offset in the ring buffer where the producer can start writing
   *                         data and the number of bytes that were actually acquired for writing. Null, if the ring buffer is set
   *                         to OverflowBehaviour.NON_OVERFLOWING and the ring buffer is full.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If the producer has already acquired bytes and has not
   *                                                     yet released them.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT If the provided number of bytes is less than or equal
   *                                                        to 0 or greater than the size of the ring buffer.
   */
  virtual ::android::binder::Status acquire(int32_t bytes, ::std::optional<::com::rdk::hal::ringbuffer::RingBufferAcquireResult>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Release bytes in the ring buffer after writing.
   *
   * If bytes is less than the number of bytes acquired in the corresponding acquire call, the remaining bytes will be
   * dropped and not marked readable for the consumer. They can be acquired again in a subsequent call to acquire.
   *
   * @note Once this call has returned, the producer is not allowed to write to the ring buffer at the offset and size
   * returned by the corresponding acquire call anymore. The consumer is now allowed to read from the ring buffer at
   * that offset.
   *
   * @param id The ID from the corresponding acquire call to correlate the release with the acquire.
   * @param bytes The number of bytes to release after writing.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT If the provided ID does not match the ID returned by
   *                                                        the last acquire call or if the provided number of
   *                                                        bytes is less than 0 or greater than the number of
   *                                                        bytes acquired in the corresponding acquire call.
   */
  virtual ::android::binder::Status release(const ::com::rdk::hal::ringbuffer::RingBufferAcquireResult::Id& id, int32_t bytes) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IRingBufferSink

class IRingBufferSinkDefault : public IRingBufferSink {
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
  ::android::binder::Status release(const ::com::rdk::hal::ringbuffer::RingBufferAcquireResult::Id& /*id*/, int32_t /*bytes*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IRingBufferSinkDefault
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
