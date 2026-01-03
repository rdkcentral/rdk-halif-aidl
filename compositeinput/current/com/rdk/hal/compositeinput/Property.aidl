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
 * @brief Port property identifiers.
 * 
 * Defines extensible properties that can be queried or configured
 * on a per-port basis. Properties 0-999 are for configuration and status.
 * Properties 1000+ are for metrics.
 */
@VintfStability
@Backing(type="int")
enum Property
{
    /** Signal strength in dBm (int, read-only). */
    SIGNAL_STRENGTH = 0,
    
    /** Detected video standard (VideoStandard enum, read-only). */
    VIDEO_STANDARD = 1,
    
    /** Detected color system (VideoStandard enum, read-only). */
    COLOR_SYSTEM = 2,
    
    /** Audio signal present (boolean, read-only). */
    AUDIO_PRESENT = 3,
    
    /** Macrovision copy protection detected (boolean, read-only). */
    MACROVISION_DETECTED = 4,
    
    // Future properties can be added here (5-999) without breaking API
    
    /** Metric: Average signal lock time in milliseconds (long, read-only). */
    METRIC_SIGNAL_LOCK_TIME = 1000,
    
    /** Metric: Total count of signal drops (long, read-only). */
    METRIC_SIGNAL_DROPS = 1001,
    
    /** Metric: Total uptime in milliseconds (long, read-only). */
    METRIC_UPTIME = 1002,
    
    // Future metrics can be added here (1003+) without breaking API
}
