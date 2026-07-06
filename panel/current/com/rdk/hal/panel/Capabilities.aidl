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
package com.rdk.hal.panel;
import com.rdk.hal.panel.PanelType;
import com.rdk.hal.panel.PQParameterCapability;
import com.rdk.hal.videodecoder.DynamicRange;
import com.rdk.hal.AVSource;

/**
 *  @brief     Panel capabilities definition.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 *
 *  PQ capability is modelled as a normalized relation:
 *  `pqContexts` declares the distinct (picture modes × video formats × AV sources)
 *  support sets once, and each entry in `pqParameters` references the context(s)
 *  it applies in by index.  Either orientation — "which contexts does parameter P
 *  apply in?" or "which parameters apply in context C?" — is a trivial derivation.
 *  For the latter, `IPanelOutput.getSupportedPQParameters()` answers directly.
 */
@VintfStability
parcelable Capabilities
{
    /**
     * The panel type.
     */
    PanelType panelType;

    int pixelWidth;
    int pixelHeight;

    int widthCm;    // centimeters
    int heightCm;

    /**
     * Whether frame rate matching is supported by the device.
     */
    boolean frameRateMatchingSupported;

    /**
     * Whether display fade control is supported by the device.
     */
    boolean fadeDisplaySupported;

    /**
     * Panel display refresh rates supported in Hz, used in frame rate matching.
     */
    double[] supportedRefreshRatesHz;

    /**
     * A named PQ support context — one set of (picture modes × video formats × AV sources).
     *
     * A context declares that every listed picture mode supports every listed
     * video format, restricted per format to the listed AV sources.
     * Platforms typically need only a small number of contexts
     * (e.g. "all modes/formats/sources" and "expert-mode only").
     */
    parcelable PQContext
    {
        /**
         * The picture modes in this context.
         */
        String[] pictureModes;

        /**
         * The AV sources supported for one video format.
         */
        parcelable FormatSources
        {
            /**
             * The dynamic range video format.
             */
            DynamicRange format;

            /**
             * The AV sources supported for this video format.
             */
            AVSource[] sources;
        }

        /**
         * The video formats in this context and their supported AV sources.
         */
        FormatSources[] formatSources;
    }

    /**
     * The distinct PQ support contexts for this platform.
     * Referenced by index from `PQParameterInfo.contextIndexes`.
     * The union of `pictureModes` across all contexts is the platform's
     * complete picture mode list.
     */
    PQContext[] pqContexts;

    /**
     * A supported PQ parameter and the context(s) it applies in.
     */
    parcelable PQParameterInfo
    {
        /**
         * The parameter identity, scope and value range.
         */
        PQParameterCapability capability;

        /**
         * Indexes into `pqContexts` for the context(s) this parameter applies in.
         * Global parameters (`capability.isGlobal == true`) apply in every
         * context regardless of this list.
         */
        int[] contextIndexes;
    }

    /**
     * The PQ parameters supported by this platform.
     * A parameter's presence implies support; unsupported parameters are not listed.
     */
    PQParameterInfo[] pqParameters;

    /**
     * Array of color temperature names.
     * e.g. { "Cool", "Normal", "Warm" }.
     * Each index of the String[] corresponds to the index of a color temperature preset
     * used in `PQParameter.COLOR_TEMPERATURE` and functions such as `set2PointWhiteBalance()`.
     */
    String[] colorTemperatureNames;
}
