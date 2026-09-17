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
package com.rdk.hal.broadcast;

import com.rdk.hal.broadcast.ImplementationVersion;
import com.rdk.hal.broadcast.ca.ICaSlot;
import com.rdk.hal.broadcast.demux.IDemux;
import com.rdk.hal.broadcast.frontend.IFrontend;

/**
 * @brief BroadcastManager HAL interface.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
interface IBroadcastManager {
    /**
     * The service name to publish.
     *
     * To be returned by getServiceName() in the derived class.
     */
    const @utf8InCpp String serviceName = "BroadcastManager";

    /**
     * @brief Gets the service implementation version.
     *
     * This is not the same as the interface version, which is defined for the AIDL interface itself. The same
     * implementation version may implement multiple versions of the interface, and multiple implementations versions
     * may implement the same interface version (for example following internal bug fixes).
     *
     * @returns The implementation name and semantic version of the service.
     */
    ImplementationVersion getImplementationVersion();

    /**
     * @brief Gets the platform list of frontend IDs.
     *
     * @returns Array of IFrontend.Id values for all frontends on this platform.
     */
    IFrontend.Id[] getFrontendIds();

    /**
     * @brief Get the frontend interface for the given ID.
     *
     * @param[in] frontendId An ID obtained from getFrontendIds().
     *
     * @returns The frontend interface for the given ID.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT if the ID is invalid.
     */
    IFrontend getFrontend(in IFrontend.Id frontendId);

    /**
     * @brief Gets the list of demux IDs available on this platform.
     *
     * @returns Array of IDemux.Id values for all demuxes on this platform.
     */
    IDemux.Id[] getDemuxIds();

    /**
     * @brief Get the demux interface for the given ID.
     *
     * @param[in] demuxId An ID obtained from getDemuxIds().
     *
     * @returns The demux interface for the given ID.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT if the ID is invalid.
     */
    IDemux getDemux(in IDemux.Id demuxId);

    /**
     * @brief Gets the list of CA slot IDs available on this platform.
     *
     * @returns Array of ICaSlot.Id values for all CA slots on this platform.
     */
    ICaSlot.Id[] getCaSlotIds();

    /**
     * @brief Get the CA slot interface for the given ID.
     *
     * @param[in] slotId An ID obtained from getCaSlotIds().
     *
     * @returns The CA slot interface for the given ID.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT if the ID is invalid.
     */
    ICaSlot getCaSlot(in ICaSlot.Id slotId);
}
