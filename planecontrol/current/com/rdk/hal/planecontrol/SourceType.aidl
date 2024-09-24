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
 *  @brief     Video plane sources definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
@Backing(type="int")
enum SourceType
{
    /** 
     *  No video source is set for the video plane. Default value for all planes. 
     */
    NONE = 0,
 
    /** 
     *  A video sink is set as the source for the video plane. 
     */
    VIDEO_SINK = 1, 
     
    /** 
     *  A HDMI input is set as the source for the video plane. 
     */
    HDMI = 2,   
 
    /** 
     * A composite input is set as the source for the video plane. 
     */
    COMPOSITE = 3,
}
