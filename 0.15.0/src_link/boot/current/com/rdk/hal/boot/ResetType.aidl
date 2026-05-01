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
package com.rdk.hal.boot;
 
/** 
 *  @brief     Reset types.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability 
@Backing(type = "int")
enum ResetType {

    /** 
     * Upon restart, the system shall come up and delete all persistent data partitions and recreate them.
     * BootReason will be reported as WARM_RESET
     */
    FULL_SYSTEM_RESET = 0,

    /** 
     * Upon restart, the current application image is invalidated and shall NOT be selected for loading
     * on the next boot. If the platform supports multiple application image banks then the alternate
     * bank should be selected; otherwise the Disaster Recovery Image (DRI) will be loaded.
     * BootReason will be reported as WARM_RESET
     * @note After the next boot, the running image cannot determine from BootReason alone that this
     *       reset type caused the transition. The exact boot-selection behaviour is platform-dependent.
     * @note The precise semantics and sequencing of this reset type are under review. A sequence
     *       diagram documenting entry, exit and observable state should be provided.
     */
    INVALIDATE_CURRENT_APPLICATION_IMAGE = 1,

    /** 
     * Upon restart, the system shall enter disaster recovery mode by loading the
     * Disaster Recovery Image (DRI).
     * BootReason will be reported as WARM_RESET
     * @note From a Primary/Current Image (PCI) perspective there is no visibility that the system
     *       entered disaster recovery mode. Only the DRI itself knows it was force-loaded. After the
     *       DRI completes recovery and the system returns to normal operation, the BootReason will not
     *       reflect that a forced disaster recovery occurred.
     * @note This reset type may not be supported on all platforms (e.g. platforms without a dedicated
     *       disaster recovery image). Clients **MUST** verify platform support by checking
     *       Capabilities.supportedResetTypes before requesting this reset type.
     * @note The precise semantics, sequencing and terminology for this reset type are under review.
     *       A sequence diagram documenting how the system enters, executes and exits disaster recovery
     *       mode should be provided.
     */
    FORCE_DISASTER_RECOVERY = 2,

    /**
     * Performing Reboot for a Maintenance reason. The caller **MUST** set the reasonString
     * BootReason will be reported as MAINTENANCE_REBOOT
     */
    MAINTENANCE_REBOOT = 3,

    /**
     * Performing Reboot for a Software reason (which is specifically not a Maintenance Reboot). The caller **MUST** set the reasonString
     * BootReason will be reported as WARM_RESET, unless overridden by setBootReason prior to reboot.
     */
    SOFTWARE_REBOOT = 4,
}
