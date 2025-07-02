/*
 * Copyright 2024 RDK Management
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */
package com.rdk.hal.audiomixer;

import com.rdk.hal.audiomixer.OutputPortProperty;

/**
 * @brief     Listener interface for audio output port events.
 * @details   Provides callbacks for changes in port connection state, supported formats,
 *            output format changes, state transitions, and feature support (e.g., Dolby Atmos).
 *            Registered by clients interested in monitoring real-time output port events.
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @copyright Copyright 2024 RDK Management
 */
@VintfStability
oneway interface IAudioOutputPortListener {

    /**
     * @brief     Called when a dynamic property value changes.
     * @param[in] property   The OutputPortProperty that changed.
     * @param[in] newValue   The new PropertyValue.
     */
    void onPropertyChanged(in OutputPortProperty property, in PropertyValue newValue);
}
