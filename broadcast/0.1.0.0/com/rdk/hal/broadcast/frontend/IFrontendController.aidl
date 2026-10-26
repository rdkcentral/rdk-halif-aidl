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
 * @brief Frontend controller interface.
 *
 * This interface gives exclusive access to a frontend's resources, allowing *one* client to tune the frontend and query
 * its status. Only one controller will be given out per frontend at a time, guaranteeing the client uninterrupted
 * access to the frontend.
 *
 * The client might choose to internally share the frontend controller with other components, in which case it's the
 * client's responsibility to ensure that the internal usage is synchronized.
 *
 * The service side is thread-safe: concurrent calls on this interface are permitted and are serialised internally, so a
 * client sharing the controller across threads risks interleaved ordering but never a corrupted service state. Calls
 * may block for the duration of the underlying hardware operation.
 *
 * This interface deliberately provides no listener or callback interface. Tune status and signal information are
 * observed by polling getTuneStatus() and getSignalInfo(); the client chooses its own polling interval. Nothing is
 * pushed from the service, so a client that stops polling simply stops observing.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
interface IFrontendController {
    /**
     * @brief Tune with the given parameters.
     *
     * Asynchronous: returns as soon as the request has been accepted, not when lock is achieved. The frontend enters
     * TUNING and the client polls getTuneStatus() until it reports LOCKED or NO_SIGNAL.
     *
     * Retuning is allowed. Calling tune() while a tune is already in progress, or while locked, is legal and
     * supersedes the previous request: the frontend abandons it and begins tuning to the new parameters. The client
     * does not need to call stopTune() first.
     *
     * @param[in] tuneParams The carrier-specific parameters to tune with.
     *
     * @exception ::android::binder::Status::EX_UNSUPPORTED_OPERATION The given parameters are for a carrier type that
     *                                                                is not supported by this frontend.
     */
    void tune(in TuneParameters tuneParams);

    /** @brief Cancels any ongoing tune and sets the tuner into unlocked state. */
    void stopTune();

    /**
     * @brief Gets the current frontend tune status.
     *
     * This is the only means of observing tune progress: there is no completion callback, so a client waiting for a
     * tune to finish polls this method until it reports LOCKED or NO_SIGNAL. Loss of lock after a successful tune is
     * likewise only visible by continued polling.
     *
     * @returns Current tune status (e.g. IDLE, TUNING, NO_SIGNAL, LOCKED).
     */
    TuneStatus getTuneStatus();

    /** Return type for @ref IFrontendController::getSignalInfo. */
    @VintfStability
    parcelable SignalInfoReturn {
        /** Possible readiness values. */
        @VintfStability
        @Backing(type = "int")
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
     * @brief Get frontend signal information.
     *
     * @param[in] properties A list of information types that shall be returned. Note that this has to be a subset of
     *                       the information types returned in the Capabilities set for this frontend.
     *
     * @returns The list of the requested information values, in the same order as the requested properties.
     */
    SignalInfoReturn[] getSignalInfo(in SignalInfoProperty[] properties);
}
