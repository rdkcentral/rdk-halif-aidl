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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.audiomixer;

import com.rdk.hal.audiomixer.InputRouting;
import com.rdk.hal.audiomixer.Property;
import com.rdk.hal.audiosink.VolumeRamp;
import com.rdk.hal.PropertyValue;

/**
 * @brief     Audio Mixer Controller HAL interface.
 * @details   Provides stateful and runtime control over a specific platform audio mixer resource.
 *            This includes lifecycle management (start/stop), flushing, signalling end-of-stream,
 *            routing configuration, and property configuration. Intended for use by the
 *            middleware audio server and platform integrators.
 *
 *            <h3>Mix policy and clipping</h3>
 *            The mixer guarantees the output signal will not clip. When the sum of active
 *            input contributions (per-input volume × input signal level) would exceed full
 *            scale, the HAL applies headroom management — typically a soft limiter on the
 *            master mix bus or master attenuation. The exact mechanism is a vendor
 *            implementation detail; what is guaranteed is that the output stays within
 *            full scale.
 *
 *            Per-input volumes set via setInputVolume() / setInputVolumeRamp() are the
 *            subjective gains the application requests. The HAL handles the math to keep
 *            the output safe. Applications do not need to compute their own normalisation
 *            budget.
 *
 *            For predictable mixes during overlapping audio events (e.g. system sound
 *            over main programme), applications should explicitly duck the main input via
 *            setInputVolumeRamp() rather than relying on the limiter — see the audio_mixer
 *            documentation "Use case 2 — Ducking a system sound over main audio".
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 */
@VintfStability
interface IAudioMixerController {

    /**
     * @brief     Sets the audio source routing for one or more inputs on this mixer instance.
     * @details   Allows multiple audio [source -> mixer input] mappings to be configured.
     *            This enables operations such as switching between decoders, routing
     *            HDMI input audio, or connecting application audio to mixer inputs.
     *
     *            The target mixer input is defined by the array position:
     *            - routing[0] configures mixer input 0
     *            - routing[1] configures mixer input 1
     *            - etc.
     *
     *            Each InputRouting element specifies sourceType/sourceIndex for that input.
     *
     *            To disconnect a source from a mixer input, set `sourceType` to `AudioSourceType.NONE`.
     *
     *            Validation:
     *            - If a source type and source index appear multiple times in the routing array, the call fails.
     *            - If a mixer input is already mapped to a different source, returns false.
     *
     * @param[in] routing   Array of audio source to mixer input routing configurations.
     * @returns   Success status.
     * @retval true     All routing mappings were successfully applied.
     * @retval false    One or more routing configurations were invalid or conflicted.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if routing array contains invalid values.
     * @exception binder::Status EX_ILLEGAL_STATE if mixer is in a state that prevents routing changes.
     * @see       IAudioMixer.getInputRouting()
     */
    boolean setInputRouting(in InputRouting[] routing);

    /**
     * @brief     Sets a property on the controlled mixer instance.
     * @param[in] property      The property key (from Property enum).
     * @param[in] propertyValue The value to set (PropertyValue union).
     * @returns   true if successfully set, false otherwise.
     * @see       IAudioMixer.getProperty()
     */
    boolean setProperty(in Property property, in PropertyValue propertyValue);

    /**
     * @brief     Starts audio mixing for this mixer instance.
     * @details   The mixer transitions to the STARTED state and processes configured audio inputs and outputs.
     * @exception binder::Status EX_ILLEGAL_STATE if already started or not ready.
     * @pre       The mixer must be in READY state.
     * @see       stop(), flush()
     */
    void start();

    /**
     * @brief     Stops audio mixing for this mixer instance.
     * @details   The mixer transitions through STOPPING to READY state, ceasing output and freeing any buffered resources.
     * @exception binder::Status EX_ILLEGAL_STATE if not started.
     * @pre       The mixer must be in STARTED state.
     * @see       start(), flush()
     */
    void stop();

    /**
     * @brief     Flushes the mixer, discarding all buffered audio data.
     * @param[in] reset   When true, resets internal state to READY; when false, retains configuration but flushes data.
     * @exception binder::Status EX_ILLEGAL_STATE if not started.
     * @pre       The mixer must be in STARTED state.
     */
    void flush(in boolean reset);

    /**
     * @brief     Signals a stream discontinuity in the mixer pipeline.
     * @details   Used when a break or change in input PTS or format occurs, such as switching sources or seeking.
     * @exception binder::Status EX_ILLEGAL_STATE if not started.
     * @pre       The mixer must be in STARTED state.
     */
    void signalDiscontinuity();

