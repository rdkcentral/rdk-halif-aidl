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

import com.rdk.hal.cryptoengine.ICryptoEngineController;
import com.rdk.hal.cryptoengine.EngineCapabilities;

/**
 * @brief Crypto Engine HAL Manager interface.
 * @author Gerald Weatherup
 *
 * Top-level entry point for a standalone crypto engine instance.
 * A crypto engine performs cryptographic operations (encrypt, decrypt,
 * hash, sign, verify) independently of any key storage.
 *
 * Engines can be attached to a KeyVault to operate on vault-managed keys,
 * or used standalone with caller-provided key material.
 *
 * The implementation may use hardware crypto acceleration (TEE) or
 * a software fallback, depending on platform capabilities.
 *
 * <h3>Exception Handling</h3>
 * Unless otherwise specified, this interface follows standard Android Binder semantics:
 * - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 * - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *   In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *   The caller must ignore any output variables.
 */
@VintfStability
interface ICryptoEngine {
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "CryptoEngine";

    /**
     * @brief Get the capabilities of this crypto engine.
     *
     * @returns EngineCapabilities describing supported algorithms, modes, and limits.
     */
    EngineCapabilities getCapabilities();

    /**
     * @brief Open a new crypto engine session.
     *
     * Returns a controller for performing crypto operations.
     * Each controller maps to an independent crypto engine instance.
     *
     * @returns ICryptoEngineController for crypto operations, or null on failure.
     * @exception binder::Status EX_ILLEGAL_STATE if max concurrent sessions reached.
     */
    @nullable ICryptoEngineController open();

    /**
     * @brief Close a crypto engine session.
     *
     * All active operations on this controller are aborted and the
     * underlying crypto engine instance is freed.
     *
     * @param controller The controller to close (obtained from open()).
     * @returns true if the session was closed, false if the controller was not recognised.
     */
    boolean close(in ICryptoEngineController controller);
}
