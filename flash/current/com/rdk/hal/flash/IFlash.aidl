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
import com.rdk.hal.flash.IFlashListener;
 
/** 
 *  @brief     Flash HAL interface definition.
 *  @author    Luc Kennedy-Lamb
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
interface IFlash
{
    /**
     * Flashes a firmware image file onto the device.
     * 
     * The image file could contain an application image, 
     * disaster recovery image, bootloader or bootloader splash screen image.
     * 
     * The types of images that are supported is platform dependent and the
     * type is detected by examination of the file.
     * 
     * The `flashImageFromFile()` function is non-blocking and requests the 
     * flashing of an image file in background.
     * 
     * The progress of the flashing operation is provided in the 
     * `IFlashListener` listener callbacks.
     * 
     * Only one background flashing operation is supported at any time.
     * 
     * The image file is:
     *  - Checked for existence.
     *  - Checked to be a valid flash image file.
     *  - Signature verified.
     *  - Checked to be the correct size for the target flash area.
     *  - Checked to be targeted at and compatible with the product.
     * 
     * The background flashing operation shall run at a priority which does not
     * impact foreground audio, video or graphics operations.
     * 
     * Once the background image flashing operation has completed successfully, the new 
     * image is flagged as the preferred chosen image when next loaded and run.
     * 
     * @param[in] filename      Filename of the image.
     * @param[in] listener      IFlashListener instance for callbacks.
     * 
     * @returns boolean
     * @retval true     The image file flash request was started.
     * @retval false    The image file flash request was not started because a flash
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IFlash}} for exception handling behavior).
     *                  operation is already in progress.
     * 
     * @see IFlashListener
     */
    boolean flashImageFromFile(in @utf8InCpp String filename, in IFlashListener listener);

}
