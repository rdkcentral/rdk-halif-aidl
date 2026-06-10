/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal;

import com.rdk.hal.IRingBufferSink;
import com.rdk.hal.IRingBufferSinkListener;
import com.rdk.hal.IRingBufferSource;
import com.rdk.hal.IRingBufferSourceListener;

/**
 * Generic ring buffer interface for HAL components.
 *
 * The ring buffer has to exhibit the typical Linux-like shared memory semantics, i.e. both producer and consumer have
 * to be able to mmap(2) the same shared memory using the file descriptor accessible through the IRingBufferSink and
 * IRingBufferSource interfaces. Data access is then performed by reading and writing to the mapped memory region at the
 * offsets provided by the acquire and waitForData methods of the IRingBufferSink and IRingBufferSource interfaces,
 * respectively. No out-of-band synchronization should be implemented besides the AIDL interfaces provided here.
 *
 * With that being said, though, the ring buffer is not strictly required to be implemented using shared memory. For
 * example, it could be implemented using a custom kernel driver that provides the necessary file descriptors and
 * implements the required semantics with DMA buffers backing the actual storage. When both producer and consumer can
 * agree on the semantics of the ring buffer, the actual implementation can be chosen freely, without any requirements
 * like the mmap'ability. In these cases, plain file descriptors (e.g. to UNIX domain sockets or devices in /dev) can be
 * used, using the offsets provided by the acquire and waitForData as seek sizes for read and write operations on the
 * file descriptors.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
interface IRingBuffer {
    /**
     * Set the size of the ring buffer.
     *
     * @note If there is currently a producer or a consumer registered, ::android::binder::Status::EX_ILLEGAL_STATE will
     * be thrown.
     *
     * @note If the buffer size exceeds the maximum buffer size allowed by the system,
     * ::android::binder::Status::EX_UNSUPPORTED_OPERATION will be thrown.
     *
     * @param size The number of bytes in the ring buffer. Must be greater than 0.
     */
    void setSize(in long size);

    /**
     * Set the throttling behavior of the ring buffer.
     *
     * @note If there is currently a producer or a consumer registered, ::android::binder::Status::EX_ILLEGAL_STATE will
     * be thrown.
     *
     * @param enabled If true, producers will be unable to write when the ring buffer is full. This avoids data loss on
     * the client side, but will block the producer until the consumer has read enough data to free up space in the ring
     * buffer. If false, producers will be able to write even when the ring buffer is full, which will result in data
     * loss on the client side, but will not block the producer. The default value is false.
     */
    void setThrottled(in boolean enabled);

    /**
     * Registers a producer to the ring buffer.
     *
     * @note The producer shall expect to receive a callback to IRingBufferSinkListener::onSpaceAvailable immediately
     * after registration. This is to allow the producer to learn about the ring buffer's size.
     *
     * @note Only one producer can be registered at a time. If called when a producer is already registered,
     * ::android::binder::Status::EX_ILLEGAL_STATE will be thrown.
     *
     * @param listener The listener that will receive callbacks for the producer.
     * @return An IRingBufferSink interface for the producer to write data to the ring buffer.
     */
    IRingBufferSink registerProducer(in IRingBufferSinkListener listener);

    /**
     * Unregisters the current producer from the ring buffer.
     *
     * @note If the provided sink does not match the currently registered producer, or if no producer is currently
     * registered, ::android::binder::Status::EX_ILLEGAL_ARGUMENT will be thrown.
     */
    void unregisterProducer(in IRingBufferSink sink);

    /**
     * Registers a consumer to the ring buffer.
     *
     * @note Only one consumer can be registered at a time. If called when a consumer is already registered,
     * ::android::binder::Status::EX_ILLEGAL_STATE will be thrown.
     *
     * @param listener The listener that will receive callbacks for the consumer.
     * @return An IRingBufferSource interface for the consumer to read data from the ring buffer.
     */
    IRingBufferSource registerConsumer(in IRingBufferSourceListener listener);

    /**
     * Unregisters the current consumer from the ring buffer.
     *
     * @note If the provided source does not match the currently registered consumer, or if no consumer is currently
     * registered, ::android::binder::Status::EX_ILLEGAL_ARGUMENT will be thrown.
     */
    void unregisterConsumer(in IRingBufferSource source);
}
