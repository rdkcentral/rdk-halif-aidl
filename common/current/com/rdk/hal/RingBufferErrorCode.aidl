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
    /** Overflow. Only relevant for non-throttled ring buffers. */
    OVERFLOW,
    /** The producer side has vanished unexpectedly, e.g. due to a crash or being killed by the system. */
    PRODUCER_DISCONNECTED,
    /** The consumer side has vanished unexpectedly, e.g. due to a crash or being killed by the system. */
    CONSUMER_DISCONNECTED,
    /** Implementation-specific error (the message parameter of the callback should contain more details) */
    IMPLEMENTATION_ERROR,
}
