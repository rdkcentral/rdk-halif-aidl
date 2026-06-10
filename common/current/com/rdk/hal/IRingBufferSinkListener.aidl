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

import com.rdk.hal.RingBufferErrorCode;

/**
 * Callback interface for the producer side of IRingBuffer.
 *
 * It's not allowed to call any methods on IRingBufferSink or IRingBuffer from within the callbacks of this interface.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
oneway interface IRingBufferSinkListener {
    /**
     * Called when there's space available in the ring buffer for the producer to write data.
     *
     * This callback is triggered when the number of bytes available for writing in the ring buffer is greater than or
     * equal to the notification threshold set by the producer using the IRingBufferSink::setNotificationThreshold
     * method.
     *
     * Once the threshold has been reached, the producer will not receive any further notifications until the free space
     * in the ring buffer drops below the threshold and then rises above it again. This is to prevent flooding the
     * producer with notifications when the ring buffer is already full and the producer is not able to write any data.
     *
     * @param size The number of bytes available for writing.
     */
    void onSpaceAvailable(in long size);

    /**
     * Called when the consumer side has requested a flush of the ring buffer.
     *
     * This can be used by the producer to flush any internal buffers or data sources to ensure no stale data will be
     * written to the ring buffer going forward.
     */
    void onFlushRequested();

    /**
     * Called on error.
     *
     * @param code The error code indicating the type of error that occurred.
     * @param message A human-readable message providing more details about the error.
     */
    void onError(in RingBufferErrorCode code, in String message);
}
