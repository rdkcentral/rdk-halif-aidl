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

import com.rdk.hal.broadcast.demux.IDemuxDataProvider;
import com.rdk.hal.ringbuffer.IRingBufferSink;
import com.rdk.hal.ringbuffer.IRingBufferSinkListener;

/**
 * Interface for a demux software input that can be used to feed data into a demux.
 *
 * Possible use-cases are  playing a recording from a file or for feeding data from a network source.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
interface IDemuxSoftwareInput {
    /** Demux resource ID type. */
    @VintfStability
    parcelable Id {
        /** The undefined ID value. */
        const int UNDEFINED = -1;

        /** The actual resource ID. */
        int value;
    }

    /** Get the ID of this software input. */
    Id getId();

    /**
     * Open the demux for writing.
     *
     * This is used for writing data to the demux, e.g. for playing a recording from a file or for feeding data from a
     * network source. It will work independently of the filters, i.e. it should be possible to write data to the demux
     * while filters are active and also if they are not. The data written to the demux will be processed by the filters
     * and made available to the clients as if it was coming from the tuner.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE The software input is already opened for writing or is
     *                                                        connected through a DemuxDataProvider.
     */
    IRingBufferSink openForWriting(in IRingBufferSinkListener listener);

    /**
     * Close the demux for writing.
     *
     * The IRingBufferSink obtained from openForWriting() will be invalidated.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE The software input is not opened for writing.
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The bufferSink was not obtained from openForWriting()
     *                                                           on the same software input.
     */
    void closeForWriting(in IRingBufferSink bufferSink);

    /**
     * Acquire a DemuxDataProvider that must be passed to a Demux.
     *
     * @returns A DemuxDataProvider that can be used to connect to a Demux or null on failure (e.g. there is already a
     *          DemuxDataProvider acquired).
     */
    @nullable IDemuxDataProvider acquireDataProvider();

    /**
     * Releases the DemuxDataProvider previously acquired.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE The software input is not connected to a Demux.
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The provider was not obtained from
     *                                                           acquireDataProvider() on the same software input.
     */
    void releaseDataProvider(in IDemuxDataProvider provider);
}
