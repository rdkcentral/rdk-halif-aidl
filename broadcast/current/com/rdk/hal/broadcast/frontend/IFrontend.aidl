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

import com.rdk.hal.broadcast.demux.IDemuxDataProvider;
import com.rdk.hal.broadcast.frontend.FrontendCapabilities;
import com.rdk.hal.broadcast.frontend.FrontendType;
import com.rdk.hal.broadcast.frontend.IFrontendController;
import com.rdk.hal.broadcast.frontend.ILnbController;

/**
 * Front end HAL interface.
 *
 * Non-exclusive access to the front end. Multiple clients can work on the same frontend at the same time and access
 * information about it through this interface. When a client wants to tune the frontend, it has to acquire exclusive
 * access through the IFrontendController interface obtained from open().
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

    /** Get the ID of this frontend. */
    Id getId();

    /**
     * Check whether the frontend is already opened.
     *
     * Be aware of possible TOCTOU issues when using this method, especially in connection with open().
     */
    boolean isOpen();

    /** Gets the supported frontend types. */
    FrontendType[] getFrontendTypes();

    /**
     * Get the supported capabilities for the given frontend type.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The frontendType is not supported by this frontend.
     */
    FrontendCapabilities getCapabilities(in FrontendType frontendType);

    /**
     * Exclusively open the frontend for tuning.
     *
     * The returned IFrontendController interface is used by the client to facilitate all tune related operations.
     *
     * @returns IFrontendController or null on error (e.g. frontend already opened by another client).
     */
    @nullable IFrontendController open();

    /**
     * Close the frontend and invalidate the FrontendController.
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
     * Acquire a DemuxDataProvider that must be passed to a Demux.
     *
     * @returns A DemuxDataProvider that can be used to connect a Demux to this frontend or null on error (e.g. there is
     *          already a DemuxDataProvider acquired).
     */
    @nullable IDemuxDataProvider acquireDataProvider();

    /**
     * Releases the DemuxDataProvider previously acquired.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE The frontend is not connected to a Demux.
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The provider was not obtained from
     *                                                           acquireDataProvider() on the same frontend.
     */
    void releaseDataProvider(in IDemuxDataProvider provider);

    /**
     * Opens the LNB controller for exclusive access.
     *
     * The returned ILnbController interface is used for controlling satellite equipment.
     *
     * @exception ::android::binder::Status::EX_UNSUPPORTED_OPERATION The frontend does not support LNB control.
     *
     * @returns A LnbController or null on error (e.g. LNB controller already opened)
     */
    @nullable ILnbController openLnb();

    /**
     * Closes the LNB controller and invalidates the LnbController.
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
