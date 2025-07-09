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
import com.rdk.hal.planecontrol.SourceType; 
 
/**
 *  @brief     Video source to plane mapping definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
parcelable SourcePlaneMapping
{
    /**
     * The video source type to map.
     */    
    SourceType sourceType;  
 
    /**
     * The index of the video source.
     * Ignored if `sourceType` is `SourceType.NONE`.
     */
    int sourceIndex;
 
    /**
     * The index of the plane to use as the destination for the video source.
     * A value of -1 indicates no plane.
     */
    int destinationPlaneIndex;
}
