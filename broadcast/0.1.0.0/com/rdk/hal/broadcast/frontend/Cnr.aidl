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
 * @brief A carrier to noise ratio, carrying its unit in the type.
 *
 * Reported through SignalInfoValue for SignalInfoProperty.CNR.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
parcelable Cnr {
    /**
     * The carrier to noise ratio in dB.
     *
     * Defaults to -1000.0, which is far outside any physical ratio and means "no reading". AIDL does not permit a
     * float constant, so unlike every other value type in this package the sentinel cannot be named. A client should
     * treat any value below -999.0 as absent rather than test for equality, and should in any case take
     * SignalInfoReturn.readiness as the authoritative statement of whether the reading is usable.
     */
    float dB = -1000.0f;
}
