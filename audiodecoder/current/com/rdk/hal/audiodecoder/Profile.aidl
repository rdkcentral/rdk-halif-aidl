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
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.audiodecoder;

import com.rdk.hal.audiodecoder.AACProfile;
import com.rdk.hal.audiodecoder.AVSProfile;
import com.rdk.hal.audiodecoder.DolbyAC3Profile;
import com.rdk.hal.audiodecoder.DolbyMATProfile;
import com.rdk.hal.audiodecoder.DTSProfile;
import com.rdk.hal.audiodecoder.REALAUDIOProfile;
import com.rdk.hal.audiodecoder.USACProfile;
import com.rdk.hal.audiodecoder.WMAProfile;

@VintfStability
/**
 * @brief Union of codec-specific profiles.
 * Only one field may be set at a time, matching the associated codec.
 */
union Profile {
    AACProfile aac;
    AVSProfile avs;
    DolbyAC3Profile dolbyAc3;
    DolbyMATProfile dolbyMat;
    DTSProfile dts;
    REALAUDIOProfile realAudio;
    USACProfile usac;
    WMAProfile wma;
}
