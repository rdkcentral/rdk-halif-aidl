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

/**
 * @brief Error codes for IRingBuffer.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
@Backing(type = "int")
enum RingBufferErrorCode {
    /** Clean value when default initialized */
    UNDEFINED = 0,
    /**
     * Overflow.
     *
     * Only relevant for overflowing ring buffers. Will be issued when the producer acquires a buffer which will include
     * the current reading position, i.e. the offset of the "oldest" acquire result not yet released by the consumer or
     * the offset that would be given to the next acquire call if the consumer currently holds no buffer.
     *
     * Delivered asynchronously through the oneway onError callback. Delivery may be triggered by the implementation
     * while it is handling an acquire call, so the callback can run on another thread while the producer's own acquire
     * call is still in progress. The producer must therefore not take a lock in the callback that it also holds across
     * acquire.
     */
    OVERFLOW,
    /**
     * The producer side has vanished unexpectedly, e.g. due to a crash or being killed by the system.
     *
     * Detected by the implementation through a death recipient on the producer's listener. Any acquire result the
     * producer still held is discarded, since it was never released and so was never committed, and the producer slot
     * returns to its unregistered state so that a replacement can register.
     */
    PRODUCER_DISCONNECTED,
    /**
     * The consumer side has vanished unexpectedly, e.g. due to a crash or being killed by the system.
     *
     * Detected by the implementation through a death recipient on the consumer's listener. Any acquire results the
     * consumer still held are released, returning that space to the producer, and the consumer slot returns to its
     * unregistered state so that a replacement can register.
     */
    CONSUMER_DISCONNECTED,
    /** Implementation-specific error (the message parameter of the callback should contain more details) */
    IMPLEMENTATION_ERROR,
}
