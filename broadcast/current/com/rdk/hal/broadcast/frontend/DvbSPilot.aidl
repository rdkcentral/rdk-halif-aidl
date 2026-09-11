/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 */
package com.rdk.hal.broadcast.frontend;

@VintfStability
@Backing(type = "int")
enum DvbSPilot {
    UNDEFINED = 0,
    /** DVB-S2/S2X pilot symbols are auto-detected. */
    AUTO,
    /** DVB-S2/S2X pilot symbols are present. */
    ON,
    /** DVB-S2/S2X pilot symbols are absent. */
    OFF,
}
