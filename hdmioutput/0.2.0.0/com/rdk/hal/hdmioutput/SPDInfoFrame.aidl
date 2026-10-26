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

import com.rdk.hal.hdmioutput.SPDSource;

/**
 *  @brief     Source Product Description (SPD) InfoFrame.
 *
 *  This structure defines metadata for the HDMI SPD InfoFrame as per CTA-861,
 *  allowing the source device to identify itself to the sink (e.g., TV or AV receiver).
 *
 *  The InfoFrame includes a vendor name, a product description string, and a
 *  classification of the source type.
 *
 *  All string fields are expected to be null-terminated if unused space remains.
 *  Characters must be 7-bit ASCII.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
@VintfStability
parcelable SPDInfoFrame
{
    /**
     * 8-character vendor name string.
     *
     * Encoded as 7-bit ASCII, padded with nulls if shorter than 8 bytes.
     * Must not exceed 8 bytes in length.
     */
    byte[8] vendorName;

    /**
     * 16-character product description string.
     *
     * Encoded as 7-bit ASCII, padded with nulls if shorter than 16 bytes.
     * Must not exceed 16 bytes in length.
     */
    byte[16] productDescription;

    /**
     * SPD source type information, identifying the role of the HDMI transmitter.
     *
     * See SPDSource enum for classification.
     */
    SPDSource spdSourceInformation;
}
