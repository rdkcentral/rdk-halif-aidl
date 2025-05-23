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
import com.rdk.hal.hdmioutput.FreeSync;
 
/** 
 *  @brief     HDMI output platform capabilities definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
parcelable PlatformCapabilities
{
	/**
	 * The territory specific native frame rate for HDMI output.
	 * This should be selected as the default frame rate for HDMI outputs.
	 * This can be 0.0 to remain undefined and determined by the app or RDK middleware.
	 */
	double nativeFrameRate;

	/**
	 * Indicates type of AMD FreeSync supported by the platform.
	 * `FreeSync.UNSUPPORTED` if not supported.
	 * @see Capabilities.supportsFreeSync to identify which ports support FreeSync.
	 */
	FreeSync freeSync;
}
