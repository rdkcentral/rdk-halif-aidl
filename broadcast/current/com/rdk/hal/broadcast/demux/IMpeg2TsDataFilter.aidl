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
 * @brief Filter interface for opaque MPEG2-TS data.
 *
 * This is used for metadata, as well as in non-tunneled pipelines. In order to set the filter into an operational
 * state, setPids() or setAllPids() must be called.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
interface IMpeg2TsDataFilter {
    /**
     * @brief Set the PIDs to filter for.
     *
     * Going from an empty list to a non-empty list will start the filter without flushing data. Going from a non-empty
     * list to an empty list will stop the filter without flushing data. Going from a non-empty list (or from
     * setAllPids()) to a different non-empty will update the filter, but old data may still be read from the filter
     * until the new data is available. Going from an empty list to another empty list does nothing.
     *
     * Providing a list of PIDs that exceeds getMaxPids() or contains invalid PIDs will throw an exception and not
     * change the filter state.
     *
     * The implementation shall not provide any data before setPids() (with a non-empty list of PIDs) or setAllPids()
     * has been called for the first time. I.e. no data shall be available through the ring buffer that predates the
     * first call to one of these methods.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The list of PIDs exceeds the maximum number of PIDs
     *                                                           that can be filtered for or contains invalid PIDs.
     */
    void setPids(in int[] pids);

    /**
     * @brief Use this to enable the collection of the full transport stream via wildcard filtering.
     *
     * After calling this, data from all PIDs will be returned. Old, filtered data might still be available to read,
     * though, analogously to setPids(). One practical use-case for this is if the list of PIDs becomes larger than
     * getMaxPids().
     */
    void setAllPids();

    /**
     * @brief Get the maximum number of PIDs that can be filtered for.
     *
     * @returns The maximum number of PIDs accepted by setPids().
     */
    int getMaxPids();

    /**
     * @brief Register a consumer to read out data from the filter.
     *
     * @param[in] listener Listener notified when filtered data is available to read.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE The filter already has a consumer registered.
     *
     * @returns An IRingBufferSource interface used to read filtered data from the filter.
     */
    IRingBufferSource registerConsumer(in IRingBufferSourceListener listener);

    /**
     * @brief Unregister the consumer.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE The filter does not have a consumer registered.
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The consumer was not registered with this filter.
     */
    void unregisterConsumer(in IRingBufferSource consumer);
}
