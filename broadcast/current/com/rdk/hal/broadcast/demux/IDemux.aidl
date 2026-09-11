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
import com.rdk.hal.broadcast.demux.IDemuxSoftwareInput;

/**
 * Interface for a demux.
 *
 * Provides non-exclusive access to the demux instance, allowing multiple clients to connect to the same demux and
 * gather information about its capabilities. By connecting a data provider to the demux, clients can acquire exclusive
 * access to the demux through the controller interface, enabling them to set up filters and manage data flow.
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

    /**
     * Check whether this demux is already connected.
     *
     * Be aware of possible TOCTOU issues when using this method, especially in connection with connect().
     */
    boolean isConnected();

    /** Get the supported capabilities. */
    DemuxCapabilities getCapabilities();

    /**
     * Connect this Demux to a DemuxDataProvider.
     *
     * Each demux might only be connected to one DemuxDataProvider. The connected demux represented by the
     * DemuxController can be used to set up multiple filters, depending on the Capabilities.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The DemuxDataProvider is already connected to another
     *                                                           Demux.
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE isConnected() is true.
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
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The DemuxController is not originating from this Demux.
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE isConnected() is false.
     *
     * @param[in] controller Non-null DemuxController obtained from connect() on the same Demux.
     *
     * @returns IDemuxDataProvider the provider instance passed to connect().
     */
    IDemuxDataProvider disconnect(in IDemuxController controller);

    /**
     * Create a software source for this demux.
     *
     * The created DemuxSoftwareInput can be used to write data to the demux, and only to *this* demux instance.
     *
     * @exception ::android::binder::Status::EX_UNSUPPORTED_OPERATION The demux does not support software sources.
     *
     * @returns IDemuxSoftwareInput or null on failure (e.g. maximum number of DemuxSoftwareInput instances has been
     *          reached).
     */
    @nullable IDemuxSoftwareInput.Id createSoftwareInput();

    /**
     * Release the given software source.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The software source ID is not valid for this demux.
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE The DemuxSoftwareInput is still acquired by a client.
     *
     * @param[in] id Non-null ID for the software source obtained from createSoftwareInput() on the same Demux.
     */
    void destroySoftwareInput(in IDemuxSoftwareInput.Id id);

    /**
     * Acquire the given software source.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The software source ID is not valid for this demux.
     *
     * @param[in] id Non-null software source ID obtained from createSoftwareInput() on the same Demux.
     */
    IDemuxSoftwareInput acquireSoftwareInput(in IDemuxSoftwareInput.Id id);

    /**
     * Release the given software source.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The software source is not valid for this demux.
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE The DemuxSoftwareInput is not acquired by any client.
     *
     * @param[in] input The instance of the software input obtained from acquireSoftwareInput() on the same Demux.
     */
    void releaseSoftwareInput(in IDemuxSoftwareInput input);
}
