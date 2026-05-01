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

import com.rdk.hal.planecontrol.GraphicsFbInfo;
import com.rdk.hal.planecontrol.GraphicsFbCapabilities;

/** 
 *  @brief     Graphics Frame Buffer (Fb) interface.
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
interface IGraphicsFbProvider
{

    /**
     * Gets the graphics frame buffer capabilities.
     *
     * This function can be called at any time and is not dependent on any Plane Control state.
     * The returned value is not allowed to change between calls.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns GraphicsFbCapabilities
     *
     */
    GraphicsFbCapabilities getCapabilities();

    /**
     * Commit the graphics frame buffer to be displayed on the graphics plane.
     *
     * This is a non-blocking function to commit this frame buffer to display at the earliest opportunity.
     * After the frame has been displayed an event is raised to indicate that the buffer, previously on display, is now free to be re-used.
     * 
     * @param[in] graphicsFbId                The Frame Id of the buffer to replace the currently displaying buffer
     * 
     * @returns boolean
     * @retval true     The frame was accepted for display.
     * @retval false    The frame was not accepted because the graphics frame id is invalid or unknown to this provider.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid value.
     *
     *
     * @see createGraphicsFb()
     */
    boolean commitGraphicsFb(in int graphicsFbId);
 
    /**
     * Creates a graphics frame buffer for this plane.
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
     * width and height must not exceed the GraphicsFbCapabilities. 
     * 
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid value.
     *
     * 
     * @see destroyGraphicsFb()
     */
    ParcelFileDescriptor createGraphicsFb(in int width, in int height, out GraphicsFbInfo outInfo );

    /**
     * Frees a graphics frame buffer.
     * 
     * @param[in] graphicsFbId    The graphics frame buffer identifier
     * 
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid value.
     * 
     * @see createGraphicsFb()
     */
    void destroyGraphicsFb(in int graphicsFbId);

    /**
     * Gets a native display handle
     * 
     * Used by the compositor with eglGetPlatformDisplay() so EGL display
     * initialisation does not require vendor-specific code paths.
     * 
     * @returns the vendor-specific native display handle for EGL setup.
     * 
     */
    long getNativeDisplayHandle();
    
    /**
     * Gets the EGL Platform Type
     * 
     * The platform type is paired with getNativeDisplayHandle() for eglGetPlatformDisplay().
     *
     * @returns the EGL_PLATFORM_* constant (e.g. EGL_PLATFORM_GBM_KHR or a
     * vendor-defined value) that pairs with getNativeDisplayHandle() for
     * eglGetPlatformDisplay().
     */
    int getEGLPlatformType();
}
