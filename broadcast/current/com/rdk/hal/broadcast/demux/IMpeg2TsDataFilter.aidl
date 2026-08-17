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
package com.rdk.hal.broadcast.demux;

import com.rdk.hal.ringbuffer.IRingBufferSource;
import com.rdk.hal.ringbuffer.IRingBufferSourceListener;

/**
 * Filter interface for opaque MPEG2-TS data.
 *
 * Before this filter is operational, setFilter() must be called. This is used for metadata, as well as in non-tunneled
 * pipelines.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
interface IMpeg2TsDataFilter {
    /**
     * Set the PIDs to filter for.
     *
     * Going from an empty list to a non-empty list will start the filter without flushing data. Going from a non-empty
     * list to an empty list will stop the filter without flushing data. Going from a non-empty list to a different
     * non-empty will update the filter, but old data may still be read from the filter until the new data is available.
     * Going from an empty list to another empty list does nothing.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The list of PIDs exceeds the maximum number of PIDs that can be filtered for or contains invalid PIDs.
     *
     */
    void setPids(in int[] pids);

    /**
     * Use this to enable the collection of the full transport stream via wildcard filtering.
     *
     * When calling this data from all PIDs will be returned. One practical usecase for this is if the list of PIDs
     * becomes larger than maxPids()
     */
    void setAllPids();

    /**
     * Get the maximum number of PIDs that can be filtered for.
     *
     * TODO is this in line with the C++ API?
     */
    int maxPids();

    /**
     * Register a consumer to read out data from the filter.
     *
     * @note Only one consumer can be registered at a time. Trying to register a second consumer cause
     * ::android::binder::Status::EX_INVALID_STATE to be thrown.
     */
    IRingBufferSource registerConsumer(in IRingBufferSourceListener listener);

    /**
     * Unregister the consumer.
     *
     * @note Only a consumer that was registered on this filter can be unregistered. Trying to unregister a different
     * consumer cause ::android::binder::Status::EX_INVALID_ARGUMENT to be thrown.
     */
    void unregisterConsumer(in IRingBufferSource consumer);
}
