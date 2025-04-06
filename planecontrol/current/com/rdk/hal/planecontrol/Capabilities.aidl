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
import com.rdk.hal.planecontrol.PlaneType;
import com.rdk.hal.planecontrol.SourceType;
import com.rdk.hal.videodecoder.PixelFormat;
import com.rdk.hal.videodecoder.DynamicRange;
 
/**
 *  @brief     Plane resource capabilities definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
parcelable Capabilities
{
    /**
     * 0 based index of this plane resource.
     * Video planes shall be listed first, with the primary video plane at resource index 0.
     * Graphics planes are listed next.
     */
    int planeIndex;

    /**
     * The type of plane.
     */
    PlaneType type;

    /** 
     * The list of pixel formats supported by this plane. 
     */
    PixelFormat[] pixelFormats;
 
    /**
     * The list of video source types the plane supports.
     */
    SourceType[] sourceTypes;

    /** 
     * The maximum width and height in pixels the plane can be set to.
     * `maxWidth` must be <= `frameWidth` and `maxHeight` must be <= `frameHeight`.
     */
    int maxWidth;
    int maxHeight;
 
    /** 
     * The frame width and height the plane geometry references.
     * This defines the full frame coordinate system that `maxWidth`, `maxHeight` and other properties
     * are defined by.
     */
    int frameWidth;
    int frameHeight;
  
    /** 
     * Array of DynamicRange values supported by this plane instance. 
     */
    DynamicRange[] supportedDynamicRanges;
 
    /** 
     * The color depth of the pixel format. 
     * e.g. 8, 10, 12. 
     */
    int colorDepth;
 
    /** 
     * The maximum frame rate supported by the plane in frames per second. 
     * e.g. 60, 120.
     */
    int maxFrameRate;
 
    /** 
     * Indicates if the plane supports the ALPHA property. 
     */
    boolean supportsAlpha;
 
    /**
     * Indicates whether the plane supports the ZORDER property.
     * Must be false for the primary graphics plane.
     */
    boolean supportsZOrder;
 
    /**
     * Specifies the display latency of this plane.
     * Measured in vsync periods, the display latency is measured from
     * the moment a change is made to plane (e.g. video frame presented)
     * to the moment it appears on the output display (e.g. panel or HDMI output).
     */
    int vsyncDisplayLatency;
}
