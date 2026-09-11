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
package com.rdk.hal.ringbuffer;

import com.rdk.hal.ringbuffer.RingBufferAcquireResult;
import com.rdk.hal.ringbuffer.RingBufferInfo;

/**
 * Producer side of IRingBuffer.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
interface IRingBufferSink {
    /**
     * Get the underlying file descriptor for the ring buffer.
     */
    ParcelFileDescriptor getFileDescriptor();

    /** Get information about the ring buffer. */
    RingBufferInfo getInfo();

    /**
     * Set the minimum number of bytes that will cause a notification.
     *
     * The producer will be notified through the IRingBufferSinkListener::onSpaceAvailable callback when the number of
     * bytes available for writing in the ring buffer is greater than or equal to the specified threshold. The producer
     * can then call acquire() to acquire the available bytes for writing. If the number of bytes available for writing
     * is already greater than or equal to the specified threshold when this method is called, the producer will be
     * notified immediately through the onSpaceAvailable callback.
     *
     * The notification threshold can be set to 0 to disable notifications.
     *
     * The default value is one, i.e. the producer will be notified as soon as there is at least one byte available for
     * writing in the ring buffer.
     *
     * @param bytes The minimum number of bytes that will cause a notification.
     */
    void setNotificationThreshold(in int bytes);

    /**
     * Acquire bytes for writing.
     *
     * @note If the underlying IRingBuffer is set up to use overflowing behavior, this method will return immediately
     * with the number of bytes requested. It will thus override data which has not yet been read by the consumer if the
     * producer writes more data than the size of the ring buffer without the consumer reading it.
     *
     * @note The producer is not allowed to call this method again before releasing the bytes acquired in the previous
     * call to acquire. This is to prevent fragmentation of the ring buffer and to ensure that the producer can always
     * write to a contiguous block of memory.
     *
     * @param bytes The number of bytes to acquire for writing.
     * @return An RingBufferAcquireResult containing the offset in the ring buffer where the producer can start writing
     *         data and the number of bytes that were actually acquired for writing. Null, if the ring buffer is set up
     *         not to overflow and the ring buffer is full or if there's already space acquired by the producer that has
     *         not yet been released.
     */
    @nullable RingBufferAcquireResult acquire(in int bytes);

    /**
     * Release bytes in the ring buffer after writing.
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
     */
    void release(in RingBufferAcquireResult.Id id, in int bytes);
}
