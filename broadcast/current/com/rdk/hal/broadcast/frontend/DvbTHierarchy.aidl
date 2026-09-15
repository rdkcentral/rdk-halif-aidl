/*
 * If not stated otherwise in this file or this component's LICENSE file the following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 */
package com.rdk.hal.broadcast.frontend;

/**
 * Hierarchical transmission modes defined for DVB-T tuning.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
@Backing(type = "int")
enum DvbTHierarchy {
    /** Clean value when default initialized. */
    UNDEFINED = 0,
    /** Automatically detect the hierarchy. */
    AUTO,
    /** Non-hierarchical transmission. */
    NONE,
    /** Hierarchical transmission with alpha 1. */
    ALPHA_1,
    /** Hierarchical transmission with alpha 2. */
    ALPHA_2,
    /** Hierarchical transmission with alpha 4. */
    ALPHA_4,
}
