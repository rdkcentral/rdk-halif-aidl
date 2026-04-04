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
package com.rdk.hal.keyvault;

import com.rdk.hal.keyvault.IKeyVaultController;
import com.rdk.hal.keyvault.IKeyVaultEventListener;
import com.rdk.hal.cryptoengine.SecurityLevel;

/**
 * @brief KeyVault HAL Manager interface.
 * @author Gerald Weatherup
 *
 * Top-level entry point for the KeyVault HAL. Provides discovery of
 * available vault instances and factory methods to open vault sessions.
 *
 * A KeyVault is a logical keystore (key namespace) with its own key
 * material, access rules, and persistence policy. Multiple vaults can
 * coexist for different requirements (e.g. app secure storage, platform
 * identity, session keys, DRM provisioning).
 *
 * Key material is encrypted at rest by OTP-derived root keys. To perform
 * crypto operations on vault-managed keys, callers attach an
 * ICryptoEngineController to the vault session.
 *
 * <h3>Exception Handling</h3>
 * Unless otherwise specified, this interface follows standard Android Binder semantics:
 * - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 * - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *   In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *   The caller must ignore any output variables.
 */
@VintfStability
interface IKeyVault {
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "KeyVault";

    /**
     * @brief Get the list of available vault names.
     *
     * Vault names are defined by platform configuration and may include
     * pre-provisioned vaults (e.g. "platform-identity") and runtime-created
     * vaults (e.g. per-app vaults).
     *
     * @returns Array of vault name strings.
     */
    @utf8InCpp String[] getVaultNames();

    /**
     * @brief Get the security level of a named vault.
     *
     * @param vaultName The name of the vault to query.
     * @returns SecurityLevel of the vault (SOFTWARE or TEE).
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if vaultName is not recognised.
     */
    SecurityLevel getSecurityLevel(in @utf8InCpp String vaultName);

    /**
     * @brief Open a session to a named vault.
     *
     * Returns a controller interface for key management and crypto operations
     * within the specified vault. The controller remains valid until close()
     * is called or the device enters deep sleep (for TEE-backed vaults).
     *
     * @param vaultName The name of the vault to open.
     * @param listener Event listener for vault lifecycle events. May be null.
     * @returns IKeyVaultController for the opened vault session, or null on failure.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if vaultName is not recognised.
     * @exception binder::Status EX_ILLEGAL_STATE if the vault is already at max sessions.
     */
    @nullable IKeyVaultController open(in @utf8InCpp String vaultName, in @nullable IKeyVaultEventListener listener);

    /**
     * @brief Close a vault session.
     *
     * All active operations on this controller are aborted. Key material
     * remains persisted in the vault's partition.
     *
     * @param controller The controller to close (obtained from open()).
     * @returns true if the session was closed, false if the controller was not recognised.
     */
    boolean close(in IKeyVaultController controller);

    // -------------------------------------------------------------------------
    // Application-created vaults
    // -------------------------------------------------------------------------

    /**
     * @brief Create a new vault at runtime.
     *
     * Applications may create additional vaults beyond the platform-provisioned
     * ones, subject to the limits defined in the HFP (allowApplicationVaults,
     * maxApplicationVaults).
     *
     * @param vaultName Unique name for the new vault.
     * @param securityLevel Requested security level (SOFTWARE or TEE).
     * @param maxKeys Maximum number of keys this vault can hold.
     * @returns true if the vault was created successfully.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if vaultName already exists.
     * @exception binder::Status EX_ILLEGAL_STATE if max application vaults reached.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if application vault creation is not permitted.
     */
    boolean createVault(in @utf8InCpp String vaultName, in SecurityLevel securityLevel, in int maxKeys);

    /**
     * @brief Destroy a runtime-created vault and all its keys.
     *
     * Only application-created vaults can be destroyed. Platform-provisioned
     * vaults cannot be removed.
     *
     * @param vaultName The name of the vault to destroy.
     * @returns true if the vault was destroyed.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if vaultName does not exist or is platform-provisioned.
     */
    boolean destroyVault(in @utf8InCpp String vaultName);
}
