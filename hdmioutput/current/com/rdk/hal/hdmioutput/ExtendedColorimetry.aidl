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
 *  @brief     HDMI extended colorimetry enum.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 */
 
@VintfStability
@Backing(type = "int")
enum ExtendedColorimetry
{
	/**
	 * AVI InfoFrame C=3, EC=0
	 */
	XV_YCC_601 = 0,

	/**
	 * AVI InfoFrame C=3, EC=1
	 */
	XV_YCC_709 = 1,

	/**
	 * AVI InfoFrame C=3, EC=2
	 */
	S_YCC_601 = 2,

	/**
	 * AVI InfoFrame C=3, EC=3
	 */
	OP_YCC_601 = 3,

	/**
	 * AVI InfoFrame C=3, EC=4
	 */
	OP_RGB = 4,

	/**
	 * AVI InfoFrame C=3, EC=5
	 */
	BT2020_C_YCC = 5,

	/**
	 * AVI InfoFrame C=3, EC=6
	 * RGB when Y=0
	 * YCC when Y=1, 2 or 3
	 */
	BT2020_RGB_YCC = 6,

	/**
	 * AVI InfoFrame EC=7
	 * @see enum AdditionalColorimetryExtension
	 */
	ADDITIONAL_COLORIMETRY_EXTENSION = 7,
}
