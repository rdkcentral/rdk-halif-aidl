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
import com.rdk.hal.panel.PQParameter;
import com.rdk.hal.videodecoder.DynamicRange;
import com.rdk.hal.AVSource;

/** 
 *  @brief     PQ parameter configuration.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */
 
@VintfStability
parcelable PQParameterConfiguration
{
	/**
	 * The PQ parameter.
	 */
	PQParameter pqParameter;

	/**
	 * The picture mode.
	 * null means wildcard which applies to all supported picture modes.
	 */
	@nullable String pictureMode;

	/**
	 * The AV source.
	 * AVSource.UNKNOWN means wildcard which applies to all supported AV sources.
	 */
	AVSource source;

	/**
	 * The video format dynamic range.
	 * DynamicRange.UNKNOWN means wildcard which applies to all supported dynamic range formats.
	 */
	DynamicRange format;
	
	/**
	 * The value for the PQ parameter.
	 */
	int value;
}
