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
 * @brief Port telemetry metrics.
 * 
 * Statistical and telemetry data for a composite input port,
 * useful for diagnostics and monitoring.
 */
@VintfStability
parcelable PortMetrics
{
    /** Total number of times signal lock was achieved. */
    long totalSignalLockCount;
    
    /** Total number of times signal was lost. */
    long totalSignalLossCount;
    
    /** Average time to achieve signal lock in milliseconds. */
    long averageSignalLockTimeMs;
    
    /** Most recent signal lock time in milliseconds. */
    long lastSignalLockTimeMs;
    
    /** Total uptime of this port in milliseconds. */
    long uptimeMs;
    
    /** Timestamp when metrics were last reset (milliseconds since epoch). */
    long lastResetTimestampMs;
}
