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

import com.rdk.hal.broadcast.demux.Filter;
import com.rdk.hal.broadcast.demux.FilterType;
import com.rdk.hal.ringbuffer.IRingBufferSink;
import com.rdk.hal.ringbuffer.IRingBufferSinkListener;

/**
 * Interface for an opened demux.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
interface IDemuxController {
    /**
     * Open a filter for the given filter type.
     *
     * The returned union contains exactly one active member, representing the concrete type-specific filter interface.
     *
     * @param[in] filterType The type of filter to create.
     *
     * @returns DemuxFilter or null on error (e.g. no filter available for the given type, or the implementation cannot
     *          create another instance).
     */
    @nullable Filter openFilter(in FilterType filterType);

    /**
     * Closes the given filter.
     *
     * The filter object will be invalidated. If the filter was not stopped before calling this method, the call to
     * closeFilter() will stop the filter first.
     *
     * @note Trying to close a filter that was not opened on this demux will result in
     * ::android::binder::Status::EX_ILLEGAL_ARGUMENT being thrown.
     *
     * @param[in] filter The filter to close.
     */
    void closeFilter(in Filter filter);

    /**
     * Open the demux for writing.
     *
     * This is used for writing data to the demux, e.g. for playing a recording or for feeding data from a network
     * source. It should work independently of the filters, i.e. it should be possible to write data to the demux while
     * filters are active and also if they are not. The data written to the demux will be processed by the filters and
     * made available to the clients as if it was coming from the tuner.
     *
     * @param listener The listener to receive notifications about the ring buffer sink.
     *
     * @returns The IRingBufferSink related to the demux's internal IRingBuffer.
     */
    @nullable IRingBufferSink openForWriting(in IRingBufferSinkListener listener);
}
