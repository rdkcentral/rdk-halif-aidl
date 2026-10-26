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
 * @brief What a ring buffer does when the producer outruns the consumer.
 *
 * There is no interface-wide default. Which behaviours a ring buffer offers, and whether the behaviour can be changed
 * at all, is a capability of the particular implementation, so the owning component selects the one it requires
 * through IRingBuffer::setOverflowBehaviour() and reads the value in effect through getInfo().
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
@Backing(type = "int")
enum OverflowBehaviour {
    /** Clean value when default initialized */
    UNDEFINED = 0,
    /**
     * The producer is able to write even when the ring buffer is full.
     *
     * This will result in data loss on the consumer side, but will not block the producer. Overflows are reported to
     * the producer through RingBufferErrorCode.OVERFLOW.
     */
    OVERFLOWING,
    /**
     * The producer receives null from acquire() when the ring buffer is full, avoiding data loss.
     *
     * The producer can retry after IRingBufferSinkListener::onSpaceAvailable() or drop data at source.
     */
    NON_OVERFLOWING,
}
