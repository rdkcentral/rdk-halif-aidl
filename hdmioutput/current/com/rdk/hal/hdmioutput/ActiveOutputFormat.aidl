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
package com.rdk.hal.hdmioutput;

import com.rdk.hal.hdmioutput.AdditionalColorimetryExtension;
import com.rdk.hal.hdmioutput.Colorimetry;
import com.rdk.hal.hdmioutput.ExtendedColorimetry;
import com.rdk.hal.hdmioutput.HDROutputMode;
import com.rdk.hal.hdmioutput.PixelFormat;
import com.rdk.hal.hdmioutput.QuantizationRange;
import com.rdk.hal.hdmioutput.VIC;

/**
 *  @brief     The video signal the HDMI output is sending now.
 *
 *  Read with IHDMIOutput.getActiveOutputFormat() and delivered whole by
 *  IHDMIOutputEventListener.onActiveOutputFormatChanged(). Every field
 *  describes the same instant: one negotiated change (e.g. a switch into
 *  HDR, which changes EOTF, colorimetry and colour depth together) is one
 *  event, so a client never sees a mix of old and new values.
 *
 *  Configured values stay in Property (e.g. HDR_OUTPUT_MODE may be AUTO);
 *  this parcelable is what they resolved to against the content and sink.
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
parcelable ActiveOutputFormat
{
    /** Video mode on the wire. Never VIC0_UNAVAILABLE. */
    VIC vic;

    /** Base colorimetry. AVI InfoFrame C. */
    Colorimetry colorimetry;

    /**
     * Extended colorimetry. AVI InfoFrame EC.
     * Meaningful only when colorimetry is EXTENDED_COLORIMETRY.
     */
    ExtendedColorimetry extendedColorimetry;

    /**
     * Additional colorimetry extension. AVI InfoFrame ACE.
     * Meaningful only when extendedColorimetry is
     * ADDITIONAL_COLORIMETRY_EXTENSION.
     */
    AdditionalColorimetryExtension additionalColorimetryExtension;

    /** Bits per colour component (8, 10, 12 or 16). */
    int colorDepth;

    /** Chroma format. AVI InfoFrame Y. */
    PixelFormat pixelFormat;

    /** Quantization range. AVI InfoFrame Q / YQ. */
    QuantizationRange quantizationRange;

    /** Dynamic range being signalled. Never AUTO. */
    HDROutputMode hdrOutputMode;
}
