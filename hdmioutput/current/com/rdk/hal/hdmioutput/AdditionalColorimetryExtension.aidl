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
package com.rdk.hal.hdmioutput;
 
/** 
 *  @brief     HDMI additional colorimetry extension enum.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 */
 
@VintfStability
@Backing(type = "int")
enum AdditionalColorimetryExtension
{
	/**
	 * AVI InfoFrame C=3, EC=7, ACE=0
	 */
	DCI_P3_RGB_D65 = 0,

	/**
	 * AVI InfoFrame C=3, EC=7, ACE=1
	 */
	DCI_P3_RGB_THEATER = 1,
}
