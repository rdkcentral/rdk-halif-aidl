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
package com.rdk.hal.panel;
 
/** 
 *  @brief     PQ Parameter enumeration.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */

@VintfStability 
@Backing(type = "int")
enum PQParameter
{
    // 
    BRIGHTNESS = 0,                     //!< Picture parameter  is Brightness (video pixels)
    //
    CONTRAST = 1,                       //!< Picture parameter  is Contrast (video plane) 
    //
    SHARPNESS = 2,                      //!< Picture parameter  is Sharpness (video plane)  
    //
    SATURATION = 3,                     //!< Picture parameter  is Saturation (video plane)  
    //
    HUE = 4,                            //!< Picture parameter  is Hue (video plane)  
    //
    MANUAL_BACKLIGHT = 5,               //!< Picture parameter  is Backlight (fixed/global) (not the ALS value)  Setting will fail if ALS enabled.
    // Valid gamma values are defined in enum SDRGamma.
    SDR_GAMMA = 6,                      //!< Picture parameter  is SDR Gamma
    // 0..n depending on preconfigured number of presets.
    COLOR_TEMPERATURE = 7,              //!< Picture parameter  is Colour temperature (?)
    // 0=Fixed 1=Global 2=Local
    DIMMING_MODE = 8,                   //!< Picture parameter  is Dimming mode
    // 0..n presets defined by vendor (for global or local dimming)
    DIMMING_LEVEL = 9,                	//!< Picture parameter  is Local dimming level
    // Boolean
    LOW_LATENCY_STATE = 10,             //!< Picture parameter  is Low latency state
    //
    SATURATION_RED = 11,                //!< Picture parameter  is Component saturation red
    //
    SATURATION_BLUE = 12,               //!< Picture parameter  is Component saturation blue
    //
    SATURATION_GREEN = 13,              //!< Picture parameter  is Component saturation green
    //
    SATURATION_YELLOW = 14,             //!< Picture parameter  is Component saturation yellow
    //
    SATURATION_CYAN = 15,               //!< Picture parameter  is Component saturation cyan
    //
    SATURATION_MAGENTA = 16,            //!< Picture parameter  is Component saturation magenta
    //
    HUE_RED = 17,                       //!< Picture parameter  is Component hue red
    //
    HUE_BLUE = 18,                      //!< Picture parameter  is Component hue blue
    //
    HUE_GREEN = 19,                     //!< Picture parameter  is Component hue green
    //
    HUE_YELLOW = 20,                    //!< Picture parameter  is Component hue yellow
    //
    HUE_CYAN = 21,                      //!< Picture parameter  is Component hue cyan
    //
    HUE_MAGENTA = 22,                   //!< Picture parameter  is Component hue magenta
    //
    LUMA_RED = 23,                      //!< Picture parameter  is Component luma red
    //
    LUMA_BLUE = 24,                     //!< Picture parameter  is Component luma blue
    //
    LUMA_GREEN = 25,                    //!< Picture parameter  is Component luma green
    //
    LUMA_YELLOW = 26,                   //!< Picture parameter  is Component luma yellow
    //
    LUMA_CYAN = 27,                     //!< Picture parameter  is Component luma cyan
    //
    LUMA_MAGENTA = 28,                  //!< Picture parameter  is Component luma magenta
    // TBD: Boolean or Integer scale?
    MEMC = 29,                  		//!< Picture parameter  is MEMC
    // 0..n (0=off, n=maximum level)
    LOCAL_CONTRAST_LEVEL = 30,          //!< Picture parameter  is Local contrast

    /**
     * LED backlight local dimming zones matrix dimensions.
     */
    //LOCAL_DIMMING_ZONES_X = 31,  MOVE TO Caps if needed.
    //LOCAL_DIMMING_ZONES_Y = 32,

    /**
     * MPEG noise reduction.
     * integer 0..n (0=off, n=maximum level)
     */
    MPEG_NOISE_REDUCTION = 31,

    /**
     * Noise reduction.
     * integer 0..n (0=off, n=maximum level)
     */
    NOISE_REDUCTION = 32,

    /**
     * AI picture quality management engine.
     * boolean
     */
    AI_PQ_ENGINE = 33,

    /**
     * Ambient light sensor (ALS) control.
     * boolean
     */
    AMBIENT_LIGHT_SENSOR_CONTROL = 34,

}
