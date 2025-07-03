/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
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
package com.rdk.hal.deviceinfo;

/**
 * @brief DeviceInfo property keys used in getProperty() and setProperty().
 *        These are symbolic names for well-known device information attributes.
 * 
 * Each property is mapped to a persistent or platform-specific value.
 * Not all properties may support write access.
 * 
 * @author Luc Kennedy-Lamb
 * @author Peter Stieglitz
 * @author Douglas Adler
 */
@VintfStability
@Backing(type = "int")
enum Property {
    /**
     * Device manufacturer name.
     * Type: ASCII string.
     * Access: Read-only.
     */
    MANUFACTURER = 0,

    /**
     * Manufacturer IEEE OUI (Organizationally Unique Identifier).
     * Format: Hex string (3 bytes, uppercase).
     * Access: Read-only.
     */
    MANUFACTURER_OUI = 1,

    /**
     * Device model name.
     * Type: ASCII string.
     * Access: Read-only.
     */
    MODELNAME = 2,

    /**
     * Product class identifier.
     * Type: ASCII string.
     * Access: Read-only.
     */
    PRODUCTCLASS = 3,

    /**
     * Serial number of the device.
     * Type: ASCII string.
     * Access: Read-only.
     */
    SERIALNUMBER = 4,

    /**
     * Wi-Fi MAC address.
     * Format: XX:XX:XX:XX:XX:XX
     * Access: Read-only.
     */
    WIFIMAC = 5,

    /**
     * Bluetooth MAC address.
     * Format: XX:XX:XX:XX:XX:XX
     * Access: Read-only.
     */
    BLUETOOTHMAC = 6,

    /**
     * WPS PIN (8-digit string).
     * Type: ASCII string.
     * Access: Read-write.
     */
    WPSPIN = 7,

    /**
     * Ethernet MAC address.
     * Format: XX:XX:XX:XX:XX:XX
     * Access: Read-only.
     */
    ETHERNETMAC = 8,

    /**
     * RF4CE MAC address.
     * Format: XX:XX:XX:XX:XX:XX
     * Access: Read-only.
     */
    RF4CEMAC = 9,

    /**
     * Application image name.
     * Type: ASCII string.
     * Access: Read-only.
     */
    IMAGENAME = 10,

    /**
     * Application image type.
     * Type: ASCII string.
     * Access: Read-only.
     */
    IMAGETYPE = 11,

    /**
     * Country code (e.g., "US", "GB").
     * Type: ASCII string.
     * Access: Read-write.
     */
    COUNTRYCODE = 12,

    /**
     * Language code (e.g., "en", "fr").
     * Type: ASCII string.
     * Access: Read-write.
     */
    LANGUAGECODE = 13,

    /**
     * Manufacturer data blob (opaque string).
     * Type: ASCII string.
     * Access: Read-write.
     */
    MANUFACTURERDATA = 14
}
