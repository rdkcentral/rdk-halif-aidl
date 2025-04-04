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
package com.rdk.hal.videodecoder;

/** 
 *  @brief     Video frame pixel data formats.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
@Backing(type="int")
/**
 * Enumeration defining the supported pixel formats.
 */
enum PixelFormat 
{
    /**< YCbCr 4:2:2 pixel format. */
    YCBCR422 = 1,
    /**< YCbCr 4:4:4 pixel format. */
    YCBCR444 = 2,
    /**< YCbCr 4:2:0 pixel format. */
    YCBCR420 = 3,
    /**< Red, Green, Blue pixel format. */
    RGB = 4,

    /**< Native pixel format. This format is specific to the video decoder HAL output
     * and the plane control HAL input.
     */
    NATIVE = 100,
};