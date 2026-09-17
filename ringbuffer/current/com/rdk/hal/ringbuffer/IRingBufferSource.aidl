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

import com.rdk.hal.ringbuffer.RingBufferAcquireResult;
import com.rdk.hal.ringbuffer.RingBufferInfo;

/**
 * @brief Consumer side of IRingBuffer.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
interface IRingBufferSource {
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
     * @returns The file descriptor backing the ring buffer, to be mapped or read by the consumer.
     */
    ParcelFileDescriptor getFileDescriptor();

    /**
     * @brief Get information about the ring buffer.
     *
     * The result is a snapshot taken while the call was serviced, not a live view. The producer runs concurrently, so
     * availableForReading may already be out of date by the time the caller inspects it and is advisory only — useful
     * for metrics or coarse decisions, but never as the basis for a read. acquire() is the authoritative operation,
     * and the bytes field of its result is the only trustworthy statement of what the caller may access. The size and
     * overflow setting are stable while a client is registered.
     *
     * @returns A snapshot of the ring buffer size, readable byte count and overflow setting.
     */
    RingBufferInfo getInfo();

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
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT If the provided threshold is less than 0 or greater
     *                                                           than the size of the ring buffer.
     *
     * @param bytes The minimum number of bytes that will cause a notification.
     */
    void setNotificationThreshold(in int bytes);

    /**
     * @brief Acquire data for reading.
     *
     * Unlike the producer, the consumer may hold several outstanding acquire results at once: calling this method
     * again before releasing a previous result is allowed and does not throw. Each result is identified by its own
     * RingBufferAcquireResult.Id.
     *
     * @note If the ring buffer has been set up to be overflowing, the data acquired by this call may be significantly
     * newer than the data acquired through the last call to acquire() when an overflow has occurred. Likewise, the
     * acquired data might mix newer and older data when the overflow hasn't filled the whole requested size. In other
     * words, the data might be discontinuous. The consumer should be prepared to handle this situation and not assume
     * that the data acquired is contiguous or in order. Note though, that an overflow will be signalled through the
     * IRingBufferSourceListener::onError callback and the consumer can choose to discard the acquired data in that
     * case.
     *
     * @note The number of bytes available for reading can be less than the requested size, and even zero. The consumer
     * should check the number of bytes available for reading in the returned RingBufferAcquireResult and only read that
     * many bytes from the ring buffer.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT If the provided number of bytes is less than or equal
     *                                                           to 0 or greater than the size of the ring buffer.
     *
     * @param bytes The number of requested bytes.
     * @returns A RingBufferAcquireResult containing the offset in the ring buffer where the consumer can start reading
     *         data and the number of bytes that are currently available for reading, or null if no data is available
     *         for reading.
     */
    @nullable RingBufferAcquireResult acquire(in int bytes);

    /**
     * @brief Release bytes in the ring buffer after reading.
     *
     * Outstanding acquire results may be released in any order; the consumer is not required to release them in the
     * order they were acquired. Space is returned to the producer as each result is released.
     *
     * @note Once this call has returned, the consumer is not allowed to read from the ring buffer at the offset and
     * size returned by the corresponding acquire call anymore. The producer is now allowed to write to the ring buffer
     * at that offset.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT If the provided ID does not correspond to an
     *                                                           outstanding acquire on this source.
     *
     * @param id The ID from the corresponding acquire call to correlate the release with the acquire.
     */
    void release(in RingBufferAcquireResult.Id id);

    /**
     * @brief Request a flush of the ring buffer.
     *
     * This will both reset read and write positions and forward the request to the producer in order to give it a
     * chance to reset its internal buffers as well. The producer will be notified through the
     * IRingBufferSinkListener::onFlushRequested callback.
     *
     * @note The flush request is asynchronous and the consumer should not assume that the ring buffer has been flushed
     * when this call returns. On the producer side, the flush request will be processed best effort and the producer
     * may not be able to flush its internal buffers at all.
     *
     * @note Acquire results that are currently held by the consumer should be released before calling this method.
     * Otherwise, garbage data may be read through these results after the flush has been requested.
     */
    void requestFlush();
}
