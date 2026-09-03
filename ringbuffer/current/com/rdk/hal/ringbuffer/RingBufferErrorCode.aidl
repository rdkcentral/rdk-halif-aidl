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

/**
 * Error codes for IRingBuffer.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
@Backing(type="int")
enum RingBufferErrorCode {
    /** Clean value when default initialized */
    UNDEFINED = 0,
    /**
     * Overflow.
     *
     * Only relevant for overflowing ring buffers. Will be issued when the producer acquires a buffer which will include
     * the current reading position, i.e. the offset of the "oldest" acquiry result not yet released by the consumer or
     * the offset that would be given to the next acquire call if the consumer currently holds no buffer.
     *
     * Might be issued in-line, i.e. during the acquire call. The producer must therefore be prepared to handle this
     * error while being in the middle of an acquire call, and should thus, for example, not try to lock a mutex which
     * is also used while calling acquire.
     */
    OVERFLOW,
    /** The producer side has vanished unexpectedly, e.g. due to a crash or being killed by the system. */
    PRODUCER_DISCONNECTED,
    /** The consumer side has vanished unexpectedly, e.g. due to a crash or being killed by the system. */
    CONSUMER_DISCONNECTED,
    /** Implementation-specific error (the message parameter of the callback should contain more details) */
    IMPLEMENTATION_ERROR,
}
