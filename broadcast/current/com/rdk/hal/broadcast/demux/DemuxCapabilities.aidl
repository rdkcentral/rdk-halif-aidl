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

import com.rdk.hal.broadcast.demux.FilterType;

/**
 * Demux capabilities.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
parcelable DemuxCapabilities {
    /** Whether the demux accepts data from software sources. */
    boolean acceptsDataFromSoftware;

    /** Whether the demux accepts data from hardware sources. */
    boolean acceptsDataFromHardware;

    /** Whether the demux can hold back data. */
    boolean canHoldBackData;

    @VintfStability
    parcelable FilterCapability {
        /** The filter type. */
        FilterType filterType;

        /** Maximum number of instances of this filter type. */
        int maxInstances;

        /**
         * Maximum number of PIDs a single filter of this type can track simultaneously.
         *
         * Use 0 if not applicable (e.g. for tunnel filters that take a single PID).
         */
        int maxPids;
    }

    /**
     * Map of supported filter types to maximum instances.
     *
     * The service must only return one entry per filter type, with the maximum number of instances for that type.
     */
    FilterCapability[] supportedFilters;
}
