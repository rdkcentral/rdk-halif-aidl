/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
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
package com.rdk.hal.broadcast.demux;

import com.rdk.hal.broadcast.demux.IDemuxDataProvider;

/**
 *  @brief     Interface for injecting software data into a Demux.
 *
 *  Obtained via IDemux.createInjector(). Allows client-side software (e.g. DVR playback or
 *  network-sourced content) to feed transport stream data into a connected Demux.
 *
 *  A Demux can only be connected to a software injector if its DemuxCapabilities.acceptsDataFromSoftware
 *  is true. Only one injector can be connected at a time.
 *
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 *
 *  @see IDemux.createInjector()
 *  @see DemuxCapabilities.acceptsDataFromSoftware
 */
@VintfStability
interface IDataFromSoftwareInjector {

    /**
     * Write data into the connected Demux.
     *
     * Writes the given byte array into the Demux. The call may block up to timeoutMs milliseconds
     * if there is not enough space available. Use timeoutMs = 0 for a non-blocking call, or -1
     * to block indefinitely.
     *
     * If not all data could be written before the timeout expired, the return value reflects
     * only the bytes actually written; the caller must retry with the remaining data.
     *
     * @param[in] data       The transport stream data to inject.
     * @param[in] timeoutMs  Maximum time to block in milliseconds. 0 = non-blocking, -1 = infinite.
     *
     * @returns The number of bytes actually written. May be less than data.length on timeout or
     *          when the buffer is full.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if no data provider has been acquired.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if timeoutMs < -1.
     */
    int write(in byte[] data, in int timeoutMs);

    /**
     * Abort a currently blocking write() call.
     *
     * Thread-safe. If write() is not currently blocking, the next call to write() will return
     * immediately with the bytes written so far.
     */
    void abort();

    /**
     * Acquire a DemuxDataProvider to connect this injector to a Demux.
     *
     * Only one data provider can be acquired at a time. Returns null if a provider has already
     * been acquired and not yet released.
     *
     * @returns IDemuxDataProvider or null if already acquired.
     *
     * @see IDemux.connect()
     * @see releaseDataProvider()
     */
    @nullable IDemuxDataProvider acquireDataProvider();

    /**
     * Release a previously acquired DemuxDataProvider.
     *
     * After calling this, acquireDataProvider() may be called again.
     *
     * @param[in] provider A non-null provider previously returned by acquireDataProvider() on this
     *                     same injector.
     *
     * @see acquireDataProvider()
     */
    void releaseDataProvider(in IDemuxDataProvider provider);
}
