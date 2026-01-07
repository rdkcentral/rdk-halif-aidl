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
package com.rdk.hal.indicator;

@VintfStability
@Backing(type="int")
/**
 * @brief Indicator states.
 *
 * Represents the persistent, mutually exclusive states that the system indicator can be in.
 * These states reflect the current condition of the device (e.g., booting, active, error)
 * and remain in effect until explicitly changed. The HAL implementation is expected to
 * reflect these states via hardware-controlled visual indicators (e.g., LEDs, panels),
 * allowing upper layers to signal meaningful system conditions to the end user without
 * depending on the underlying hardware or product-specific display logic.
 *
 * This abstraction decouples UI-level logic from platform-specific LED or panel control,
 * enabling consistent behaviour across diverse hardware implementations. Middleware and
 * client applications interact only with defined states—they are not aware of (nor should
 * they assume) how these states are physically rendered.
 *
 * ### Key Characteristics:
 * - Each state describes a long-lived, persistent condition.
 * - Only one state should be active at any time; transitions are explicit and deterministic.
 * - These states map to end-user-visible modes (e.g., "device is booting", "WPS active").
 * - Transient events (e.g., "blink on RCU press") are **not** indicator states. Such momentary
 *   visual effects must be implemented entirely within the vendor's HAL logic and are never
 *   reported or managed through this enum.
 * - States such as `ERROR_UNKNOWN` and `BOOT` are informational and **not settable** by clients.
 *   `BOOT` is the **initial system state**, typically assigned during startup, and is expected
 *   to be handled internally by the platform (e.g., by the bootloader or HAL startup logic).
 *
 * ### Platform-Specific Extensions:
 * Vendors may define additional persistent states by extending this enum starting from
 * `USER_DEFINED_BASE = 1000`. These must follow the same semantics—i.e., they must be persistent,
 * mutually exclusive system states. They must be declared in the platform's HAL Feature Profile (HFP)
 * YAML to enable middleware discovery, capability validation, and automated test coverage.
 *
 * These vendor-specific states may reflect custom product features (e.g., voice mode active,
 * device in setup mode, or special branding states) and must be clearly documented with
 * associated visual behaviour.
 *
 * ### Runtime and Capability Expectations:
 * The supported set of states returned by `getCapabilities()` must align with the platform's
 * `hfp-indicator.yaml`. States not declared there must be rejected by the HAL if clients
 * attempt to set them. This guarantees runtime compatibility and prevents feature misuse.
 *
 * @author Luc Kennedy-Lamb
 * @author Peter Stieglitz
 * @author Douglas Adler
 * @author Gerald Weatherup
 */
enum State
{
    // General and boot-related states
    ERROR_UNKNOWN = -1, 	/**< The current state cannot be determined. This state cannot be set by clients. */
    BOOT = 0, 			/**< Initial bootloader-defined state. Read-only and set internally at HAL startup. */
    ACTIVE = 1,			/**< System is fully operational. */
    STANDBY = 2, 		/**< Low-power idle state. Device remains partially responsive. */
    OFF = 3, 			/**< All indicators are off. Used for deep standby or energy-saving modes. */
    DEEP_SLEEP = 4, 		/**< Deep sleep mode with minimal system activity. */

    // WPS-related states
    WPS_CONNECTING = 100, 	/**< Wi-Fi Protected Setup is currently active. */
    WPS_CONNECTED = 101, 	/**< WPS connection successfully completed. */
    WPS_ERROR = 102, 		/**< WPS session failed (e.g., timeout, authentication error). */
    WPS_SES_OVERLAP = 103,	/**< Multiple WPS sessions detected; requires user intervention. */

    // Network states
    WIFI_ERROR = 200, 		/**< Wi-Fi hardware or configuration fault. */
    IP_ACQUIRED = 201, 		/**< IP address successfully assigned. */
    NO_IP = 202, 		/**< IP assignment failed; no address obtained. */

    // System operations
    FULL_SYSTEM_RESET = 300, 		/**< Factory reset or system restore in progress. */
    USB_UPGRADE = 301, 			/**< Firmware upgrade in progress via USB. */
    SOFTWARE_DOWNLOAD_ERROR = 302, 	/**< Software update failed during download or installation. */
    PSU_FAILURE = 303, 			/**< Power supply fault detected. */

    /**
     * Reserved base for vendor-defined persistent states.
     * Custom states must follow the same semantics: they must be persistent,
     * mutually exclusive, and platform-documented in the HAL Feature Profile.
     */
    USER_DEFINED_BASE = 1000
}
