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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.hdmioutput;

/** 
 *  @brief     HDMI content type enum.
 *
 *  Maps to the AVI InfoFrame fields ITC (InfoFrame Type Code) and CN (Content Type),
 *  allowing source devices to indicate the intended content profile for the video stream.
 *
 *  Reference: HDMI Specification – AVI InfoFrame ITC/CN fields.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type = "int")
enum ContentType {
    /**
     * Content type not specified – AVI InfoFrame ITC=0
     */
    UNSPECIFIED = -1,

    /**
     * Graphics content – AVI InfoFrame ITC=1, CN=0
     */
    GRAPHICS = 0,

    /**
     * Photo content – AVI InfoFrame ITC=1, CN=1
     */
    PHOTO = 1,

    /**
     * Cinema content – AVI InfoFrame ITC=1, CN=2
     *
     * Also used to declare FilmMaker Mode.
     */
    CINEMA = 2,

    /**
     * Game content – AVI InfoFrame ITC=1, CN=3
     *
     * Suggests the sink device enter low-latency mode or switch to a game-optimised picture mode.
     */
    GAME = 3
}
