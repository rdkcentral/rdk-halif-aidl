#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSink.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSinkListener.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSource.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSourceListener.h>
#include <com/rdk/hal/ringbuffer/OverflowBehaviour.h>
#include <com/rdk/hal/ringbuffer/RingBufferInfo.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
// @aidl-doc
/**
 * @brief Generic ring buffer interface for HAL components.
 *
 * This interface is implementation-internal. It is owned by the HAL component that creates the ring buffer and is
 * deliberately never exposed over the producer or consumer interfaces: it is not registered with the service manager,
 * has no serviceName constant, and is not returned by any method a producer or consumer client can call. Clients only
 * ever hold an IRingBufferSink or an IRingBufferSource, obtained from the owning HAL component.
 *
 * Buffer size and overflow behaviour are therefore set by the owning component, not negotiated by its clients.
 *
 * The ring buffer has to exhibit the typical Linux-like shared memory semantics, i.e. both producer and consumer have
 * to be able to mmap(2) the same shared memory using the file descriptor accessible through the IRingBufferSink and
 * IRingBufferSource interfaces. Data access is then performed by reading and writing to the mapped memory region at the
 * offsets provided by the acquire methods of the IRingBufferSink and IRingBufferSource interfaces, respectively. No
 * out-of-band synchronization should be implemented besides the AIDL interfaces provided here.
 *
 * With that being said, though, the ring buffer is not strictly required to be implemented using shared memory. For
 * example, it could be implemented using a custom kernel driver that provides the necessary file descriptors and
 * implements the required semantics with DMA buffers backing the actual storage. When both producer and consumer can
 * agree on the semantics of the ring buffer, the actual implementation can be chosen freely, without any requirements
 * like the mmap'ability. In these cases, plain file descriptors (e.g. to UNIX domain sockets or devices in /dev) can be
 * used, using the offsets provided by the acquire methods as seek sizes for read and write operations on the
 * file descriptors.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class IRingBuffer : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(RingBuffer)
  static const int32_t VERSION = 1000;
  const std::string HASH = "5a1f05ac0895c7939e525e8935437358f793e70c";
  static constexpr char* HASHVALUE = "5a1f05ac0895c7939e525e8935437358f793e70c";
  // @aidl-doc
  /**
   * @brief Get information about the ring buffer.
   *
   * Available to the owning component at any time, including before a producer or consumer has been registered.
   *
   * @param[out] _aidl_return A snapshot of the ring buffer size, readable byte count and overflow behaviour.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getInfo(::com::rdk::hal::ringbuffer::RingBufferInfo* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Set the size in bytes of the ring buffer.
   *
   * Sizes and offsets are 32-bit throughout this interface, which bounds a ring buffer at 2 GiB. That limit is
   * deliberate and is not expected to constrain the intended use cases.
   *
   * @note If there is currently a producer or a consumer registered, ::android::binder::Status::EX_ILLEGAL_STATE will
   * be thrown.
   *
   * @param bytes The number of bytes in the ring buffer. Must be greater than 0.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If there is currently a producer or a consumer registered.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT If the provided size is less than or equal to 0.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION If the provided size exceeds the maximum buffer
   *                                                             size allowed by the system.
   */
  virtual ::android::binder::Status setSize(int32_t bytes) = 0;
  // @aidl-doc
  /**
   * @brief Set the overflow behaviour of the ring buffer.
   *
   * The interface defines no default. Whether a ring buffer overflows, and whether that behaviour can be changed at
   * all, is a capability of the particular implementation, so the owning component shall set the behaviour it
   * requires rather than relying on an initial value, and shall be prepared for EX_UNSUPPORTED_OPERATION where the
   * implementation does not offer it. The value in effect can be read back through getInfo().
   *
   * @param behaviour The overflow behaviour to apply. See OverflowBehaviour for what each value means to the
   * producer.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If there is currently a producer or a consumer registered.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT If the provided behaviour is
   *                                                        OverflowBehaviour.UNDEFINED.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION If the provided overflow behaviour is not
   *                                                             supported by the system.
   */
  virtual ::android::binder::Status setOverflowBehaviour(::com::rdk::hal::ringbuffer::OverflowBehaviour behaviour) = 0;
  // @aidl-doc
  /**
   * @brief Registers a producer to the ring buffer.
   *
   * @note The producer shall expect to receive a callback to IRingBufferSinkListener::onSpaceAvailable immediately
   * after registration. This is to allow the producer to learn about the ring buffer's size.
   *
   * @note The listener is hosted by the client, so the implementation shall register a death recipient on it
   * (linkToDeath) to learn if the producer terminates unexpectedly. On death the implementation shall discard any
   * acquire result the producer still held and release the registration, returning the producer slot to its
   * unregistered state as if unregisterProducer() had been called. A crashed producer must not leave the slot
   * permanently occupied.
   *
   * @param listener The listener that will receive callbacks for the producer.
   * @param[out] _aidl_return An IRingBufferSink interface for the producer to write data to the ring buffer.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If there is currently a producer registered.
   */
  virtual ::android::binder::Status registerProducer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSinkListener>& listener, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Unregisters the current producer from the ring buffer.
   *
   * @param sink The sink returned by registerProducer() for the producer being unregistered.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If there is currently no producer registered.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT If the provided sink does not match the currently
   *                                                        registered producer.
   */
  virtual ::android::binder::Status unregisterProducer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>& sink) = 0;
  // @aidl-doc
  /**
   * @brief Registers a consumer to the ring buffer.
   *
   * @note The listener is hosted by the client, so the implementation shall register a death recipient on it
   * (linkToDeath) to learn if the consumer terminates unexpectedly. On death the implementation shall release any
   * acquire results the consumer still held, returning that space to the producer, and release the registration,
   * returning the consumer slot to its unregistered state as if unregisterConsumer() had been called. A crashed
   * consumer must not leave the slot permanently occupied.
   *
   * @param listener The listener that will receive callbacks for the consumer.
   * @param[out] _aidl_return An IRingBufferSource interface for the consumer to read data from the ring buffer.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If there is currently a consumer registered.
   */
  virtual ::android::binder::Status registerConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSourceListener>& listener, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Unregisters the current consumer from the ring buffer.
   *
   * @param source The source returned by registerConsumer() for the consumer being unregistered.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If there is currently no consumer registered.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT If the provided source does not match the currently
   *                                                        registered consumer.
   */
  virtual ::android::binder::Status unregisterConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>& source) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IRingBuffer

class IRingBufferDefault : public IRingBuffer {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getInfo(::com::rdk::hal::ringbuffer::RingBufferInfo* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setSize(int32_t /*bytes*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setOverflowBehaviour(::com::rdk::hal::ringbuffer::OverflowBehaviour /*behaviour*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerProducer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSinkListener>& /*listener*/, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterProducer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>& /*sink*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSourceListener>& /*listener*/, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>& /*source*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IRingBufferDefault
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
