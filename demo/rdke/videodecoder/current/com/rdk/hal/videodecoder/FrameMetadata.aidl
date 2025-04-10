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
import com.rdk.hal.videodecoder.ScanType;
import com.rdk.hal.videodecoder.PixelFormat;
import com.rdk.hal.videodecoder.DynamicRange;
import com.rdk.hal.AVSource;

/** 
 *  @brief     Decoded video frame metadata, relating to the frame output from the video decoder.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
parcelable FrameMetadata {

    /**
	 * Pixel aspect ratio (PAR) defined as the ratio parX:parY.
     * e.g. 1:1 for square pixels, 480i=10:11, 576i=59:54
     * @see Rec.601 and https://en.wikipedia.org/wiki/Pixel_aspect_ratio
     */
    int parX;
    int parY;
 
    /**
	 * Source aspect ratio (SAR) defined as the ratio sarX:sarY.
     * e.g. 720:480, 3840:2160
     */
    int sarX;
    int sarY;
	
	/**
	 * The coded width and height of the video frame in pixels. 
	 * Decoded video frame buffers hold the video frame in coded dimensions.
	 */
    int codedWidth;
    int codedHeight;

	/**
	 * The active display dimensions of the video frame in pixels. 
	 * These dimensions can be smaller than the coded dimensions to specify a 
	 * smaller central region to display inside the coded video frame.
	 * The active dimensions should reflect any display frame or bar data from the stream.
	 */
    int activeX;
	int activeY;
    int activeWidth;
	int activeHeight;

	/**
	 * The color depth in bits. 
	 * e.g. 8, 10, 12. 
	 */
    int colorDepth;
	
	/**
	 * Pixel format of the video frame. 
	 */
	PixelFormat pixelFormat;
	
	/**
	 * Dynamic range of the video frame.
	 */
	DynamicRange dynamicRange;
	
	/**
	 * The picture scan type output from the decoder. 
	 */
    ScanType scanType;
	
	/**
	 * Active format description code. 
	 * See https://en.wikipedia.org/wiki/Active_Format_Description
	 */
    int afd;
 
	/**
	 * Frame rate decoded from the video stream expressed as a fraction.
	 * Use 0/0 if unknown.e
	 * e.g. 24fps = 24/1, 59.94fps = 60000/1001
	 */
	int frameRateNumerator;
	int frameRateDenominator;
	
	/**
	 * End of stream marker found in the video bitstream.
	 */
	boolean endOfStream;
	
	/**
	 * Discontinuity indicator where the PTS for this frame is likely to be discontinuous to the previous.
	 */
	boolean discontinuity;
	
	/**
	 * Indicates if the video should be delivered in low latency mode.
	 */
	boolean lowLatency; 
		
//TODO: colorimetry for static HDR metadata... - must have matching properties
	
	/**
	 * The source of the video frame.
	 * When the frame is presented the source may be used to configure the TV picture mode settings.
	 */
	AVSource source;

	/**
	 * SHA1 calculation value.
	 * Only set when SHA1_CALC is set 1=on
	 */ 
	byte[] sha1;

	/**
	 * Private extension for future use. 
	 */
    ParcelableHolder extension;
}
