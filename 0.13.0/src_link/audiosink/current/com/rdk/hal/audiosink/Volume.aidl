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
package com.rdk.hal.audiosink;
 
/** 
 *  @brief     Audio sink volume settings.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
parcelable Volume {

	/**
	 * Volume level of the audio sink.
	 * Range from 0.0 (minimum/muted) to 1.0 (maximum) in logarithmic dB scale.
	 */
    double volume;

	/**
	 * Muted state of the audio sink.
	 */
	boolean muted;    
}
