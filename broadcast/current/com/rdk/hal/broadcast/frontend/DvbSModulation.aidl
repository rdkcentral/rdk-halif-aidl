/*
 * If not stated otherwise in this file or this component's LICENSE file the following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 */
package com.rdk.hal.broadcast.frontend;

/**
 * Available modulations.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
@Backing(type = "int")
enum DvbSModulation {
    /** Clean value when default initialized. */
    UNDEFINED = 0,
    /** Auto-selected modulation. */
    AUTO,
    /** QPSK. */
    QPSK,
    /** QAM_16. */
    QAM_16,
    /** PSK_8. */
    PSK_8,
    /** PSK_16. */
    PSK_16,
    /** PSK_32. */
    PSK_32,
    /** APSK_8. */
    APSK_8,
    /** APSK_16. */
    APSK_16,
    /** APSK_32. */
    APSK_32,
    /** APSK_64. */
    APSK_64,
    /** APSK_128. */
    APSK_128,
    /** APSK_256. */
    APSK_256,
    /** ACM. */
    ACM,
}
