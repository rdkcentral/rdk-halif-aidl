/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
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

package com.rdk.hal.compositeinput;

/**
 * @brief Video rectangle for positioning and sizing.
 * 
 * Defines a rectangular region in pixel coordinates for video output.
 * All coordinates are relative to the top-left corner of the display.
 */
@VintfStability
parcelable VideoRectangle
{
    /** X coordinate of top-left corner in pixels (minimum 0). */
    int x;
    
    /** Y coordinate of top-left corner in pixels (minimum 0). */
    int y;
    
    /** Width in pixels (minimum 0). */
    int width;
    
    /** Height in pixels (minimum 0). */
    int height;
}
