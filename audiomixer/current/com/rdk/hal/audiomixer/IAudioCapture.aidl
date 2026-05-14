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
 * @brief Audio capture interface for output ports.
 * 
 * Provides stateful control over audio capture sessions on an output port.
 * Clients obtain shared memory, register a listener, configure capture format,
 * call start() to begin streaming, receive async callbacks via IAudioCaptureListener,
 * acknowledge consumed data with releaseData(), then call stop() to end the session.
 * 
 * Example lifecycle:
 * @code
 *   int ringBufferSizeBytes;
 *   ParcelFileDescriptor pfd = capture.getSharedMemory(out ringBufferSizeBytes);
 *   capture.start();
 *   // Listener receives onDataAvailable(offset, length, metadata) callbacks.
 *   // Client reads from shared memory then calls releaseData(offset, length).
 *   capture.stop();
 * @endcode
 * 
 * The data format captured is that of the output port.
 * Where an output port is physical, the capture interface captures the data format currently being output.
 * Where the output port is a dedicated capture port setting the OUTPUT_FORMAT directly controls the format of captured data. 
 */
@VintfStability
interface IAudioCapture {
    /**
     * @brief Returns the shared-memory ring buffer descriptor for zero-copy capture.
     *
     * This method must be called before capturing of audio data has been started with a call to start().
     *
     * @param[out] sharedMemorySizeBytes Total ring buffer size in bytes.
     * @returns ParcelFileDescriptor identifying the shared-memory ring buffer.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if capture already started.
     */
    ParcelFileDescriptor getSharedMemory(out int sharedMemorySizeBytes);

    /**
     * @brief Release the shared-memory ring buffer 
     *
     * This method must be called only when capturing of audio data is stopped.
     * Calling releaseSharedMemory() before getSharedMemory() is not an error.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if capture is not stopped.
     */
    void releaseSharedMemory();

    /**
     * @brief Start audio capture stream using the configured format.
     * 
     * Transitions capture interface from stopped to started state. Listener will receive
     * onStarted() callback, followed by repeated onDataAvailable() callbacks as audio
     * frames become available. Call stop() to end the stream.
     *
     * Ring buffer state is reset on every start() following a stop() transition.
     * 
     * @returns true if capture stream started successfully.
     * 
     * @exception binder::Status EX_ILLEGAL_STATE if a shared memory ring buffer has not been aquired by the client.
     * It is not considered an error if start() is called while already started.
     * 
     */
     boolean start();

    /**
     * @brief Stop audio capture stream.
     * 
     * Transitions capture interface from started to stopped state. Listener will receive
     * onStopped() callback after this method returns. No further onDataAvailable() callbacks
     * will be delivered.
     * 
     * @returns Success flag indicating whether the capture state changed.
     * @retval true Capture stream stopped successfully.
     * @retval false Capture was already stopped.
     *
     * Calling stop() while already stopped is not considered an error.
     */
    boolean stop();

    /**
     * @brief Acknowledges that previously signalled data has been consumed by the client.
     *
     * The offset and length must match a previously received onDataAvailable() callback.
     *
     * @param[in] offsetBytes Byte offset previously received from onDataAvailable().
     * @param[in] lengthBytes Length in bytes previously received from onDataAvailable().
     *
     * @exception binder::Status EX_ILLEGAL_STATE if capture not started.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT for invalid region.
     */
    oneway void releaseData(in long offsetBytes, in int lengthBytes);
}
