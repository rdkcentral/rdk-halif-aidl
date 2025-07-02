/*
 * Copyright 2024 RDK Management
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */
package com.rdk.hal.audiomixer;

/**
 * @brief    Audio Mixer properties used in property get/set functions.
 *           All properties can be read in any state unless otherwise noted.
 * @author   Luc Kennedy-Lamb
 * @author   Peter Stieglitz
 * @author   Douglas Adler
 */
@VintfStability
@Backing(type="int")
enum Property {
    /**
     * Current latency of the mixer in milliseconds.
     * 
     * Type: Integer
     * Access: Read-only.
     */
    LATENCY_MS = 0,

    /**
     * Enables or disables debug tap output for audio analysis.
     * 
     * Type: Boolean
     * Access: Read-write.
     * Writeable in states: READY
     */
    DEBUG_TAP_ENABLED = 1,

    /**
     * Gets or sets the currently active AQ (Audio Quality) profile or preset.
     * 
     * Type: String  
     * Access: Read-write  
     * Writable States: READY, STARTED  
     * 
     * The value must correspond to a named AQ parameter configuration supported
     * by the system. These profiles internally control one or more parameters
     * defined in {@see AQParameter}, such as DIALOGUE_ENHANCER, BASS_ENHANCER_GAIN,
     * or GRAPHIC_EQUALIZER.
     *
     * Example values: "DIALOGUE_ENHANCER", "GRAPHIC_EQUALIZER", "SURROUND_VIRTUALIZER"
     *
     * @see com.rdk.hal.audiomixer.AQParameter
     */
    ACTIVE_AQ_PROFILE = 2,
    
    /**
    * Mixer operating mode (e.g., NORMAL, DUCKED).
    *
    * Designed for runtime changes in response to policy or stream priority.
    *
    * Type: MixingMode (Enum) @see com.rdk.hal.audiomixer.MixingModes
    * Access: Read-write.
    * Writable in states: READY, STARTED
    *
    * @see MixingMode
    */
    MIXING_MODE = 3,

    /**
     * Custom vendor-specific property for mixer configuration or debug.
     * 
     * Type: Integer or String (as defined by vendor extension)
     * Access: Read-write.
     * Writeable in states: All
     */
    VENDOR_EXTENSION = 1000,
};
