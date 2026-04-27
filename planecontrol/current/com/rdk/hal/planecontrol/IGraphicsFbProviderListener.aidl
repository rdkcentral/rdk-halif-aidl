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
package com.rdk.hal.planecontrol;
  
/** 
 *  @brief     Callbacks listener interface from Plane Control.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
oneway interface IGraphicsFbProviderListener
{
    /**
     * @brief     Called after a call to commitGraphicsFb() when the Graphics Frame Buffer has become current.
     * @param[in] oldGraphicsFbId    The Frame Id of the old frame replaced by the newly committed frame.
     * @param[in] elapsedRealtimeNanos  The CLOCK_MONOTONIC time when the old graphics frame was replaced by the new.
     *
     * If no old frame exists (e.g. the first time), -1 is returned as oldGraphicsFbId.
     */
    void onGfxFrameReleased(in int oldGraphicsFbId, in long elapsedRealtimeNanos);
}