    /**
     * @brief     Signals end-of-stream for all active mixer inputs.
     * @details   After all buffered frames are processed, the mixer drains remaining data
     *            and transitions through STOPPING to READY state.
     * @exception binder::Status EX_ILLEGAL_STATE if not started.
     * @pre       The mixer must be in STARTED state.
     */
    void signalEOS();

    /**
     * @brief     Sets the volume (attenuation) for a specific mixer input.
     * @details   Per-input attenuation lets clients balance multiple sources
     *            mixed into the same output (e.g., reduce main programme volume
     *            while a system sound plays). Value range is 0..100 where 100
     *            is unity gain (no attenuation) and 0 is silence.
     *
     *            Independent of the mixer-level FADER_LEVEL property which
     *            controls main/associated audio balance, and the output port
     *            VOLUME property which controls overall output volume.
     *
     *            <b>Mute behaviour:</b> setting volume to 0 removes that input's
     *            contribution from the mix budget. Remaining active inputs
     *            retain their requested levels (no auto-scale-up). Restoring
     *            the volume re-introduces the input at the new level.
     *
     *            <b>Mix policy:</b> the mixer prevents output clipping — see
     *            the interface header "Mix policy and clipping" notes. High
     *            per-input volumes across multiple active inputs will not
     *            cause output clipping; the HAL applies headroom management.
     *
     *            <b>Instant change:</b> this call applies the new volume
     *            immediately. For changes during active playback, prefer
     *            setInputVolumeRamp() to avoid audible clicks (zipper noise).
     *
     * @param[in] inputIndex  Mixer input index (0..Capabilities.inputs.length-1).
     * @param[in] volume      Volume level 0..100.
     *
     * @returns   true on success, false if the input is unsupported on this
     *            mixer (e.g. input is unrouted / has no source). Out-of-range
     *            inputIndex or volume values throw EX_ILLEGAL_ARGUMENT.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if inputIndex is outside
     *            [0, Capabilities.inputs.length-1] or volume is outside [0, 100].
     *
     * @see       getInputVolume(), setInputVolumeRamp()
     */
    boolean setInputVolume(in int inputIndex, in int volume);

    /**
     * @brief     Gets the current volume for a specific mixer input.
     *
     * @param[in] inputIndex  Mixer input index (0..Capabilities.inputs.length-1).
     * @returns   Current volume level 0..100. While a ramp is in progress
     *            (setInputVolumeRamp), returns the instantaneous current
     *            volume along the ramp, not the target.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if inputIndex is invalid.
     *
     * @see       setInputVolume(), setInputVolumeRamp()
     */
    int getInputVolume(in int inputIndex);

    /**
     * @brief     Smoothly ramps the volume of a specific mixer input.
     * @details   Walks the input's volume from its current value to
     *            targetVolume over overMs milliseconds, following the chosen
     *            VolumeRamp curve. Use this for any volume change that
     *            happens while audio is flowing — instantaneous changes
     *            cause audible clicks (zipper noise).
     *
     *            Typical durations are 50–500 ms — long enough to avoid
     *            clicks, short enough to feel responsive. Common ducking
     *            pattern: 200 ms attack to duck the main input, hold while
     *            the system sound plays, 300 ms release to restore.
     *
     *            If a ramp is already in progress on this input, it is
     *            stopped at its current instantaneous volume and replaced by
     *            this new ramp starting from that point.
     *
     *            Ducking with this API works uniformly across all input
     *            source types — sink-routed, tunnelled decoder, and direct
     *            (HDMI / Composite) inputs alike. This is the only API that
     *            does so; sink-side IAudioSinkController.setVolumeRamp()
     *            applies only to sink-routed sources.
     *
     * @param[in] inputIndex    Mixer input index (0..Capabilities.inputs.length-1).
     * @param[in] targetVolume  Target volume at end of ramp (0..100).
     * @param[in] overMs        Duration of the ramp in milliseconds. Must be > 0.
     *                          A value of 0 is rejected; use setInputVolume()
     *                          for instantaneous changes.
     * @param[in] curve         Ramp curve from VolumeRamp enum
     *                          (LINEAR, IN_CUBIC, OUT_CUBIC).
     *
     * @returns   true on success, false if any parameter is out of range.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if inputIndex,
     *            targetVolume, or overMs is invalid.
     * @exception binder::Status EX_ILLEGAL_STATE if the mixer is not in
     *            STARTED state.
     *
     * @see       setInputVolume(), getInputVolume(), VolumeRamp
     */
    boolean setInputVolumeRamp(in int inputIndex, in int targetVolume, in int overMs, in VolumeRamp curve);
}
