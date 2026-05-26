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

import com.rdk.hal.cryptoengine.Algorithm;
import com.rdk.hal.cryptoengine.CryptoConfig;
import com.rdk.hal.cryptoengine.Digest;
import com.rdk.hal.cryptoengine.ICryptoEngineController;
import com.rdk.hal.cryptoengine.KeyType;
import com.rdk.hal.keyvault.DerivedKeySpec;
import com.rdk.hal.keyvault.IKeyVaultEventListener;
import com.rdk.hal.keyvault.KeyDescriptor;
import com.rdk.hal.keyvault.VaultCapabilities;
import com.rdk.hal.keyvault.VaultState;

/**
 * @brief Per-session controller for a KeyVault instance.
 * @author Gerald Weatherup
 *
 * Obtained via IKeyVault.open(). Provides key storage, lifecycle,
 * and access control scoped to a single vault instance.
 *
 * The vault is purely a key store — it holds key material, manages
 * key metadata, and controls access. To perform crypto operations on
 * vault-managed keys, attach a configured ICryptoEngineController to
 * this vault. The engine then uses the vault's keys for its operations
 * based on its own crypto configuration.
 *
 * <h3>Exception Handling</h3>
 * Unless otherwise specified, this interface follows standard Android Binder semantics:
 * - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 * - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *   In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 */
@VintfStability
interface IKeyVaultController {

    // -------------------------------------------------------------------------
    // Crypto engine attachment
    // -------------------------------------------------------------------------

    /**
     * @brief Attach a configured crypto engine to this vault.
     *
     * Once attached, the engine can operate on this vault's keys.
     * The engine's crypto configuration (algorithm, mode, etc.) determines
     * how the vault's keys are used — the vault itself has no opinion on
     * crypto operations.
     *
     * @param engine A configured ICryptoEngineController to attach.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if engine is null.
     * @exception binder::Status EX_ILLEGAL_STATE if an engine is already attached.
     */
    void attachCryptoEngine(in ICryptoEngineController engine);

    /**
     * @brief Detach the currently attached crypto engine.
     *
     * Any in-flight operations using vault keys are aborted.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if no engine is attached.
     */
    void detachCryptoEngine();

    // -------------------------------------------------------------------------
    // Vault introspection
    // -------------------------------------------------------------------------

    /**
     * @brief Get the capabilities of this vault instance.
     *
     * @returns VaultCapabilities describing key limits, security level,
     *          and persistence behaviour.
     */
    VaultCapabilities getCapabilities();

    /**
     * @brief Get the current state of this vault.
     *
     * Callers should check state after open() before attempting key operations.
     *
     * @returns VaultState (READY, ERROR).
     */
    VaultState getVaultState();

    // -------------------------------------------------------------------------
    // Key lifecycle
    // -------------------------------------------------------------------------

    /**
     * @brief Generate a new symmetric key within this vault.
     *
     * The key material is created inside the secure environment and never
     * leaves it. Algorithm and usages are bound to the key at creation
     * time and enforced on all subsequent operations.
     *
     * @param alias Unique name for the key within this vault.
     * @param algorithm Algorithm for this key (AES, HMAC).
     * @param keySizeBits Key size in bits (e.g. 128, 256).
     * @param usages Allowed usages as a bitmask of KeyPurpose values.
     * @param extractable Whether the raw key material can be exported.
     * @returns KeyDescriptor for the newly created key.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if alias already exists, algorithm/size is invalid, or usages are incompatible with algorithm.
     * @exception binder::Status EX_SERVICE_SPECIFIC if the vault has reached its key limit.
     */
    KeyDescriptor generateKey(in @utf8InCpp String alias, in Algorithm algorithm, in int keySizeBits, in int usages, in boolean extractable);

    /**
     * @brief Generate an asymmetric keypair within this vault.
     *
     * Both the public and private key are stored in the vault under
     * separate aliases. Only key descriptors are returned from this call;
     * callers must use exportKey(publicAlias) to obtain raw public key bytes.
     *
     * @param publicAlias Alias for the public key in the vault.
     * @param privateAlias Alias for the private key in the vault.
     * @param algorithm Algorithm for this keypair (EC, RSA, DH).
     * @param keySizeBits Key size in bits.
     * @param usages Allowed usages for the private key as a bitmask of KeyPurpose values.
     * @param extractable Whether the private key material can be exported.
     * @returns KeyDescriptor[] — two descriptors: [0] = public, [1] = private.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if aliases already exist or params are invalid.
     * @exception binder::Status EX_SERVICE_SPECIFIC if the vault has reached its key limit.
     */
    KeyDescriptor[] generateKeyPair(in @utf8InCpp String publicAlias, in @utf8InCpp String privateAlias, in Algorithm algorithm, in int keySizeBits, in int usages, in boolean extractable);

