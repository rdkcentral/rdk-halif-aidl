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
package com.rdk.hal.videodecoder;
import com.rdk.hal.metrics.MetricEvent;
import com.rdk.hal.videodecoder.ErrorCode;
import com.rdk.hal.videodecoder.State;

/**
 *  @brief     Event callbacks listener interface from video decoder.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
oneway interface IVideoDecoderEventListener {

    /**
	 * Callback when the decoder has raised an error.
     *
     * @param[in] errorCode 		    An ErrorCode enum value.
     * @param[in] vendorErrorCode  	    A vendor specific error code.
     */
    void onDecodeError(in ErrorCode errorCode, in int vendorErrorCode);

    /**
	 * Callback when the decoder has transitioned to a new state.
     *
     * @param[in] oldState	            The state that the decoder has transitioned from.
     * @param[in] newState              The new state that the decoder has transitioned to.
     */
    void onStateChanged(in State oldState, in State newState);

    /**
     * Callback when the decoder has reported a metric occurrence.
     *
     * One occurrence per call, stamped at detection rather than at delivery, so a
     * consumer can tell how long an event waited and two events keep their true
     * spacing however they were dispatched.
     *
     * This carries the measurable detail of an occurrence — which fault, where in
     * the stream, the vendor's own code for it. `onDecodeError()` remains the
     * control signal that a fault happened; the two describe the same fault from
     * different sides, and a decoder raising one raises the other.
     *
     * The event kind is a `MetricEventKind` value and its payload fields are
     * `MetricEventAttribute` values, so a listener can walk an occurrence whose
     * kind it does not specifically know.
     *
     * @param[in] event                 The occurrence, its identifier and its payload.
     */
    void onMetricEvent(in MetricEvent event);
}
