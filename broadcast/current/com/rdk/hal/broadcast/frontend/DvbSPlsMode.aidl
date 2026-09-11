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
enum DvbSPlsMode {
    UNDEFINED = 0,
    /** Auto-selected. */
    AUTO,
    /** DVB-S2/S2X root physical-layer scrambling sequence. */
    ROOT,
    /** DVB-S2/S2X gold physical-layer scrambling sequence. */
    GOLD,
    /** DVB-S2/S2X combined physical-layer scrambling sequence. */
    COMBO,
}
