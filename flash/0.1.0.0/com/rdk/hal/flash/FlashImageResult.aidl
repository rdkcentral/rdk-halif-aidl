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
 
/** 
 *  @brief     Flash image result codes enumeration.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
@Backing(type = "int")
enum FlashImageResult
{
    /**
     * General error result code.
     * Additional details should be provided in the `onCompleted()` `report` string parameter.
     */
    ERROR_GENERAL = -1,

    /**
     * Image was flashed successfully. 
     */
    SUCCESS = 0,

    /**
     * Failed to open input file.
     * The filename is invalid, the file does not exist or cannot be opened for reading.
     */
    ERROR_FILE_OPEN_FAIL = 1,

    /**
     * The image cannot be recognised as a flashable image.
     */
    ERROR_IMAGE_INVALID_TYPE = 2,

    /**
     * The image signature failed verification during pre-flash validation.
     * This error occurs during the initial validation phase before any data is written to flash.
     */
    ERROR_IMAGE_INVALID_SIGNATURE = 3,

    /**
     * Image size does not fit into the target flash area.
     */
    ERROR_IMAGE_INVALID_SIZE = 4,

    /**
     * Image is incompatible with this product.
     */
    ERROR_IMAGE_INVALID_PRODUCT = 5,

    /**
     * Flash write operation failed.
     */
    ERROR_FLASH_WRITE_FAILED = 6,

    /**
     * Flash read-back verify operation failed after writing.
     * This error indicates that data written to flash does not match the source image data
     * when read back for verification. This is a data integrity check performed after the
     * flash write operation completes.
     */
    ERROR_FLASH_VERIFY_FAILED = 7,

    /**
     * Flash image signature failed verification after writing.
     * 
     * This error occurs during the post-flash validation phase and indicates that the
     * signature verification of the image data read back from flash has failed.
     * 
     * Implementation Requirements:
     * - This validation MUST be performed after the flash write operation completes.
     * - The implementation MUST read the written image data back from flash.
     * - If a signature exists in the image, the implementation MUST verify it against
     *   the image data read from flash.
     * - This is a critical security validation step to ensure the integrity of the
     *   flashed image and detect any corruption or tampering that may have occurred
     *   during the write process.
     * - The signature verification algorithm and key management are platform-specific
     *   and should align with the platform's secure boot requirements.
     */
    ERROR_FLASH_VERIFY_SIGNATURE_FAILED = 8,
}
