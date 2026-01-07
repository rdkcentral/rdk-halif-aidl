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
package com.rdk.hal.avclock;
 
/**
 * @brief Represents a snapshot of the AV System Time Clock (STC) along with its associated Linux system timestamp.
 *
 * In AV systems multiple clocks exist that may run at different rates.
 * The System Time Clock (STC) is used to regulate AV playback, ensuring both Audio and Video stay in sync.
 * On some platforms the Audio clock *is* the STC, and it may not match the Linux wall clock.
 *
 * This structure allows consumers to retrieve the current STC value and know when (in system time) that value was sampled.
 * This is essential for tasks such as subtitle scheduling or time-domain synchronization.
 *
 * Common use-case: Subtitle rendering
 *
 * Subtitle timestamps (PTS) are expressed in the STC domain. To render a subtitle at the right moment,
 * we need to convert that STC time to Linux wall clock time using:
 *
 * @code
 * SubtitleWallClockTime = SubtitlePTS - clockTimeNs + sampleTimestampNs
 * @endcode
 *
 * This method gives a close approximation suitable for short durations. Over long durations, drift may occur.
 *
 * Note on virtual devices:
 * On virtual platforms (e.g., QEMU), the STC and the system clock may initially progress at the same rate.
 * Thus, clockTimeNs may be equal to sampleTimestampNs. This will change if proper broadcast clock recovery is introduced.
 *
 * @see https://linux.die.net/man/2/clock_gettime for CLOCK_MONOTONIC_RAW behavior.
 *
 * @author Luc Kennedy-Lamb
 * @author Peter Stieglitz
 * @author Douglas Adler
 * @author Gerald Weatherup
 */
@VintfStability
parcelable ClockTime 
{

    /**
     * The current STC (System Time Clock) value in nanoseconds.
     * This clock governs AV playback timing and may differ in rate from system wall clock time.
     */
    long clockTimeNs;

    /**
     * The Linux CLOCK_MONOTONIC_RAW nanosecond timestamp when the STC value was sampled.
     * This allows consumers to relate AV time (STC) to system time.
     */
    long sampleTimestampNs;
}
