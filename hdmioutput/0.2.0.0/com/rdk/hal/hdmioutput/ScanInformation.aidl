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

/**
 *  @brief     HDMI AVI InfoFrame Scan Information enum.
 *
 *  Defines how the HDMI signal describes scan handling. This affects how the
 *  display should scale or crop content, particularly in SD/HD modes.
 *
 *  Mapped to the AVI InfoFrame `S[1:0]` field (Scan Information).
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type = "int")
enum ScanInformation
{
    /**
     * No scan information is provided to the sink.
     * The receiver may infer default scan behaviour.
     * AVI InfoFrame S = 0
     */
    NO_DATA = 0,

    /**
     * Content is composed for an overscanned display.
     * The sink is expected to apply overscan, cropping part of the active image.
     * AVI InfoFrame S = 1
     */
    OVERSCAN = 1,

    /**
     * Content is composed for an underscanned display.
     * The sink is expected to show the full active image area without cropping.
     * AVI InfoFrame S = 2
     */
    UNDERSCAN = 2,

    /**
     * Reserved value per HDMI/CTA-861 spec.
     * Should not be used unless explicitly defined in future standards.
     * AVI InfoFrame S = 3
     */
    RESERVED = 3
}
