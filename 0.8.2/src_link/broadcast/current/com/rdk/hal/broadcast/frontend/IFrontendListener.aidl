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
import com.rdk.hal.State;

/**
 *  @brief     Listener for important changes on a frontend
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */

@VintfStability
oneway interface IFrontendListener {

    /**
	 * Callback when the frontend has transitioned to a new state.
     *
     * @param[in] oldState      The state that the frontend has transitioned from.
     * @param[in] newState      The new state that the frontend has transitioned to.
     */
    void onStateChanged(in State oldState, in State newState);

}
