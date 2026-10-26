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
package com.rdk.hal;
 
/** 
 * @brief     AV source type definitions.
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 */
 
@VintfStability
@Backing(type="int")
enum AVSource {   

	/**
	 * Source is automatically determined by the system.
	 */
    AUTO = -1,

	/**
	 * Source is unknown and should be treated as IP.
	 */
    UNKNOWN = 0,

	/**
	 * Source is streamed over IP.
	 */
    IP = 1,

	/**
	 * Source is from a broadcast tuner.
	 */
    TUNER = 2,

	/**
	 * Source is from a system application.
	 * This indicates a PCM system sound clip.
	 */
	SYSTEM = 3,

	/**
	 * Source is from a HDMI input port.
	 */
	HDMI_1 = 101,
	HDMI_2 = 102,
	HDMI_3 = 103,
	HDMI_4 = 104,
	HDMI_5 = 105,

	/**
	 * Source is from a composite input port.
	 */
	COMPOSITE_1 = 201,
	COMPOSITE_2 = 202,
	COMPOSITE_3 = 203,
	COMPOSITE_4 = 204,
	COMPOSITE_5 = 205,
}
