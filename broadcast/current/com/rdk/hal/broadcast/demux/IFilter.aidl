/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
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

import com.rdk.hal.broadcast.demux.DataPacket;
import com.rdk.hal.broadcast.demux.DemuxFilterParameters;
import com.rdk.hal.broadcast.demux.ISoftwareSinkListener;
import com.rdk.hal.broadcast.demux.SoftwareSink;

/**
 *  @brief     The IFilter interface is created by calling @ref IDemux::open(). Before this to be operational
 *             @ref IFilter::setFilter() must be called.
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
 */


@VintfStability
interface IFilter {
    /**
     * Set a new filter
     *
     * The filter is allowed to change after @ref IFilter::start() has been called.
     */
    void setFilter(in DemuxFilterParameters demuxFilterParameters);

    /** Start collecting data for this filter on the demux */
    void start();

    /** Stop collecting data for this filter on the demux */
    void stop();

    /**
     * Close the filter
     *
     * After calling this this instance is no longer valid.
     */
    void close();

    /**
     * Register a software sink for the filter
     *
     * The sink will receive the data from the filter through the means provided in the
     * @ref SoftwareSink return value. It will further provide callbacks in the softwareSink
     * parameter.
     *
     * @param softwareSink A set of callbacks the sink wants to receive.
     * @return The details the sink needs in order to actually be able to receive data.
     */
    SoftwareSink registerSoftwareSink(in ISoftwareSinkListener softwareSink);

    /**
     * Unregister a software sink
     *
     * The caller should remember to also close and dispose the shared memory, file descriptor and
     * message queue.
     *
     * @param id The ID of the sink to be unregistered.
     * @return True, if a sink with the given ID existed and was removed, false otherwise.
     */
    boolean unregisterSoftwareSink(in SoftwareSink.Id id);

    /**
     * Mark a data packet as consumed
     *
     * @param id The ID of the calling software sink.
     * @param pId The ID of the packet that has been consumed.
     */
    void onDataPacketConsumed(in SoftwareSink.Id id, DataPacket.Id pId);
}
