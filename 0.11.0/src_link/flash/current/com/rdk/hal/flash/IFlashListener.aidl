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
package com.rdk.hal.flash;
import com.rdk.hal.flash.FlashImageResult;
 
/** 
 *  @brief     Flash listener callbacks interface definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
oneway interface IFlashListener
{
    /**
     * Callback which occurs during the background image flashing operation to provide progress reports.
     *
     * The `onProgress()` callback provides a percentage complete report.
     * After all image validations are complete and as flashing is about to start, 
     * 0% progress is reported.
     * On success, 100% progress is reported before the `onCompleted()` callback is made.
     *
     * @param[in] percentComplete   Percentage complete (0~100)
     */
    void onProgress(int percentComplete);

    /**
     * Callback which occurs when the background image flashing operation has completed.
     * 
     * On a successful flashing operation, the FlashImageResult::SUCCESS is returned, otherwise
     * an error result code is returned.
     * 
     * The `report` parameter can be an empty string, but it is recommended that error result codes
     * provide additional details in this parameter which can be logged by the RDK middleware
     * for analysis.
     * 
     * @param[in] result        Success or error FlashImageResult code.
     * @param[in] report        Optional string report to provide additional result details.
     */
    void onCompleted(in FlashImageResult result, in @utf8InCpp String report);
}
