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
package com.rdk.hal.panel;
import com.rdk.hal.videodecoder.DynamicRange;
import com.rdk.hal.AVSource;

/** 
 *  @brief     Display Panel Output Listener interface.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */

@VintfStability
oneway interface IPanelOutputListener
{
    /**
     * Callback when the picture mode changes.
     * 
     * This can occur on an AVSource or DynamicRange change in the video
     * or occurs after a call to setPictureMode().
     * 
     * @param[in] pictureMode   The new picture mode.
     */
    void onPictureModeChanged(in String pictureMode);
 
    /**
     * Callback when the video source being tracked for PQ settings changes.
     * 
     * This occurs when video starts, stops or on an AVSource change to the video.
     * When video stops then `AVSource.UNKNOWN` is passed in the call.
     * 
     * @param[in] avSource      The new AV source.
     */
    void onVideoSourceChanged(in AVSource avSource);

    /**
     * Callback when the dynamic range video format being tracked for PQ settings changes.
     * 
     * This occurs when video starts, stops or on a DynamicRange change in the video.
     * When video stops then `DynamicRange.UNKNOWN` is passed in the call.
     *
     * @param[in] dynamicRange      The new dynamic range video format.
     */
    void onVideoFormatChanged(in DynamicRange dynamicRange);

    /**
     * Callback when the video frame rate being tracked for PQ settings changes.
     * 
     * This occurs when video starts, stops or on a frame rate change in the video.
     * When video stops then the frame rate 0/0 is passed in the call.
     *
     * @param[in] frameRateNumerator        The numerator of the frame rate.
     * @param[in] frameRateDenominator      The denominator of the frame rate.
     */
    void onVideoFrameRateChanged(in int frameRateNumerator, in int frameRateDenominator);
 
    /**
     * Callback when the video resolution being tracked for PQ settings changes.
     * 
     * This occurs when video starts, stops or on a resolution change in the video.
     * When video stops then width and height 0,0 are passed in the call.
     *
     * @param[in] width     The video frame width.
     * @param[in] height    The video frame height.
     */
    void onVideoResolutionChanged(in int width, in int height);

    /**
     * Callback when the panel refresh rate changes.
     * 
     * This occurs when `setRefreshRate()` sets a new refresh rate or if frame rate
     * matching is enabled and it adjusts the refresh rate to best match the video frame rate.
     * 
     * @param[in] refreshRateHz     The new panel refresh rate.
     */
    void onRefreshRateChanged(in double refreshRateHz);

}
