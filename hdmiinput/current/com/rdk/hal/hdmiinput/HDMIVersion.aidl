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
package com.rdk.hal.hdmiinput;
 
/** 
 *  @brief     HDMI standard version.
 * 
 *  Reference: HDMI 2.1 Specification, Section 6.x for Video ID Codes.
 * 
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 */
 
@VintfStability
@Backing(type = "int")
enum HDMIVersion
{
	/**
	 * HDMI version 1.3 or 1.3a
	 */
	HDMI_1_3 = 0,

	/**
	 * HDMI version 1.4, 1.4a or 1.4b
	 */
	HDMI_1_4 = 1,

	/**
	 * HDMI version 2.0, 2.0a or 2.0b
	 */
	HDMI_2_0 = 2,

	/**
	 * HDMI version 2.1
	 */
	HDMI_2_1 = 3

}
