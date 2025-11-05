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
import com.rdk.hal.broadcast.demux.DemuxCapabilities;
import com.rdk.hal.broadcast.demux.IDemuxDataProvider;
import com.rdk.hal.broadcast.demux.IDemuxController;

/**
 *  @brief     Interface for a demux. 
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */


@VintfStability
interface IDemux {

    /** Demux resource ID type */
    @VintfStability
    parcelable Id {
        /** The undefined ID value. */
        const long UNDEFINED = -1;

        /** The actual resource ID */
        long value;
    }

    /**
     * Get the ID of this demux
     *
     * @returns Id the unique identifier for this demux
     */
    Id getId();

    /**
     * Check whether this demux is already connected
     *
     * @returns boolean true if connected, false otherwise
     */
    boolean isConnected();

    /**
     * Get the supported capabilities
     *
     * @returns DemuxCapabilities the capabilities of this demux
     */
    DemuxCapabilities getCapabilities();

    /**
     * Connect this Demux to a DemuxDataProvider
     *
     * Each Demux might only be connected to one DemuxDataProvider. The connected Demux represented
     * by the DemuxController can be used to set up multiple filters, depending on the Capabilities.
     *
     * @param[in] provider The DemuxDataProvider to connect the Demux to
     *
     * @returns IDemuxController or null on failure (e.g. already connected)
     */
    @nullable IDemuxController connect(in IDemuxDataProvider provider);

    /**
     * Disconnect this Demux from a DemuxDataProvider.
     *
     * The DemuxController object will be invalidated.
     *
     * @param[in] controller non-null DemuxController obtained from connect() on the same Demux
     *
     * @returns IDemuxDataProvider the provider instance passed to connect()
     */
    @nullable IDemuxDataProvider disconnect(in IDemuxController controller);
}
