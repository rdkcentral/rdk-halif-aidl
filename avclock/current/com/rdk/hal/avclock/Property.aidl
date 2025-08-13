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
 package com.rdk.hal.avclock;
 
/** 
 *  @brief     AV Clock properties used in property get/set functions.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
@Backing(type="int")
enum Property {

	/**
	 * Unique ID per AV Clock resource instance.
	 *
	 * Type: Integer
	 * Access: Read-only.
	 *
	 * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
	 *
	 */
	RESOURCE_ID = 0,

	/**
	 * Metrics
	 */

	/**
	 * Last measured A/V synchronisation accuracy in the session.
	 * 
	 * This is the relative time of audio AFTER video.
	 * It can be a negative value if audio is before video.
	 * Only valid if audio and video decoders are defined in the sync group.
	 * 
	 * This metric is reset on `open()` and `flush()` calls.
	 *
	 * Type: Integer
	 *  -1 means this metric is not yet implemented by the vendor.
	 * Access: Read-only.
	 *
	 * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
	 *
	 */
	METRIC_AV_SYNC_ACCURACY_MS = 1000,

	/**
	 * Count of re-sync events to bring audio and video in lip sync.
	 * 
	 * This metric is reset on `open()` and `flush()` calls.
	 *
	 * Type: Integer
	 *  -1 means this metric is not yet implemented by the vendor.
	 * Access: Read-only.
	 *
	 * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
	 *
	 */
	METRIC_AV_RESYNC_COUNT = 1001,
}
