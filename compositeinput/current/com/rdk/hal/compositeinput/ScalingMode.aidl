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
 * @brief Video scaling mode.
 * 
 * Defines how video is scaled and positioned within the output rectangle.
 */
@VintfStability
@Backing(type="int")
enum ScalingMode
{
    /** No scaling, direct pixel mapping (1:1). */
    NONE = 0,
    
    /** Scale to fit within rectangle, maintaining aspect ratio (letterbox/pillarbox). */
    ASPECT_FIT = 1,
    
    /** Scale to fill rectangle, maintaining aspect ratio (may crop). */
    ASPECT_FILL = 2,
    
    /** Scale to exact rectangle dimensions (may distort aspect ratio). */
    CUSTOM = 3,
}
