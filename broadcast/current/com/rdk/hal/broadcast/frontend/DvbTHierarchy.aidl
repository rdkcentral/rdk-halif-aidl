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

/**
 * Multiple Input Single Output (MISO) modes defined for DVB-T frontend tuning.
 */
@VintfStability
@Backing(type = "int")
enum DvbTHierarchy {
    /** Clean value when default initialized. */
    UNDEFINED = 0,
    /** Automatically detect the hierarchy. */
    AUTO,
    /** Non-hierarchical transmission. */
    NONE,
    /** Hierarchical transmission with alpha 1. */
    ALPHA_1,
    /** Hierarchical transmission with alpha 2. */
    ALPHA_2,
    /** Hierarchical transmission with alpha 4. */
    ALPHA_4,
}
