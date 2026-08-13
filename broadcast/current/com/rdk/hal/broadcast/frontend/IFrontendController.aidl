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

import com.rdk.hal.broadcast.frontend.FrontendType;
import com.rdk.hal.broadcast.frontend.SignalInfoProperty;
import com.rdk.hal.broadcast.frontend.SignalInfoValue;
import com.rdk.hal.broadcast.frontend.TuneParameters;
import com.rdk.hal.broadcast.frontend.TuneStatus;

/**
 * FrontendController HAL interface.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
interface IFrontendController {
    /** Tune with the given parameters. */
    void tune(in TuneParameters tuneParams);

    /** Cancels any ongoing tune and sets the tuner into unlocked state. */
    void stopTune();

    /** Gets the current frontend tune status. */
    TuneStatus getTuneStatus();

    /** Return type for @ref IFrontend::getSignalInfo. */
    @VintfStability
    parcelable SignalInfoReturn {
        /** Possible readiness values. */
        @VintfStability
        enum Readiness {
            /** Clean value when default initialized. */
            UNDEFINED = 0,
            /** The requested info is not available for this frontend or tune type. */
            UNSUPPORTED,
            /** The info is generally supported but currently not available. */
            UNAVAILABLE,
            /** The returned reading has to be considered unstable. */
            UNSTABLE,
            /** A reliable reading. */
            STABLE
        }

        /** The requested value. */
        SignalInfoValue value;

        /** The quality of the reading. */
        Readiness readiness;
    }

    /**
     * Get frontend signal information.
     *
     * @param[in] properties A list of information types that shall be returned. Note that this has to be a subset of
     *                       the information types returned in the Capabilities set for this frontend.
     *
     * @returns The list of the requested information values, in the same order as the requested properties.
     */
    SignalInfoReturn[] getSignalInfo(in SignalInfoProperty[] properties);
}
