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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.hdmiinput;

/**
 * @brief HDMI input properties used in property get/set functions.
 *
 * These keys are used in conjunction with getProperty(), setProperty(), and related
 * functions. Each key defines a known attribute or metric of the HDMI input resource.
 *
 * @author Luc Kennedy-Lamb
 * @author Peter Stieglitz
 * @author Amit Patel
 * @author Gerald Weatherup
 */
@VintfStability
@Backing(type="int")
enum Property 
{
    /**
     * Unique ID for the HDMI input port.
     *
     * Type: Integer
     * Access: Read-only
     */
    RESOURCE_ID = 0,

    /**
     * Count of HDMI packet errors detected since the port was started.
     * This value is reset on each open().
     *
     * Type: Integer
     * Special Value: -1 if not implemented by the vendor.
     * Access: Read-only
     */
    METRIC_PACKET_ERRORS = 1000

    /**
     * Additional keys may be introduced in future revisions.
     * Clients must tolerate unknown keys gracefully.
     */
}
