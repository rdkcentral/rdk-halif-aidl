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
 *  @brief     HDMI pixel format enum.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 */
 
@VintfStability
@Backing(type = "int")
enum PixelFormat
{
	/**
	 * RGB 4:4:4 pixel format.
	 * AVI InfoFrame Y=0
	 */
	RGB_444 = 0,

	/**
	 * YCbCr 4:2:2 pixel format.
	 * AVI InfoFrame Y=1
	 */
	YCBCR_422 = 1,

	/**
	 * YCbCr 4:4:4 pixel format.
	 * AVI InfoFrame Y=2
	 */
	YCBCR_444 = 2,

	/**
	 * YCbCr 4:2:0 pixel format.
	 * AVI InfoFrame Y=3
	 */
	YCBCR_420 = 3
}

