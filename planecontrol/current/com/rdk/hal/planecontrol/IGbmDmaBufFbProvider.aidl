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

parcelable GraphicsDmaBufFrameFd cpp_header "com/rdk/hal/planecontrol/GraphicsDmaBufFrameFd.h";

import com.rdk.hal.planecontrol.GbmDmaBufGraphicsFrameInfo;
import com.rdk.hal.planecontrol.GbmDmaBufCapabilities;

/** 
 *  @brief     Generic Buffer Management Dma-Buf interface.
 *  @author    Gerald Weatherup
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */
 
@VintfStability
interface IGbmDmaBufFbProvider
{

    /**
     * Gets the GBM Dma-Buf graphics frame buffer capabilities.
     *
     * This function can be called at any time and is not dependant on any Plane Control state.
     * The returned value is not allowed to change between calls.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns GbmDmaBufCapabilities
     *
     */
    GbmDmaBufCapabilities getCapabilities();

    /**
     * Commit the graphics frame buffer to be displayed on the graphics plane.
     *
     * This is a non-blocking function to commit this frame buffer to display at the earliest opportunity.
     * After the frame has been displayed an event is raised to indicate that the buffer, previously on display, is now free to be re-used.
     * 
     * @param[in] graphicsFrameId                The Frame Id of the buffer to replace the currently displaying buffer
     * 
     * @returns boolean
     * @retval true     The frame was accepted for display.
     * @retval false    The frame was not accepted because the graphics frame id is invalid or unknown to this provider.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid value.
     *
     *
     * @see createGraphicsFrameBuffer()
     */
    boolean commitGraphicsFrameBuffer(in int graphicsFrameId);
 
    /**
     * Creates a GBM (Generic Buffer Management) Dma-Buf graphics frame buffer for this plane.
     * 
     * This function can be called multiple times to create up to the maximum allowed graphics frames specified in the plane resources capabilities. 
     * The returned file descriptor can be the same for all created graphics frame buffers.
     * 
     * @param[in] width                 The requested width of the graphics frame buffer.  
     * @param[in] height                The requested height of the graphics frame buffer.  
     * @param[out] outInfo              A parcelable describing the graphics frame buffer.
     *
     * @returns A Dma-Buf file descriptor and the associated graphics frame buffer info.
     * 
     * width and height must not exceed the GbmDmaBufCapabilities. 
     * 
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid value.
     *
     * 
     * @see destroyGraphicsFrameBuffer()
     */
    GraphicsDmaBufFrameFd createGraphicsFrameBuffer(in int width, in int height, out GbmDmaBufGraphicsFrameInfo outInfo );

    /**
     * Frees a graphics frame buffer.
     * 
     * @param[in] GraphicsFrameId    The graphics frame buffer identifier
     * 
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid value.
     * 
     * @see createGraphicsFrameBuffer()
     */
    void destroyGraphicsFrameBuffer(in int GraphicsFrameId);

}
