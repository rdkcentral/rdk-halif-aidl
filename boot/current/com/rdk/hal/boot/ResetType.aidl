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
     * Upon restart, the current application image is invalidated and will be selected for loading on the next boot.
     * If the platform supports multiple application image banks then the other bank should be selected.
     * BootReason will be reported as WARM_RESET
     */
    INVALIDATE_CURRENT_APPLICATION_IMAGE = 1,

    /** 
     * Upon restart, the system shall enter disaster recovery mode.
     * BootReason will be reported as WARM_RESET
     */
    FORCE_DISASTER_RECOVERY = 2,

    /**
     * Performing Reboot for a Maintenance reason, caller should also set the reasonString
     * BootReason will be reported as MAINTENANCE_REBOOT
     */
    MAINTENANCE_REBOOT = 3,

    /**
     * Performing Reboot for a Software reason (which is specifically not a Maintenance Reboot), caller should also set the reasonString
     * BootReason will be reported as WARM_RESET, unless overridden by setBootReason prior to reboot.
     */
    SOFTWARE_REBOOT = 4,
}
