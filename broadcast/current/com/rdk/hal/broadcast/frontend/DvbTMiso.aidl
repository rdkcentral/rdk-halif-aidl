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
 * Hierarchical transmission modes defined for DVB-T tuning.
 */
@VintfStability
@Backing(type = "int")
enum DvbTMiso {
    /** Clean value when default initialized. */
    UNDEFINED = 0,
    /** Let the receiver determine the mode. */
    AUTO,
    /** Single Input Single Output. */
    SISO,
    /** Multiple Input Single Output. */
    MISO,
}
