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
package com.rdk.hal.panel;

/**
 * @brief Panel AV source identifier.
 *
 * `type` identifies the source family, for example HDMI, COMPOSITE, DTV, IP,
 * AUTO, or UNKNOWN. `instance` optionally identifies a concrete source within
 * that family, for example 1 or 2 for HDMI inputs.
 */
@VintfStability
parcelable PanelSource {
    /** The source family, for example HDMI, COMPOSITE, DTV, IP, AUTO or UNKNOWN. */
    String type;
    /** The concrete source within the family, for example 1 or 2 for HDMI inputs. Null if not specified. */
    @nullable String instance;
}
