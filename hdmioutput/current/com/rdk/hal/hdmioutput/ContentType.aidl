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
 *  @brief     HDMI content type enum.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 */
 
@VintfStability
@Backing(type = "int")
enum ContentType
{
	/**
	 * AVI InfoFrame ITC=0
	 */
	UNSPECIFIED = -1;

	/**
	 * AVI InfoFrame ITC=1, CN=0
	 */
	GRAPHICS = 0;

	/**
	 * AVI InfoFrame ITC=1, CN=1
	 */
	PHOTO = 1;

	/**
	 * AVI InfoFrame ITC=1, CN=2
	 * CINEMA is also used to declare FilmMaker mode.
	 */
	CINEMA = 2;

	/**
	 * AVI InfoFrame ITC=1, CN=3
	 * GAME provides a hint to the connected TV to enter a low latency state and/or switch to a Game picture mode.
	 */
	GAME = 3;
}
