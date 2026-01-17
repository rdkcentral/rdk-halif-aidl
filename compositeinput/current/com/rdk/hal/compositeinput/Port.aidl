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
 * @brief Composite input port identifier and metadata.
 * 
 * Defines port identifiers and optional metadata for composite input ports.
 * Port ID ranges from 0 to (maxPorts - 1).
 */
@VintfStability
parcelable Port
{
    /** Port ID (0 to maxPorts-1). */
    int id;
    
    /** Optional human-readable port name (e.g., "Front Panel", "Rear"). */
    @utf8InCpp String name;
    
    /** Optional port description. */
    @utf8InCpp String description;
}
