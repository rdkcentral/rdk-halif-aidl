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
package com.rdk.hal.videodecoder;
import com.rdk.hal.videodecoder.Codec;
import com.rdk.hal.videodecoder.CodecProfile;
import com.rdk.hal.videodecoder.CodecLevel;

/**
 *  @brief     Codec capability definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */

@VintfStability
parcelable CodecCapabilities
{
	/**
	 * Defines the video codec type.
	 */
    Codec codec;

  	/**
     * Defines the profile for this Codec.
     */
    CodecProfile profile;

    /**
     * Defines the level for this Codec.
     */
    CodecLevel level;
	/**
	 * The maximum frame rate (FPS) supported for decode for this Codec.
	 * e.g. 25, 30, 50, 60, 120.
	 */
    int maxFrameRate;

	/**
	 * The maximum frame width (pixels) supported for decode for this Codec.
	 */
    int maxFrameWidth;

	/**
	 * The maximum frame height (pixels) supported for decode for this Codec.
	 */
    int maxFrameHeight;
}
