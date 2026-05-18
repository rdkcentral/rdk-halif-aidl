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
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "flash";

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
     * Image Validation Process:
     * 
     * Before flashing begins, the image file is validated through the following steps:
     *  - Checked for existence (ERROR_FILE_OPEN_FAIL if not found or cannot be opened).
     *  - Checked to be a valid flash image file (ERROR_IMAGE_INVALID_TYPE if not recognised).
     *  - Signature verified if present in the image (ERROR_IMAGE_INVALID_SIGNATURE if verification fails).
     *  - Checked to be the correct size for the target flash area (ERROR_IMAGE_INVALID_SIZE if too large).
     *  - Checked to be targeted at and compatible with the product (ERROR_IMAGE_INVALID_PRODUCT if incompatible).
     * 
     * If any pre-flash validation fails, the operation is aborted and onCompleted() is called
     * with the appropriate error code. No data is written to flash in this case.
     * 
     * After the image is written to flash, post-flash validation is performed:
     *  - The written data is read back from flash and compared to the source image data
     *    (ERROR_FLASH_VERIFY_FAILED if data integrity check fails).
     *  - If a signature exists in the image, it is re-verified against the data read from flash
     *    (ERROR_FLASH_VERIFY_SIGNATURE_FAILED if post-flash signature verification fails).
     * 
     * The post-flash validation is a critical security step to ensure the integrity of the
     * flashed image and detect any corruption or tampering during the write process.
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
     *                  operation is already in progress.
     * 
     * @see IFlashListener
     */
    boolean flashImageFromFile(in @utf8InCpp String filename, in IFlashListener listener);

}
