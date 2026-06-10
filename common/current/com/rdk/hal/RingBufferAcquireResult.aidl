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

/**
 * Results of a call to acquire() for either reading or writing data in the ring buffer.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
parcelable RingBufferAcquireResult {
    /** An typesafe ID. */
    @VintfStability
    parcelable Id {
        long id;
    }

    /** The ID to correlate acquire and release calls. */
    Id id;

    /** The offset in the ring buffer where data can be read/written. */
    long offset;

    /**
     * The number of bytes that were actually acquired for reading/writing.
     *
     * @note The number of bytes acquired can be less than the requested size, and even zero. The consumer/producer
     * should check the number of bytes acquired in the returned RingBufferAcquireResult and only read/write that many
     * bytes.
     */
    long size;

    /**
     * The number of remaining bytes available for reading/writing in the ring buffer after this acquire.
     *
     * @note remaining bytes can be greater than zero even if size is smaller than the requested size. This can happen
     * when the acquired data is located right before the end of the ring buffer, and the remaining data is located at
     * the beginning of the ring buffer.
     */
    long remaining;

    /**
     * Overflow signalling.
     *
     * This is only relevant for non-throttling ring buffers. For producers, this indicates that the acquired space has
     * not been read by the consumer since the producer's last call to release() for the space. For consumers, this
     * indicates that the acquired data is discontinuous with the previously acquired data.
     */
    boolean overflow;
}
