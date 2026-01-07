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
package com.rdk.hal.broadcast;

import com.rdk.hal.broadcast.demux.IDemux;
import com.rdk.hal.broadcast.frontend.IFrontend;

/**
 *  @brief     BroadcastManager HAL interface.
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */

@VintfStability
interface IBroadcastManager {
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "BroadcastManager";

    /**
	 * Gets the platform list of frontend IDs.
     * 
     * @returns IFrontEnd.Id[]
     */
    IFrontend.Id[] getFrontendIds();

    /**
     * Get the frontend interface for the given ID
     *
     * @param[in] frontendId    The ID of the frontend.
     *
     * @returns IFrontend ID or null if the ID is invalid.
     */
    @nullable IFrontend getFrontend(in IFrontend.Id frontendId);

    /*
     * Open a instance of Demux.
     *
     * The opened demux can afterwards be used on a tuner or a software input
     *
     * @returns IDemux or null if we are out of demux resources.
     */
    @nullable IDemux openDemux();
}
