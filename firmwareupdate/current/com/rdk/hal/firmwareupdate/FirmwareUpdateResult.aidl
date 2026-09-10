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

/**
 *  @brief     Firmware update result codes enumeration.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
@Backing(type = "int")
enum FirmwareUpdateResult
{
    /**
     * General error result code.
     * Additional details should be provided in the `onCompleted()` `report` string parameter.
     */
    ERROR_GENERAL = -1,

    /**
     * Image was updated successfully.
     */
    SUCCESS = 0,

    /**
     * Failed to open input file.
     * The filename is invalid, the file does not exist or cannot be opened for reading.
     */
    ERROR_FILE_OPEN_FAIL = 1,

    /**
     * The image cannot be recognised as a valid firmware image.
     */
    ERROR_IMAGE_INVALID_TYPE = 2,

    /**
     * The image signature failed verification during pre-update validation.
     * This error occurs during the initial validation phase before any data is written.
     */
    ERROR_IMAGE_INVALID_SIGNATURE = 3,

    /**
     * Image size does not fit into the target firmware area.
     */
    ERROR_IMAGE_INVALID_SIZE = 4,

    /**
     * Image is incompatible with this product.
     */
    ERROR_IMAGE_INVALID_PRODUCT = 5,

    /**
     * Firmware write operation failed.
     */
    ERROR_FW_UPDATE_WRITE_FAILED = 6,

    /**
     * Read-back verify operation failed after writing.
     * This error indicates that data written to the target firmware area does not match the source
     * image data when read back for verification. This is a data integrity check performed after the
     * firmware write operation completes.
     */
    ERROR_FW_UPDATE_VERIFY_FAILED = 7,

    /**
     * Firmware image signature failed verification after writing.
     *
     * This error occurs during the post-update validation phase and indicates that the
     * signature verification of the image data read back from the target firmware area has failed.
     *
     * Implementation Requirements:
     * - This validation MUST be performed after the firmware write operation completes.
     * - The implementation MUST read the written image data back from the target firmware area.
     * - If a signature exists in the image, the implementation MUST verify it against
     *   the image data read back.
     * - This is a critical security validation step to ensure the integrity of the
     *   written image and detect any corruption or tampering that may have occurred
     *   during the write process.
     * - The signature verification algorithm and key management are platform-specific
     *   and should align with the platform's secure boot requirements.
     */
    ERROR_FW_UPDATE_VERIFY_SIGNATURE_FAILED = 8,
}
