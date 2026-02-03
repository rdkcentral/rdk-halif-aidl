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
package com.rdk.hal.audiomixer;
import com.rdk.hal.audiomixer.AudioSourceType;

/**
 * @brief     Audio source to mixer input routing definition.
 * @details   Specifies which audio source is connected to which mixer input.
 *            Follows the pattern established by planecontrol::SourcePlaneMapping.
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 * @copyright Copyright 2024 RDK Management
 */
@VintfStability
parcelable InputRouting
{
    /**
     * The destination mixer input index.
     *
     * This specifies which mixer input to configure.
     * Valid range: 0 to (number of mixer inputs - 1) as defined in Capabilities.inputs[].
     * The index corresponds to the position in the Capabilities.inputs array.
     */
    int mixerInputIndex;

    /**
     * The audio source type to route to this mixer input.
     */
    AudioSourceType sourceType;

    /**
     * The instance index of the specified audio source type.
     *
     * For example:
     * - If sourceType is AUDIO_DECODER, sourceIndex specifies which decoder (0, 1, 2...).
     * - If sourceType is HDMI_INPUT, sourceIndex specifies which HDMI input port (0, 1, 2...).
     *
     * Ignored if `sourceType` is `AudioSourceType.NONE`.
     */
    int sourceIndex;
}
