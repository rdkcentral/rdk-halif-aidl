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

import com.rdk.hal.ringbuffer.RingBufferErrorCode;

/**
 * @brief Callback interface for the consumer side of IRingBuffer.
 *
 * This interface is oneway, so callbacks are dispatched asynchronously and the implementation does not wait for them
 * to return. Methods on IRingBufferSource or IRingBuffer must not be called from within a callback body; the consumer
 * may call them once the callback has returned.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
oneway interface IRingBufferSourceListener {
    /**
     * @brief Called when there's data available in the ring buffer for the consumer to read.
     *
     * This callback is triggered when the number of bytes available for reading in the ring buffer is greater than or
     * equal to the notification threshold set by the consumer using the IRingBufferSource::setNotificationThreshold
     * method.
     *
     * Once the threshold has been reached, the consumer will not receive any further notifications until the readable
     * space in the ring buffer drops below the threshold and then reaches or exceeds it again. This is to prevent
     * flooding the consumer with notifications when the ring buffer is already full and the consumer is not able to
     * read any data.
     *
     * @param bytes The number of bytes available for reading.
     */
    void onDataAvailable(in int bytes);

    /**
     * @brief Called on error.
     *
     * @param code The error code indicating the type of error that occurred.
     * @param message A human-readable message providing more details about the error.
     */
    void onError(in RingBufferErrorCode code, in String message);
}
