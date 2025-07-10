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
 *  @brief     HDCP status type enum.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
 
@VintfStability
@Backing(type = "int")
enum HDCPStatus
{
	/**
	 * Not connected, not powered.
	 *
	 * Indicates the state is not yet determined or the operation is not applicable. Clients should poll or retry later.
	 */
	UNKNOWN = -1,

	/**
	 * The connection is unauthenticated.
	 */
	UNAUTHENTICATED = 0,

	/**
	 * HDCP authentication is in progress.
	 */
	AUTHENTICATION_IN_PROGRESS = 1,
	
	/**
	 * HDCP authentication failed.
	 */
	AUTHENTICATION_FAILURE = 2,
	
	/**
	 * HDCP is successfully authenticated.
	 */
	AUTHENTICATED = 3,
}
