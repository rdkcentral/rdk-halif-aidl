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
 * @brief Scaling filter quality.
 * 
 * Defines the quality level for video scaling filters.
 * Higher quality may use more processing resources.
 */
@VintfStability
@Backing(type="int")
enum FilterQuality
{
    /** Fastest processing, lowest quality (nearest neighbor). */
    LOW = 0,
    
    /** Balanced quality and performance (bilinear). */
    MEDIUM = 1,
    
    /** Best quality, highest processing cost (bicubic or better). */
    HIGH = 2,
}
