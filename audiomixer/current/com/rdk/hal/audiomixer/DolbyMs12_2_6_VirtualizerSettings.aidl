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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.audiomixer;

import com.rdk.hal.audiomixer.DolbyMs12_2_6_VirtualizerMode;

/**
 * @brief Surround virtualizer settings returned by
 *        IDolbyMs12_2_6_Dap.getSurroundVirtualizer().
 *
 * Packages the current virtualizer mode and boost into a single parcelable so
 * the accessor can return both atomically. AIDL primitive parameters cannot be
 * `out`, which forces a parcelable return shape for paired accessors that
 * combine an enum with a primitive.
 */
@VintfStability
parcelable DolbyMs12_2_6_VirtualizerSettings {
    /** Current surround virtualizer mode. */
    DolbyMs12_2_6_VirtualizerMode mode;

    /** Current surround virtualizer boost in range 0 to 96. */
    int boost;
}
