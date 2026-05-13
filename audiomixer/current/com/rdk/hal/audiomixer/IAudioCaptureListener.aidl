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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.rdk.hal.audiomixer;

/**
 * @brief Audio capture event listener interface.
 * Asynchronous callback interface for receiving audio capture events from an output port.
 * All methods are one-way (fire-and-forget) to avoid blocking the capture thread.
 */
@VintfStability
oneway interface IAudioCaptureListener {
    /**
     * @brief Called when a new audio data frame is available in shared-memory ring buffer.
     *
     * Wrap-around semantics:
     * If (offsetBytes + lengthBytes) <= ringBufferSizeBytes, the frame is contiguous.
     * If (offsetBytes + lengthBytes) > ringBufferSizeBytes, the frame wraps and must be read
     * as two segments:
     * segment1: [offsetBytes, ringBufferSizeBytes)
     * segment2: [0, (offsetBytes + lengthBytes) - ringBufferSizeBytes)
     *
     * @param[in] offsetBytes Byte offset from the start of the ring buffer.
     * @param[in] lengthBytes Number of valid bytes for this frame.
     * @param[in] metadata Audio frame metadata (channels, sample rate, timestamp, format).
     *
     * The client must call IAudioCapture.releaseData(offsetBytes, lengthBytes) after reading.
     * 
     * @returns Void (one-way result does not wait for callback completion).
     */
    void onDataAvailable(in long offsetBytes, in int lengthBytes, in AudioCaptureData metadata);

    /**
     * @brief Called when audio capture stream has successfully started.
     * 
     * Signals that the capture interface has transitioned to active/streaming state
     * and audio frames are being delivered via onDataAvailable() calls.
     * 
     * @returns Void (one-way result does not wait for callback completion).
     */
    void onStarted();

    /**
     * @brief Called when audio capture stream has stopped.
     * 
     * Signals that the capture interface has transitioned to idle/stopped state.
     * No further onDataAvailable() callbacks will be delivered.
     * 
     * @returns Void (one-way result does not wait for callback completion).
     */
    void onStopped();

    /**
     * @brief Called when an error occurs during audio capture.
     * ERROR_OVERFLOW indicates new incoming data was dropped and is lost.
     * 
     * @param[in] status Error code indicating the type of failure.
     * @param[in] message Human-readable error description.
     * 
     * @returns Void (one-way result does not wait for callback completion).
     * 
     * @exception None (one-way interface never throws).
     */
    void onError(in AudioCaptureStatus status, in String message);
}
