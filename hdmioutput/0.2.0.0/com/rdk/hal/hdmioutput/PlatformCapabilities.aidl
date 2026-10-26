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
package com.rdk.hal.hdmioutput;

import com.rdk.hal.hdmioutput.FreeSync;

/**
 *  @brief     HDMI output platform capabilities definition.
 *
 *  Describes static HDMI capabilities that apply across the entire platform.
 *  These are useful for test drivers, validation tools, or middleware decisions
 *  that need to understand global default behavior or hardware-specific constraints.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */
@VintfStability
parcelable PlatformCapabilities
{
    /**
     * The default/native frame rate the platform uses for HDMI output.
     *
     * Typically defined per territory (e.g., 50.0 Hz for PAL or 59.94 Hz for NTSC).
     * If set to 0.0, it is considered undefined, and the application or middleware
     * may determine the preferred default dynamically.
     */
    double nativeFrameRate;

    /**
     * The AMD FreeSync capability level supported globally by the platform.
     *
     * This indicates the highest FreeSync tier available on any output.
     * The per-port presence of FreeSync is reflected in Capabilities.supportsFreeSync.
     *
     * @see Capabilities.supportsFreeSync
     */
    FreeSync freeSync;
}