    /**
     * @brief Import raw key material into this vault.
     *
     * The key data is encrypted at rest using the vault's root-derived key
     * and persisted. Algorithm and usages are bound at import time.
     *
     * @param alias Unique name for the key within this vault.
     * @param algorithm Algorithm for this key.
     * @param keyType Key type (SECRET, PUBLIC, or PRIVATE).
     * @param keyData Raw key material to import.
     * @param usages Allowed usages as a bitmask of KeyPurpose values.
     * @param extractable Whether the raw key material can be exported later.
     * @returns KeyDescriptor for the imported key.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if alias already exists, keyData is empty, or params are invalid.
     */
    KeyDescriptor importKey(in @utf8InCpp String alias, in Algorithm algorithm, in KeyType keyType, in byte[] keyData, in int usages, in boolean extractable);

    /**
     * @brief Export raw key material from the vault.
     *
     * Only permitted for keys created with extractable = true.
     *
     * @param alias The alias of the key to export.
     * @returns Raw key material bytes.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if alias does not exist.
     * @exception binder::Status EX_SECURITY if the key is not extractable.
     */
    byte[] exportKey(in @utf8InCpp String alias);

    /**
     * @brief Delete a key from this vault.
     *
     * The key material is securely erased and the keystore is re-persisted.
     *
     * @param alias The alias of the key to delete.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if alias does not exist.
     */
    void deleteKey(in @utf8InCpp String alias);

    /**
     * @brief Delete all keys from this vault.
     *
     * @post The vault is empty. All key material is securely erased.
     */
    void deleteAllKeys();

    /**
     * @brief Rotate a key, creating a new version under the same alias.
     *
     * The previous version is retained for decryption of existing data.
     * New encrypt operations use the latest version. The key version
     * counter in the KeyDescriptor is incremented.
     *
     * @param alias The alias of the key to rotate.
     * @returns Updated KeyDescriptor with the new version number.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if alias does not exist.
     */
    KeyDescriptor rotateKey(in @utf8InCpp String alias);

    /**
     * @brief List all keys in this vault.
     *
     * @returns Array of KeyDescriptor for every key in the vault.
     */
    KeyDescriptor[] listKeys();

    /**
     * @brief Get the descriptor for a specific key by alias.
     *
     * @param alias The alias of the key to look up.
     * @returns KeyDescriptor, or null if not found.
     */
    @nullable KeyDescriptor getKeyInfo(in @utf8InCpp String alias);

    // -------------------------------------------------------------------------
    // Key derivation into vault
    // -------------------------------------------------------------------------

    /**
     * @brief Derive one or more keys and store them directly in this vault.
     *
     * Performs key derivation using the attached crypto engine and stores
     * the resulting key(s) in the vault without exposing raw material.
     * Each output key is described by a DerivedKeySpec (alias, algorithm,
     * type, size, usages).
     *
     * Supports all derivation functions: HKDF, PBKDF2, DH, NFLX-DH.
     * For NFLX-DH, three output specs are expected (encryption, hmac, wrapping).
     * For HKDF/PBKDF2, typically one output spec.
     *
     * The source key for derivation must already exist in this vault
     * (referenced by the sourceKeyAlias parameter) and have DERIVE_KEY usage.
     *
     * @param config Crypto configuration for the derivation (kdf, digest, salt, info, etc.).
     *               config.keyData is ignored — the source key is taken from the vault via sourceKeyAlias.
     * @param sourceKeyAlias Alias of the source key in this vault.
     * @param peerPublicKey Peer's public key for DH/NFLX-DH. Null for HKDF/PBKDF2.
     * @param outputKeys Specifications for each derived key to store.
     * @returns KeyDescriptor[] for each derived key, in the same order as outputKeys.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if sourceKeyAlias doesn't exist, config is invalid, or output specs are invalid.
     * @exception binder::Status EX_SECURITY if the source key doesn't have DERIVE_KEY usage.
     * @exception binder::Status EX_ILLEGAL_STATE if no crypto engine is attached.
     */
    KeyDescriptor[] deriveIntoVault(in CryptoConfig config, in @utf8InCpp String sourceKeyAlias, in @nullable byte[] peerPublicKey, in DerivedKeySpec[] outputKeys);

    // -------------------------------------------------------------------------
    // Flush / persistence
    // -------------------------------------------------------------------------

    /**
     * @brief Flush any pending changes to persistent storage.
     *
     * Ensures all key additions, deletions, and metadata changes are
     * written to the underlying keystore partition and re-authenticated
     * (e.g. HMAC re-signed).
     *
     * @exception binder::Status EX_SERVICE_SPECIFIC if the write fails.
     */
    void flush();

    // -------------------------------------------------------------------------
    // Event listeners
    // -------------------------------------------------------------------------

    /**
     * @brief Register for vault lifecycle events.
     *
     * @param listener The event listener to register.
     * @post listener receives onVaultStateChanged, onKeyExpired, onKeyInvalidated, and onKeyRotated callbacks.
     */
    void registerEventListener(in IKeyVaultEventListener listener);

    /**
     * @brief Unregister a previously registered event listener.
     *
     * @param listener The event listener to unregister.
     */
    void unregisterEventListener(in IKeyVaultEventListener listener);
}
