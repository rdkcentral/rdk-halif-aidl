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
 *  @brief     Graphics Frame Buffer Info.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */

@VintfStability
parcelable GraphicsFbInfo {
 
    /* Uniquely identifies this Graphics Frame Buffer */
    int graphicsFbId;
 
    /* width of the created gfx frame in pixels */
    int pixelWidth;

    /* height of the created gfx frame in pixels */
    int pixelHeight;

    /* Stride - The number of bytes from the start of one row of pixels to the start of the next row. */
    int stride;

    /* Offset - The number of bytes from the very beginning of the DMA-BUF file descriptor's memory to the actual start of the pixel data.*/
    int offset;

    /* The pixel format of the returned graphics frame. */
    /* This is an opaque value expected to be known to the client EGL implementation */
    /* For validation purposes a constant value in the hfp can be used. */
    int format;   // FourCC format (e.g., DRM_FORMAT_ARGB8888)

    /*  modifiers that describe the buffer format. */ 
    /* This is an opaque value expected to be known to the client EGL implementation */
    /* For validation purposes a constant value in the hfp can be used. */
    long modifier;
}


