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
package com.rdk.hal.videosink;
  
/** 
 *  @brief     Video Sink properties definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
@Backing(type="int")
enum Property
{
	/**
	 * Unique 0 based index per video sink resource instance.
	 */
	RESOURCE_ID = 0,

	/**
	 * The number of frames in the video sink that are queued for display.
	 * This property must give a correct value in both tunnelled and non-tunnelled modes.
	 */
	SINK_QUEUE_DEPTH = 1,

	/**
	 * Set by the client to specify the AV source of the stream.  
	 * The AVSource is also set inside the FrameMetadata when output by a decoder.
	 * Default is 0 - AVUNKNOWN.
	 * @see enum AVSource for possible values.
	 */
	AV_SOURCE = 2,

	/**
	 * Set by the client to specify whether the first frame is rendered ahead of full playback.
	 * 
	 * The AV Clock linked to the Video Sink can be in a playing or paused state.
	 * If the first frame is ahead of the AV Clock time then it will still display but subsequent
	 * frames will not display until the AV Clock time matches its presentation time.
	 * 
	 * Type: boolean
	 *  0 - First frame is not rendered (default)
	 *  1 - First frame is rendered
	 */
	RENDER_FIRST_FRAME = 3,


    /**
	 * Metrics 
	 */
    
    /**
	 * Count of frames received.  Not necessarily displayed.
	 * -1 means this metric is not yet implemented by the vendor.
	 */  
	METRIC_FRAMES_RECEIVED = 1000,
    
    /**
	 * Count of frames presented.
	 * -1 means this metric is not yet implemented by the vendor.
	 */  
	METRIC_FRAMES_PRESENTED = 1001,
	
    /**
	 * Count of frames dropped, received but never displayed due to late delivery.
	 * Not relevant for graphics plane.
	 * -1 means this metric is not yet implemented by the vendor.
	 */  
    METRIC_FRAMES_DROPPED_LATE = 1002,
	
    /**
	 * Count of frames dropped, due to frame rate conversion.
	 * Not relevant for graphics plane.
	 * -1 means this metric is not yet implemented by the vendor.
	 */  
    METRIC_FRAMES_DROPPED_FRC = 1003,
	
    /**
	 * Count of frames repeated, due to frame rate conversion.
	 * Not relevant for graphics plane.
	 * -1 means this metric is not yet implemented by the vendor.
	 */  
    METRIC_FRAMES_REPEATED_FRC = 1004,
	
    /**
	 * Count of frames repeated, due to a missing frame at expected presentation time.
	 * Not relevant for graphics plane.
	 * -1 means this metric is not yet implemented by the vendor.
	 */  
    METRIC_FRAMES_REPEATED_MISSING_FRAME = 1005,
	
    /**
	 * Count of underflow events, due to empty frame queue at expected presentation time.
	 * Not relevant for graphics plane.
	 * -1 means this metric is not yet implemented by the vendor.
	 */  
    METRIC_UNDERFLOWED = 1006,
}
