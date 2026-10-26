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
 * @brief An RF frequency, carrying its unit in the type.
 *
 * Used wherever a frequency is tuned to, reported or bounded, so that a frequency cannot be confused with a symbol
 * rate or with a frequency expressed in another unit. The valid range is resource-specific: see
 * FrontendCapabilities.minFrequency and FrontendCapabilities.maxFrequency for the frontend in question.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
parcelable Frequency {
    /** No frequency selected. */
    const long UNDEFINED = 0;

    /** The frequency in Hertz. */
    long hertz = UNDEFINED;
}
