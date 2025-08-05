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
package com.rdk.hal.planecontrol;
  
/** 
 *  @brief     Plane properties definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
@Backing(type = "int")
enum Property
{
	/**
	 * Unique 0 based index per plane resource instance.
	 *
	 * Type: Integer
	 * Access: Read-only.
	 *
	 * @exception binder::Status EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
	 *
	 */
	RESOURCE_ID = 0,

    /**
	 * Left coordinate of the plane inside its frame coordinates. 
	 *
	 * Type: Integer
	 * Default is 0.
	 * Access: Read-write.
	 */
    X = 1,
 
    /**
	 * Top coordinate of the plane inside its frame coordinates. 
	 *
	 * Type: Integer
	 * Default is 0.
	 * Access: Read-write.
	 */
    Y = 2,
 
    /**
	 * Width of the plane inside its reference frame coordinates. 
	 *
	 * Type: Integer
	 * Default is Capabilities.maxWidth.
	 * Access: Read-write.
	 */
    WIDTH = 3,
 
    /**
	 * Height of the plane inside its reference frame coordinates. 
	 *
	 * Type: Integer
	 * Default is Capabilities.maxHeight.
	 * Access: Read-write.
	 */
    HEIGHT = 4,
 
    /**
	 * Alpha blending value for the whole plane. 0=transparent, 255=opaque. 
	 *
	 * Type: Integer
	 * Default is 255.
	 * Access: Read-write.
	 * @pre Capabilities.supportsAlpha must be true to support this property.
	 */
    ALPHA = 5,
 
    /**
	 * Z-order position of the plane. Higher z-order planes are composited above lower z-order planes. 
	 *
	 * Type: Integer
	 * Default is RESOURCE_ID property index.
	 * Access: Read-write.
	 */
    ZORDER = 6,
 
    /**
	 * Visibility of the plane.
	 *
	 * Type: Integer
	 *  0 - invisible (default)
	 *  1 - visible
	 * Access: Read-write.
	 */
    VISIBLE = 7,
  
    /**
	 * Overscan applied to a video frames presented on the video plane. 
	 * Overscan is specified in percentage and applied equally to all edges.
     * Overscan only applied to `VIDEO` planes.
	 *
	 * Type: Integer
	 *  0 - full image (no overscan).
	 * Access: Read-write.
	 */
    OVERSCAN = 8,
 
    /**
	 * Aspect ratio applied to a video plane.
     * Values are enumerated in AspectRatio.
	 *
	 * Type: Integer - enum AspectRatio
	 *  0 - AspectRatio::FULL_WITH_ASPECT
	 * Access: Read-write.
	 */
    ASPECT_RATIO = 9,
 
    /**
	 * Metrics 
	 */
    
}
