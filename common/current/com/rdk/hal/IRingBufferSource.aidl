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

import com.rdk.hal.RingBufferAcquireResult;
import com.rdk.hal.RingBufferInfo;

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
     * @param bytes The minimum number of bytes that will cause a notification.
     */
    void setNotificationThreshold(in long bytes);

    /**
     * Acquire data for reading.
     *
     * @note If the ring buffer has been set up to be non-throttled, the data acquired by this call may be significantly
     * newer than the data acquired through the last call to acquire() when an overflow has occurred. Likewise, the
     * acquired data might mix newer and older data when the overflow hasn't filled the whole requested size. In other
     * words, the data might be discontinuous. The consumer should be prepared to handle this situation and not assume
     * that the data acquired is contiguous or in order. Note though, that an overflow will be signalled through the
     * RingBufferAcquireResult.overflow flag.
     *
     * TODO: What if, for a non-throttled ring buffer, the producer writes into data which still is acquired by the
     * consumer? Should we support this?
     *
     * @note The number of bytes available for reading can be less than the requested size, and even zero. The consumer
     * should check the number of bytes available for reading in the returned RingBufferAcquireResult and only read that
     * many bytes from the ring buffer.
     *
     * @param size The number of requested bytes.
     * @return An RingBufferAcquireResult containing the offset in the ring buffer where the consumer can start reading
     *         data and the number of bytes that are currently available for reading, or null if no data is available
     *         for reading.
     */
    @nullable RingBufferAcquireResult acquire(in long size);

    /**
     * Release bytes in the ring buffer after reading.
     *
     * @note Once this call has returned, the consumer is not allowed to read from the ring buffer at the offset and
     * size returned by the corresponding acquire call anymore. The producer is now allowed to write to the ring buffer
     * at that offset.
     *
     * @param id The ID from the corresponding acquire call to correlate the release with the acquire.
     */
    void release(in RingBufferAcquireResult.Id id);
}
