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

import com.rdk.hal.panel.PQParameter;
import com.rdk.hal.panel.PanelSource;
import com.rdk.hal.videodecoder.DynamicRange;

/**
 * @brief Selector for a PQ parameter configuration.
 *
 * The selector identifies the PQ parameter and its runtime context only.
 * White-balance values are not addressed by additional selector keys; the
 * corresponding read operations return the complete 2-point or multi-point
 * white-balance bundle for the selected picture-mode, source, and dynamic-
 * range context.
 */
@VintfStability
parcelable PQParameterSelector {
    /**
     * The PQ parameter.
     */
    PQParameter pqParameter;

    /**
     * The picture mode.
     */
    String pictureMode;

    /**
     * The AV source.
     */
    PanelSource source;

    /**
     * The dynamic range.
     * DynamicRange.UNKNOWN means wildcard which applies to all supported dynamic ranges.
     */
    DynamicRange dynamicRange;
}
