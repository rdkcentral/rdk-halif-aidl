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

    /** Check whether the frontend is already opened. */
    boolean isOpen();

    /** Gets the supported frontend types. */
    FrontendType[] getFrontendTypes();

    /**
     * Get the supported capabilities for the given frontend type.
     *
     * @param frontendType The type of capabilites to request.
     *
     * @returns Capabilities or null if the type is not supported.
     */
    @nullable FrontendCapabilities getCapabilities(in FrontendType frontendType);

    /**
     * Open the frontend in a mode where it is ready to tune.
     *
     * The returned IFrontendController interface is used by the client facilitate all tune related operations.
     *
     * @pre isOpen() == false
     *
     * @see IFrontendController
     *
     * @returns IFrontendController or null on error.
     */
    @nullable IFrontendController open();

    /**
     * Close the frontend and invalidate the FrontendController.
     *
     * Cleanup all attached (hardware) resources and brings the frontend back into a state where it can be opened again.
     * Stops the current tuning and all output on TSOUT.
     *
     * @pre isOpen() == true
     *
     * @param controller Non-null controller obtained from open() on the same frontend.
     */
    void close(in IFrontendController controller);

    /**
     * Acquire a DemuxDataProvider that must be passed to a DemuxController.
     *
     * @returns IDemuxDataProvider or null on error
     */
    @nullable IDemuxDataProvider acquireDataProvider();

    /**
     * Releases the DemuxDataProvider previously acquired.
     *
     * @param provider A non-null provider obtained from acquireDataProvider() on the same frontend.
     */
    void releaseDataProvider(in IDemuxDataProvider provider);

    /**
     * Opens the LNB controller. Non-blocking.
     *
     * The returned ILnbController interface is used for controlling satellite equipment.
     *
     * @returns ILnbController or null on error (e.g. LNB controller already opened)
     */
    @nullable ILnbController openLnb();

    /**
     * Closes the LNB controller and invalidates the LnbController.
     *
     * Cleanup all attached (hardware) resources and brings the LNB controller back into a state where it can be opened
     * again.
     *
     * @param controller non-null controller obtained from openLnb() on the same FrontEnd
     */
    void closeLnb(in ILnbController controller);
}
