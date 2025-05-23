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
import com.rdk.hal.videodecoder.CodecCapabilities;
import com.rdk.hal.videodecoder.DynamicRange;
 
/** 
 *  @brief     Video decoder capabilities definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
parcelable Capabilities
{
	/**
	 * Array of CodecCapability parcelables supported by this video decoder instance. 
	 */
    CodecCapabilities[] supportedCodecs;
	
	/**
	 * Array of DynamicRange values supported by this video decoder instance. 
	 */
    DynamicRange[] supportedDynamicRanges;
	
	/**
	 * Indicates if this decoder instance can work in secure video path (SVP) mode. 
	 * @see Property.SECURE_VIDEO
	 */
    boolean supportsSecure;
}
