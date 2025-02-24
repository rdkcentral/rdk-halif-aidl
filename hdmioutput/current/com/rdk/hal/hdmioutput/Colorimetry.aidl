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
 *  @brief     HDMI Colorimetry enum.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 */
 
@VintfStability
@Backing(type = "int")
enum Colorimetry
{
	/**
	 * AVI InfoFrame C=0
	 */
	NO_DATA = 0,

	/**
	 * AVI InfoFrame C=1
	 */
	SMPTE_170M = 1,

	/**
	 * AVI InfoFrame C=2
	 */
	ITU_R_BT709 = 2,

	/**
	 * AVI InfoFrame C=3
	 * @see enum ExtendedColorimetry
	 */
	EXTENDED_COLORIMETRY = 3,
}
