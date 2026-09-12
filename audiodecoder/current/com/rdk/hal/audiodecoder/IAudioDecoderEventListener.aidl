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
package com.rdk.hal.audiodecoder;
import com.rdk.hal.audiodecoder.FrameMetadata;
import com.rdk.hal.audiodecoder.ErrorCode;
import com.rdk.hal.audiodecoder.State;
import com.rdk.hal.metrics.MetricEvent;

/**
 *  @brief     Events callbacks listener interface from audio decoder.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
oneway interface IAudioDecoderEventListener {

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
     *
     * @see getState()
     */
    void onStateChanged(in State oldState, in State newState);
 
    /**
     * Callback when a metric occurrence has been reported.
     *
     * One occurrence per call, stamped at detection rather than at delivery, so a
     * consumer can tell how long an event waited and two events keep their true
     * spacing however they were dispatched.
     *
     * An occurrence is pushed because a read cannot carry it: a condition that
     * began and ended between two reads is invisible to a reader however fast it
     * polls. The existing callbacks on this interface remain the control signals
     * that something happened; this carries the measurable detail of it.
     *
     * The event kind is a `MetricEventKind` value and its payload fields are
     * `MetricEventAttribute` values, so a listener can walk an occurrence whose
     * kind it does not specifically know.
     *
     * @param[in] event                 The occurrence, its identifier and its payload.
     */
    void onMetricEvent(in MetricEvent event);
}

