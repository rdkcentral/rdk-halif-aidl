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

import com.rdk.hal.keyvault.VaultState;

/**
 * @brief Asynchronous event listener for KeyVault state changes.
 * @author Gerald Weatherup
 *
 * Registered via IKeyVaultController to receive notifications about
 * vault lifecycle events, key expiry, and power state transitions.
 */
@VintfStability
oneway interface IKeyVaultEventListener {

    /**
     * @brief The vault state has changed.
     *
     * Fired on error conditions and initial readiness.
     *
     * @param state The new vault state (READY, ERROR).
     */
    void onVaultStateChanged(in VaultState state);

    /**
     * @brief A key has expired (TTL reached).
     *
     * The key material has been purged from the vault.
     *
     * @param alias The alias of the expired key.
     */
    void onKeyExpired(in @utf8InCpp String alias);

    /**
     * @brief A key has been deleted or otherwise invalidated.
     *
     * @param alias The alias of the key that was removed.
     */
    void onKeyInvalidated(in @utf8InCpp String alias);

    /**
     * @brief A key has been rotated to a new version.
     *
     * @param alias The alias of the rotated key.
     * @param newVersion The new version number.
     */
    void onKeyRotated(in @utf8InCpp String alias, in int newVersion);
}
