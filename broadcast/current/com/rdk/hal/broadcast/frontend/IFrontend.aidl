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
package com.rdk.hal.broadcast.frontend;

import com.rdk.hal.broadcast.IBroadcastClientToken;
import com.rdk.hal.broadcast.demux.IDemuxDataProvider;
import com.rdk.hal.broadcast.frontend.FrontendCapabilities;
import com.rdk.hal.broadcast.frontend.FrontendType;
import com.rdk.hal.broadcast.frontend.IFrontendController;
import com.rdk.hal.broadcast.frontend.ILnbController;

/**
 * @brief Front end HAL interface.
 *
 * Non-exclusive access to the front end. Multiple clients can work on the same frontend at the same time and access
 * information about it through this interface. When a client wants to tune the frontend, it has to acquire exclusive
 * access through the IFrontendController interface obtained from open().
 *
 * Exclusive claims are released when the owning client drops its Binder reference, including on abnormal termination,
 * so a crashed client cannot hold the frontend indefinitely. See the design document for the mechanism.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
interface IFrontend {
    /** Frontend resource ID type. */
    @VintfStability
    parcelable Id {
        /** The undefined ID value. */
        const int UNDEFINED = -1;

        /** The actual resource ID. */
        int value;
    }

    /**
     * @brief Get the ID of this frontend.
     *
     * @returns The resource ID of this frontend.
     */
    Id getId();

    /**
     * @brief Check whether the frontend is already opened.
     *
     * Be aware of possible TOCTOU issues when using this method, especially in connection with open().
     *
     * @returns Open state of the frontend.
     * @retval true The frontend is opened by a client.
     * @retval false The frontend is not opened.
     */
    boolean isOpen();

    /**
     * @brief Gets the supported frontend types.
     *
     * @returns Array of frontend types supported by this frontend.
     */
    FrontendType[] getFrontendTypes();

    /**
     * @brief Get the supported capabilities for the given frontend type.
     *
     * The active member of FrontendCapabilities.specifics always matches the requested frontendType: ATSC selects
     * atsc, DVB_C selects dvbC, DVB_S selects dvbS and DVB_T selects dvbT. The client does not need to inspect the
     * union tag to know which member to read.
     *
     * @param[in] frontendType A type obtained from getFrontendTypes().
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The frontendType is not supported by this frontend.
     *
     * @returns The capabilities of this frontend for the given frontend type.
     */
    FrontendCapabilities getCapabilities(in FrontendType frontendType);

    /**
     * @brief Exclusively open the frontend for tuning.
     *
     * The returned IFrontendController interface is used by the client to facilitate all tune related operations.
     *
     * @param[in] token The caller's client token. The claim is released if the owning client terminates.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The token is null or is not hosted by the caller.
     *
     * @returns An IFrontendController, or null if the frontend is already opened by another client.
     */
    @nullable IFrontendController open(in IBroadcastClientToken token);

    /**
     * @brief Close the frontend and invalidate the FrontendController.
     *
     * Cleanup all attached (hardware) resources and brings the frontend back into a state where it can be opened again.
     * Stops the current tuning and all output on TSOUT.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE The frontend is not opened.
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The controller was not obtained from open() on this
     *                                                           frontend.
     *
     * @param controller Non-null controller obtained from open() on the same frontend.
     */
    void close(in IFrontendController controller);

    /**
     * @brief Acquire a DemuxDataProvider that must be passed to a Demux.
     *
     * @param[in] token The caller's client token. The claim is released if the owning client terminates.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The token is null or is not hosted by the caller.
     *
     * @returns A DemuxDataProvider that can be used to connect a Demux to this frontend, or null if one has already
     *          been acquired.
     */
    @nullable IDemuxDataProvider acquireDataProvider(in IBroadcastClientToken token);

    /**
     * @brief Releases the DemuxDataProvider previously acquired.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE The frontend has no DemuxDataProvider acquired.
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The provider was not obtained from
     *                                                           acquireDataProvider() on the same frontend.
     */
    void releaseDataProvider(in IDemuxDataProvider provider);

    /**
     * @brief Opens the LNB controller for exclusive access.
     *
     * The returned ILnbController interface is used for controlling satellite equipment.
     *
     * @param[in] token The caller's client token. The claim is released if the owning client terminates.
     *
     * @exception ::android::binder::Status::EX_UNSUPPORTED_OPERATION The frontend does not support LNB control.
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The token is null or is not hosted by the caller.
     *
     * @returns An ILnbController, or null if the LNB controller is already opened by another client.
     */
    @nullable ILnbController openLnb(in IBroadcastClientToken token);

    /**
     * @brief Closes the LNB controller and invalidates the LnbController.
     *
     * Cleanup all attached (hardware) resources and brings the LNB controller back into a state where it can be opened
     * again.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE The LNB controller is not opened.
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The controller was not obtained from openLnb() on this
     *                                                           frontend.
     *
     * @param[in] controller Non-null controller obtained from openLnb() on the same FrontEnd
     */
    void closeLnb(in ILnbController controller);
}
