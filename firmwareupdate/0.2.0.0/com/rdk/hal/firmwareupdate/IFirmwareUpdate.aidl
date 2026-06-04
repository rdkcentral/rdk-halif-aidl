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
package com.rdk.hal.firmwareupdate;
import com.rdk.hal.firmwareupdate.IFirmwareUpdateListener;

/**
 *  @brief     Firmware Update HAL interface definition.
 *
 *  The Firmware Update HAL manages the update lifecycle for multiple
 *  classes of firmware that live at various locations across the system
 *  (bootloader regions, application partitions, peripheral firmware blobs,
 *  vendor-specific images). The unifying concept is the update lifecycle,
 *  not the underlying storage medium.
 *
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
interface IFirmwareUpdate
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "firmwareupdate";

    /**
     * Updates a firmware image file onto the device.
     *
     * The image file may contain any firmware type supported by the platform,
     * including (but not limited to): application images, disaster-recovery
     * images, bootloaders, bootloader splash-screen images, and peripheral
     * firmware blobs. The target location for the firmware (boot region,
     * application partition, peripheral device, etc.) is platform-dependent
     * and is determined by examination of the image file contents.
     *
     * The `updateFirmwareFromFile()` function is non-blocking and requests the
     * firmware update operation in background.
     *
     * The progress of the update operation is provided in the
     * `IFirmwareUpdateListener` listener callbacks.
     *
     * Only one background firmware update operation is supported at any time.
     *
     * Image Validation Process:
     *
     * Before the update begins, the image file is validated through the following steps:
     *  - Checked for existence (ERROR_FILE_OPEN_FAIL if not found or cannot be opened).
     *  - Checked to be a valid firmware image file (ERROR_IMAGE_INVALID_TYPE if not recognised).
     *  - Signature verified if present in the image (ERROR_IMAGE_INVALID_SIGNATURE if verification fails).
     *  - Checked to be the correct size for the target firmware area (ERROR_IMAGE_INVALID_SIZE if too large).
     *  - Checked to be targeted at and compatible with the product (ERROR_IMAGE_INVALID_PRODUCT if incompatible).
     *
     * If any pre-update validation fails, the operation is aborted and onCompleted() is called
     * with the appropriate error code. No data is written to the target firmware location in this case.
     *
     * After the image is written, post-update validation is performed:
     *  - The written data is read back from the target firmware area and compared to the source image data
     *    (ERROR_FW_UPDATE_VERIFY_FAILED if data integrity check fails).
     *  - If a signature exists in the image, it is re-verified against the data read back
     *    (ERROR_FW_UPDATE_VERIFY_SIGNATURE_FAILED if post-update signature verification fails).
     *
     * The post-update validation is a critical security step to ensure the integrity of the
     * written image and detect any corruption or tampering during the write process.
     *
     * The background update operation shall run at a priority which does not
     * impact foreground audio, video or graphics operations.
     *
     * Once the background firmware update operation has completed successfully, the new
     * image is flagged as the preferred chosen image when next loaded and run.
     *
     * @param[in] filename      Filename of the image.
     * @param[in] listener      IFirmwareUpdateListener instance for callbacks.
     *
     * @returns boolean
     * @retval true     The firmware update request was started.
     * @retval false    The firmware update request was not started because a firmware update
     *                  operation is already in progress.
     *
     * @see IFirmwareUpdateListener
     */
    boolean updateFirmwareFromFile(in @utf8InCpp String filename, in IFirmwareUpdateListener listener);

}
