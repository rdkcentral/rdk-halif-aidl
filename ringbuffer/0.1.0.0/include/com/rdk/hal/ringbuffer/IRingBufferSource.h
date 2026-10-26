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
 * @brief Consumer side of IRingBuffer.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class IRingBufferSource : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(RingBufferSource)
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
   * this consumer is registered. After unregisterConsumer(), or after the implementation has released the
   * registration because the consumer died, the descriptor must no longer be used to read buffer contents: the
   * region may have been reused by a new consumer. Unmap and close it as part of unregistering.
   *
   * @param[out] _aidl_return The file descriptor backing the ring buffer, to be mapped or read by the consumer.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getFileDescriptor(::android::os::ParcelFileDescriptor* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Get information about the ring buffer.
   *
   * The result is a snapshot taken while the call was serviced, not a live view. The producer runs concurrently, so
   * availableForReading may already be out of date by the time the caller inspects it and is advisory only — useful
   * for metrics or coarse decisions, but never as the basis for a read. acquire() is the authoritative operation,
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
   * The consumer will be notified through the IRingBufferSourceListener::onDataAvailable callback when the number of
   * bytes available for reading in the ring buffer is greater than or equal to the specified threshold. Once that
   * callback has returned, the consumer can call acquire() to acquire the available bytes for reading. If the number
   * of bytes available for reading is already greater than or equal to the specified threshold when this method is
   * called, the consumer will be notified immediately through the onDataAvailable callback.
   *
   * The notification threshold can be set to 0 to disable notifications.
   *
   * The default value is one, i.e. the consumer will be notified as soon as there is at least one byte available for
   * reading in the ring buffer.
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
   * @brief Acquire data for reading.
   *
   * Unlike the producer, the consumer may hold several outstanding acquire results at once: calling this method
   * again before releasing a previous result is allowed and does not throw. Each result is identified by its own
   * RingBufferAcquireResult.Id.
   *
   * @note If the ring buffer is set to OverflowBehaviour.OVERFLOWING, the data acquired by this call may be
   * significantly newer than the data acquired through the last call to acquire() when an overflow has occurred.
   * Likewise, the acquired data might mix newer and older data when the overflow hasn't filled the whole requested
   * size. In other words, the data might be discontinuous. The consumer should be prepared to handle this situation
   * and not assume that the data acquired is contiguous or in order. Note though, that an overflow will be
   * signalled through the IRingBufferSourceListener::onError callback and the consumer can choose to discard the
   * acquired data in that case.
   *
   * @note The number of bytes available for reading can be less than the requested size, and even zero. The consumer
   * should check the number of bytes available for reading in the returned RingBufferAcquireResult and only read that
   * many bytes from the ring buffer.
   *
   * @param bytes The number of requested bytes.
   * @param[out] _aidl_return A RingBufferAcquireResult containing the offset in the ring buffer where the consumer can start reading
   *                         data and the number of bytes that are currently available for reading, or null if no data is available
   *                         for reading.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT If the provided number of bytes is less than or equal
   *                                                        to 0 or greater than the size of the ring buffer.
   */
  virtual ::android::binder::Status acquire(int32_t bytes, ::std::optional<::com::rdk::hal::ringbuffer::RingBufferAcquireResult>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Release bytes in the ring buffer after reading.
   *
   * Outstanding acquire results may be released in any order; the consumer is not required to release them in the
   * order they were acquired. Only the contiguous released prefix becomes available, including how notifications
   * report it to the producer.
   *
   * @note Once this call has returned, the consumer is not allowed to read from the ring buffer at the offset and
   * size returned by the corresponding acquire call anymore. The producer is now allowed to write to the ring buffer
   * at that offset.
   *
   * @param id The ID from the corresponding acquire call to correlate the release with the acquire.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT If the provided ID does not correspond to an
   *                                                        outstanding acquire on this source.
   */
  virtual ::android::binder::Status release(const ::com::rdk::hal::ringbuffer::RingBufferAcquireResult::Id& id) = 0;
  // @aidl-doc
  /**
   * @brief Request a flush of the ring buffer.
   *
   * This will both reset read and write positions and forward the request to the producer in order to give it a
   * chance to reset its internal buffers as well. The producer will be notified through the
   * IRingBufferSinkListener::onFlushRequested callback.
   *
   * The consumer must hold no outstanding acquire results when it calls this method. Every result obtained from
   * acquire() must have been released first, otherwise ::android::binder::Status::EX_ILLEGAL_STATE is thrown and
   * the buffer is left untouched. The requirement exists because a flush resets the read and write positions, which
   * would leave any held result pointing at a region that is no longer what the consumer acquired: reading through
   * it afterwards yields arbitrary bytes.
   *
   * After the flush, acquire() returns null until data written after the flush has been committed. Data released by
   * the producer through an acquire result it obtained before or during the flush is invalidated by the ring buffer
   * and never becomes readable, so the consumer cannot observe anything that predates the flush.
   *
   * That holds regardless of producer timing. The flush is asynchronous, so the producer may still be writing when
   * it takes effect and cannot observe the moment it happened; invalidation covers that window. How quickly data
   * reappears does depend on how promptly the producer abandons its in-flight write and acquires a fresh region.
   *
   * @note The flush request is asynchronous and the consumer should not assume that the ring buffer has been flushed
   * when this call returns. On the producer side, the flush request will be processed best effort and the producer
   * may not be able to flush its internal buffers at all.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If the consumer still holds one or more acquire results
   *                                                     that have not been released.
   */
  virtual ::android::binder::Status requestFlush() = 0;
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
  ::android::binder::Status requestFlush() override {
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
