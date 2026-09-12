/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
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
package com.rdk.hal.cryptoengine;

/**
 * @brief Handle for an in-progress cryptographic operation.
 * @author Gerald Weatherup
 *
 * Returned by ICryptoEngineController.begin().
 * Callers stream data through update() and complete with finish().
 *
 * Each operation maps to a crypto engine instance internally.
 *
 * <h3>Exception Handling</h3>
 * Unless otherwise specified, this interface follows standard Android Binder semantics:
 * - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 * - <b>Failure (Exception)</b>: The method returns a service-specific exception.
 *   In this case, output parameters and return values contain undefined memory and must not be used.
 */
@VintfStability
interface ICryptoOperation {

    /**
     * @brief Feed data into the operation.
     *
     * For encryption/decryption, returns processed output bytes.
     * For signing, returns empty until finish().
     * May be called multiple times for streaming.
     *
     * @param input Data to process.
     * @returns Processed output bytes (may be empty for signing operations).
     * @exception binder::Status EX_ILLEGAL_STATE if the operation has been finalised or aborted.
     */
    byte[] update(in byte[] input);

    /**
     * @brief Complete the operation and return final output.
     *
     * For encryption: returns remaining ciphertext + GCM auth tag (if applicable).
     * For decryption: verifies GCM tag and returns remaining plaintext.
     * For signing: returns the signature.
     * For verification: input is the signature to verify; returns empty on success.
     *
     * After finish(), this operation handle is invalidated.
     *
     * @param input Optional final data to process (may be null).
     * @returns Final output bytes.
     * @exception binder::Status EX_ILLEGAL_STATE if the operation has already been finalised.
     * @exception binder::Status EX_SERVICE_SPECIFIC if GCM tag verification fails during decryption.
     */
    byte[] finish(in @nullable byte[] input);

    /**
     * @brief Abort the operation, releasing all resources.
     *
     * After abort(), this operation handle is invalidated.
     * Calling abort() on an already-finalised operation is a no-op.
     */
    void abort();
}
