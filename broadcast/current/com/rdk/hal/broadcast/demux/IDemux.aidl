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

import com.rdk.hal.broadcast.IBroadcastClientToken;
import com.rdk.hal.broadcast.demux.DemuxCapabilities;
import com.rdk.hal.broadcast.demux.IDemuxController;
import com.rdk.hal.broadcast.demux.IDemuxDataProvider;
import com.rdk.hal.broadcast.demux.IDemuxSoftwareInput;

/**
 * @brief Interface for a demux.
 *
 * Provides non-exclusive access to the demux instance, allowing multiple clients to connect to the same demux and
 * gather information about its capabilities. By connecting a data provider to the demux, clients can acquire exclusive
 * access to the demux through the controller interface, enabling them to set up filters and manage data flow.
 *
 * Exclusive claims are released when the owning client drops its Binder reference, including on abnormal termination,
 * so a crashed client cannot hold the demux indefinitely. See the design document for the mechanism.
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

    /**
     * @brief Get the ID of this demux.
     *
     * @returns The resource ID of this demux.
     */
    Id getId();

    /**
     * @brief Check whether this demux is already connected.
     *
     * Be aware of possible TOCTOU issues when using this method, especially in connection with connect().
     *
     * @returns Connection state of the demux.
     * @retval true The demux is connected to a DemuxDataProvider.
     * @retval false The demux is not connected.
     */
    boolean isConnected();

    /**
     * @brief Get the supported capabilities.
     *
     * @returns The capabilities of this demux.
     */
    DemuxCapabilities getCapabilities();

    /**
     * @brief Connect this Demux to a DemuxDataProvider.
     *
     * Each demux might only be connected to one DemuxDataProvider. The connected demux represented by the
     * DemuxController can be used to set up multiple filters, depending on the Capabilities.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The DemuxDataProvider is already connected to another
     *                                                           Demux, or the token is null or is not hosted by the
     *                                                           caller.
     *
     * @param[in] token The caller's client token. The claim is released if the owning client terminates.
     * @param[in] provider The DemuxDataProvider to connect the Demux to.
     *
     * @returns An IDemuxController, or null if this Demux is already connected (isConnected() is true).
     */
    @nullable IDemuxController connect(in IBroadcastClientToken token, in IDemuxDataProvider provider);

    /**
     * @brief Disconnect this Demux from a DemuxDataProvider.
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
     * @brief Create a software source for this demux.
     *
     * The created DemuxSoftwareInput can be used to write data to the demux, and only to *this* demux instance.
     *
     * @exception ::android::binder::Status::EX_UNSUPPORTED_OPERATION The demux does not support software sources.
     *
     * @returns An IDemuxSoftwareInput.Id, or null if the maximum number of DemuxSoftwareInput instances has already
     *          been created.
     */
    @nullable IDemuxSoftwareInput.Id createSoftwareInput();

    /**
     * @brief Destroy the given software source.
     *
     * The ID is invalidated and must not be passed to acquireSoftwareInput() again.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The software source ID is not valid for this demux.
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE The DemuxSoftwareInput is still acquired by a client.
     *
     * @param[in] id Non-null ID for the software source obtained from createSoftwareInput() on the same Demux.
     */
    void destroySoftwareInput(in IDemuxSoftwareInput.Id id);

    /**
     * @brief Acquire the given software source.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The software source ID is not valid for this demux,
     *                                                           or the token is null or is not hosted by the caller.
     *
     * @param[in] token The caller's client token. The claim is released if the owning client terminates.
     * @param[in] id Non-null software source ID obtained from createSoftwareInput() on the same Demux.
     *
     * @returns The software input instance for the given ID or null if already acquired.
     */
    @nullable IDemuxSoftwareInput acquireSoftwareInput(in IBroadcastClientToken token, in IDemuxSoftwareInput.Id id);

    /**
     * @brief Release the given software source.
     *
     * The software source remains created and can be acquired again; use destroySoftwareInput() to remove it.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The software source is not valid for this demux.
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE The DemuxSoftwareInput is not acquired by any client.
     *
     * @param[in] input The instance of the software input obtained from acquireSoftwareInput() on the same Demux.
     */
    void releaseSoftwareInput(in IDemuxSoftwareInput input);
}
