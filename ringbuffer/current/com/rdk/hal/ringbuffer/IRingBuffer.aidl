/*
 * If not stated otherwise in this file or this component's LICENSE file the following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 */
package com.rdk.hal.ringbuffer;

import com.rdk.hal.ringbuffer.IRingBufferSink;
import com.rdk.hal.ringbuffer.IRingBufferSinkListener;
import com.rdk.hal.ringbuffer.IRingBufferSource;
import com.rdk.hal.ringbuffer.IRingBufferSourceListener;
import com.rdk.hal.ringbuffer.RingBufferInfo;

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
@VintfStability
interface IRingBuffer {
    /**
     * @brief Get information about the ring buffer.
     *
     * Available to the owning component at any time, including before a producer or consumer has been registered.
     *
     * @returns A snapshot of the ring buffer size, readable byte count and overflow setting.
     */
    RingBufferInfo getInfo();

    /**
     * @brief Set the size in bytes of the ring buffer.
     *
     * Sizes and offsets are 32-bit throughout this interface, which bounds a ring buffer at 2 GiB. That limit is
     * deliberate and is not expected to constrain the intended use cases.
     *
     * @note If there is currently a producer or a consumer registered, ::android::binder::Status::EX_ILLEGAL_STATE will
     * be thrown.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE If there is currently a producer or a consumer registered.
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT If the provided size is less than or equal to 0.
     * @exception ::android::binder::Status::EX_UNSUPPORTED_OPERATION If the provided size exceeds the maximum buffer
     *                                                                size allowed by the system.
     *
     * @param bytes The number of bytes in the ring buffer. Must be greater than 0.
     */
    void setSize(in int bytes);

    /**
     * @brief Set the overflowing behavior of the ring buffer.
     *
     * The interface defines no default. Whether a ring buffer overflows, and whether that behaviour can be changed at
     * all, is a capability of the particular implementation, so the owning component shall set the behaviour it
     * requires rather than relying on an initial value, and shall be prepared for EX_UNSUPPORTED_OPERATION where the
     * implementation does not offer it. The value in effect can be read back through getInfo().
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE If there is currently a producer or a consumer registered.
     * @exception ::android::binder::Status::EX_UNSUPPORTED_OPERATION If the provided overflowing behavior is not
     *                                                                supported by the system.
     *
     * @param enabled If false, producers will receive null from acquire() when the ring buffer is full, avoiding data
     * loss; the producer can retry after onSpaceAvailable() or drop data at source. If true, producers will be
     * able to write even when the ring buffer is full, which will result in data loss on the client side, but will not
     * block the producer.
     */
    void setOverflowing(in boolean enabled);

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
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE If there is currently a producer registered.
     *
     * @param listener The listener that will receive callbacks for the producer.
     * @returns An IRingBufferSink interface for the producer to write data to the ring buffer.
     */
    IRingBufferSink registerProducer(in IRingBufferSinkListener listener);

    /**
     * @brief Unregisters the current producer from the ring buffer.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE If there is currently no producer registered.
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT If the provided sink does not match the currently
     *                                                           registered producer.
     */
    void unregisterProducer(in IRingBufferSink sink);

    /**
     * @brief Registers a consumer to the ring buffer.
     *
     * @note The listener is hosted by the client, so the implementation shall register a death recipient on it
     * (linkToDeath) to learn if the consumer terminates unexpectedly. On death the implementation shall release any
     * acquire results the consumer still held, returning that space to the producer, and release the registration,
     * returning the consumer slot to its unregistered state as if unregisterConsumer() had been called. A crashed
     * consumer must not leave the slot permanently occupied.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE If there is currently a consumer registered.
     *
     * @param listener The listener that will receive callbacks for the consumer.
     * @returns An IRingBufferSource interface for the consumer to read data from the ring buffer.
     */
    IRingBufferSource registerConsumer(in IRingBufferSourceListener listener);

    /**
     * @brief Unregisters the current consumer from the ring buffer.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE If there is currently no consumer registered.
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT If the provided source does not match the currently
     *                                                           registered consumer.
     */
    void unregisterConsumer(in IRingBufferSource source);
}
