/*
 * If not stated otherwise in this file or this component's LICENSE file the following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
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
package com.rdk.hal.broadcast.demux;

import com.rdk.hal.IRingBufferSource;
import com.rdk.hal.IRingBufferSourceListener;
import com.rdk.hal.broadcast.demux.DemuxFilterParameters;
import com.rdk.hal.broadcast.demux.FilterType;

/**
 * Filter interface created by calling IDemuxController.openFilter().
 *
 * Before this filter is operational, setFilter() must be called.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
interface IFilter {
    /**
     * Get the type of this filter.
     *
     * @returns FilterType the type of data this filter captures.
     */
    FilterType getType();

    /**
     * Set a new filter.
     *
     * The filter is allowed to change after start() has been called.
     */
    void setFilter(in DemuxFilterParameters demuxFilterParameters);

    /** Start collecting data for this filter on the demux */
    void start();

    /** Stop collecting data for this filter on the demux */
    void stop();

    /**
     * Close the filter.
     *
     * After calling this, this instance is no longer valid.
     */
    void close();

    /**
     * Register a consumer to read the data captured by this filter.
     *
     * The call is forwarded to the IRingBuffer owned by the filter's IDemuxController. Since a demux
     * permits a single MPEG2TS_DATA filter (MaxFilterInstances(1)), there is exactly one consumer of
     * that buffer.
     *
     * @note Only one consumer can be registered at a time. If called when a consumer is already
     * registered, ::android::binder::Status::EX_ILLEGAL_STATE will be thrown.
     *
     * @param[in] listener The listener that will receive IRingBufferSourceListener callbacks.
     * @returns An IRingBufferSource for the consumer to read data from the ring buffer.
     */
    IRingBufferSource registerConsumer(in IRingBufferSourceListener listener);

    /**
     * Unregister the current consumer from this filter.
     *
     * The call is forwarded to the controller's IRingBuffer.
     *
     * @note If the provided source does not match the currently registered consumer, or if no
     * consumer is currently registered, ::android::binder::Status::EX_ILLEGAL_ARGUMENT will be thrown.
     *
     * @param[in] source The IRingBufferSource returned by the corresponding registerConsumer call.
     */
    void unregisterConsumer(in IRingBufferSource source);
}
