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
 *  @brief     Plane type definition.
 *
 *  The type says where the plane's pixels come from and where they go, which is what
 *  determines the interface used to drive it.
 *
 *  | Type | Pixels come from | Pixels go to | Interface |
 *  |---|---|---|---|
 *  | `VIDEO` | A mapped video source | The display | `IPlaneControl` |
 *  | `GRAPHICS` | The client, frame by frame | The display | `IGraphicsFbProvider` |
 *  | `CAPTURE` | A mapped video source | The client, frame by frame | `ICapture` |
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
@Backing(type="int")
enum PlaneType
{
    /**
     *  Video plane.
     *
     *  Displays a mapped video source. The source is selected with
     *  `IPlaneControl.setVideoSourceDestinationPlaneMapping()`, and position, size,
     *  z-order and alpha are set through the plane's `Property` values.
     */
    VIDEO = 0,

    /**
     *  Graphics plane.
     *
     *  Displays frames the client draws. `IPlaneControl.getGraphicsFbProvider()`
     *  provides the frame buffers, and the client creates, commits and destroys them
     *  through `IGraphicsFbProvider`. Frames travel from the client to the display.
     */
    GRAPHICS = 1,

    /**
     *  Capture plane.
     *
     *  Delivers a mapped video source's decoded frames to the client as Dma-Bufs it
     *  imports as GPU textures. `IPlaneControl.getCapture()` provides the capture
     *  interface, and the source is selected with
     *  `IPlaneControl.setVideoSourceDestinationPlaneMapping()` exactly as it is for a
     *  video plane - the destination is the client's texture instead of the display.
     *
     *  What such a plane can deliver, and how its buffer pool behaves, are stated in
     *  `CaptureCapabilities`. `PlaneCapabilities` carries its routing.
     *
     *  It runs in the opposite direction to a graphics plane. Both carry frames between
     *  the client and the pipeline, but a graphics plane takes frames from the client to
     *  the display, while a capture plane takes decoded frames from the pipeline to the
     *  client.
     */
    CAPTURE = 2
}
