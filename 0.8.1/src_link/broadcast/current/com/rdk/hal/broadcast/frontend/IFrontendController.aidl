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
package com.rdk.hal.broadcast.frontend;
import com.rdk.hal.broadcast.frontend.FrontendType;
import com.rdk.hal.broadcast.frontend.IFrontendControllerListener;
import com.rdk.hal.broadcast.frontend.SignalInfoProperty;
import com.rdk.hal.broadcast.frontend.SignalInfoValue;
import com.rdk.hal.broadcast.frontend.TuneStatus;
import com.rdk.hal.broadcast.frontend.TuneParameters;
import com.rdk.hal.State;

/**
 *  @brief     FrontendController HAL interface.
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */

@VintfStability
interface IFrontendController {

    /**
	 * Closes the frontend.
     * 
     * Free's all attached (hardware) resources and brings the frontend back into a state where it
     * can be opened again. Stops the current tuning and all output on TSOUT
     * If successful the frontend transitions to a CLOSING state and then a CLOSED state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE
     * 
     * @pre The resource must be in State::READY.
     * 
     * @see IFrontend.open(), tune()
     */
    void close();

    /**
     * Tune with the given parameters
     *
     * The frontend must be in a ready or started state before it we can tune.
     * If successful the frontend will transition directly to the STARTED state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre The resource must be in State::READY or State::STARTED.
     * 
     * @see stopTune(), close()
     *
     * @param[in] tuneParams The tuning parameters of the request.
     */
    void tune(in TuneParameters tuneParams);

    /**
     * Will cancel any ongoing tune and set the tuner into unlocked state
     * The Frontend enters the STOPPING state and then the enters the READY state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre The resource must be in State::READY or State::STARTED.
     * 
     * @see tune()
     */
    void stopTune();

    /**
	 * Gets the current frontend tuneStatus.
     *
     * @returns TuneStatus enum value.
	 *
     * @see IFrontendControllerListener.onTuneStatusChanged().
     */  
    TuneStatus getTuneStatus();

    /** 
     * Return type for @ref IFrontend::getInfo 
     */
    @VintfStability
    parcelable SignalInfoReturn {
        /** Possible readiness values */
        @VintfStability
        enum Readiness {
            /** Clean value when default initialized */
            UNDEFINED = 0,
            /** The requested info is not available for this frontend or tune type */
            UNSUPPORTED,
            /** The info is generally supported but currently not available */
            UNAVAILABLE,
            /** The returned reading has to be considered unstable */
            UNSTABLE,
            /** A reliable reading */
            STABLE
        }

        /** 
         * The requested value 
         */
        SignalInfoValue value;
        
        /** 
         * The quality of the reading 
         */
        Readiness readiness;
    }

    /**
     * Get frontend signal information
     *
     * If the frontend is in any other state than State::STARTED, you can expect that 
     * Readiness is UNAVAILABLE for supported properties
     *
     * @param[in] properties A list of information types that shall be returned. Note that this has to
     *                   be a subset of the information types returned in the Capabilities set for
     *                   this frontend.
     * @returns The list of the requested information values that are in the set of the supported
     *         types.
     */
    SignalInfoReturn[] getSignalInfo(in SignalInfoProperty[] properties);
}
