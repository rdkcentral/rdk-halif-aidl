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
 * Consumer side of IRingBuffer.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
interface IRingBufferSource {
    /**
     * Get the underlying file descriptor for the ring buffer.
     */
    ParcelFileDescriptor getFileDescriptor();

    /** Get information about the ring buffer. */
    RingBufferInfo getInfo();

    /**
     * Set the minimum number of bytes that will cause a notification.
     *
     * The consumer will be notified through the IRingBufferSourceListener::onDataAvailable callback when the number of
     * bytes available for reading in the ring buffer is greater than or equal to the specified threshold. The consumer
     * can then call acquire() to acquire the available bytes for reading. If the number of bytes available for reading
     * is already greater than or equal to the specified threshold when this method is called, the consumer will be
     * notified immediately through the onDataAvailable callback.
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
     * Acquire data for reading.
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
     * Release bytes in the ring buffer after reading.
     *
     * @note Once this call has returned, the consumer is not allowed to read from the ring buffer at the offset and
     * size returned by the corresponding acquire call anymore. The producer is now allowed to write to the ring buffer
     * at that offset.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT If the provided ID does not match the ID returned by
     *                                                           a call to acquire().
     *
     * @param id The ID from the corresponding acquire call to correlate the release with the acquire.
     */
    void release(in RingBufferAcquireResult.Id id);

    /**
     * Request a flush of the ring buffer.
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
