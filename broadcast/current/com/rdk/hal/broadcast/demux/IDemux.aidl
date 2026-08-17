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

import com.rdk.hal.broadcast.demux.DemuxCapabilities;
import com.rdk.hal.broadcast.demux.IDemuxController;
import com.rdk.hal.broadcast.demux.IDemuxDataProvider;
import com.rdk.hal.broadcast.demux.IDemuxSoftwareSource;

/**
 * Interface for a demux.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
interface IDemux {
    /** Demux resource ID type. */
    @VintfStability
    parcelable Id {
        /** The undefined ID value. */
        const int UNDEFINED = -1;

        /** The actual resource ID. */
        int value;
    }

    /** Get the ID of this demux. */
    Id getId();

    /** Check whether this demux is already connected. */
    boolean isConnected();

    /** Get the supported capabilities. */
    DemuxCapabilities getCapabilities();

    /**
     * Connect this Demux to a DemuxDataProvider.
     *
     * Each demux might only be connected to one DemuxDataProvider. The connected demux represented by the
     * DemuxController can be used to set up multiple filters, depending on the Capabilities.
     *
     * @param[in] provider The DemuxDataProvider to connect the Demux to.
     *
     * @returns IDemuxController or null on failure (e.g. already connected).
     */
    @nullable IDemuxController connect(in IDemuxDataProvider provider);

    /**
     * Disconnect this Demux from a DemuxDataProvider.
     *
     * The DemuxController object will be invalidated.
     *
     * @param[in] controller Non-null DemuxController obtained from connect() on the same Demux.
     *
     * @returns IDemuxDataProvider the provider instance passed to connect().
     */
    @nullable IDemuxDataProvider disconnect(in IDemuxController controller);

    /**
     * Create a software source for this demux.
     *
     * The created demux represented by the
     * DemuxSoftwareSource can be used to write data to the demux, depending on the Capabilities.
     * Only the software source can only provide data to this demux instance.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE The demux does not support software sources.
     *
     * @returns IDemuxSoftwareSource or null on failure (e.g. the demux does not support multiple software sources).
     */
    @nullable IDemuxSoftwareSource.Id createSoftwareSource();

    /**
     * Release the given software source.
     *
     * The software source object will be invalidated. If the reference count is 0 the software source will be
     * destroyed.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE The reference count is not zero
     *
     * @param[in] softwareSource Non-null software source obtained from createSoftwareSource() on the same Demux.
     */
    void destroySoftwareSource(in IDemuxSoftwareSource.Id softwareSource);

    /**
     * Acquire the given software source. The internal reference count will be incremented.
     *
     * @param[in] id Non-null software source ID obtained from createSoftwareSource() on the same Demux.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The software source ID is not valid for this demux.
     *
     * @returns IDemuxSoftwareSource
     */
    IDemuxSoftwareSource acquireSoftwareSource(in IDemuxSoftwareSource.Id id);

    /**
     * Release the given software source. The internal reference count will be decremented.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE The reference count is already zero.
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The software source is not valid for this demux.
     */
    void releaseSoftwareSource(in IDemuxSoftwareSource softwareSource);
}
