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
 *  @brief      Dma-Buf interface capabilities definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
parcelable GraphicsFbCapabilities
{
   /**
     * The maxGraphicsFrameBuffers indicates the maximum number of frame buffers that can be created for use on this plane.
     */
    int maxGraphicsFrameBuffers;

    /** 
     * The maximum width and height in pixels that the frame buffer can be created with.
     * Typically the width and height will match the plane width and height.
     */
    int maxGraphicsFrameBufferWidth;
    int maxGraphicsFrameBufferHeight;

    /* The pixel format of the returned graphics frame. */
    /* This is an opaque value expected to be known to the client EGL implementation */
    /* For validation purposes a constant value in the hfp can be used. */
    int format;   // FourCC format (e.g., DRM_FORMAT_ARGB8888)

    /*  modifiers that describe the buffer format. */ 
    /* This is an opaque value expected to be known to the client EGL implementation */
    /* For validation purposes a constant value in the hfp can be used. */
    long modifier;
}
