/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
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
package com.rdk.hal.farfieldvoice;
import com.rdk.hal.farfieldvoice.PowerMode;

/**
 *  @brief     Far Field Voice Controller interface.
 *  @author    Philip Stick
 *  @author    Gary Skrabutenas
 */

@VintfStability
interface IFarFieldVoiceController {

    /**
     * Open an audio channel.
     *
     * If successful, creates and returns a pipe for passing the specified channel type audio to the
     * client and the specified channel type is in the open state.
     *
     * If channelType is "KEYWORD"
     *
     *  Keyword channel audio processing is initialized and keyword detection is started. Upon keyword
     *  detection, audio samples are written to the channel's pipe.
     *
     *  Audio data is signed 16 bits per sample at 16kHz sampling rate. The endian order of each sample
     *  value is that of the host processor's native endian order.
     *
     *  Once a keyword is detected, the Far Field Voice HAL begins writing audio samples to the Keyword
     *  channel's pipe whenever audio samples are available. Initially, samples may be written to the pipe
     *  faster than real time as audio buffered within the HAL is provided as fast as possible. Once all
     *  buffered audio is written to the pipe, audio will be written at a rate based on 16kHz sampling rate
     *  (real time).
     *
     *  The following controller callbacks can occur after the Keyword channel is opened.
     *   onKeywordDetected()
     *   onEndOfCommand()
     *
     *  The sample offset values provided in 'onKeywordDetected' and 'onEndOfCommand' are the relative
     *  sample number with respect to the audio samples written to the channel's pipe. A sample offset
     *  value of zero corresponds to the first sample written after opening the channel.
     *
     *  @pre The "KEYWORD" channel must be in the closed state.
     *  @pre The "MICROPHONES" channel must be in the closed state.
     *  @pre The power mode must be PowerMode::FULL_POWER or PowerMode::STANDBY.
     *
     *  @exception binder::Status::Exception::EX_ILLEGAL_STATE      The "KEYWORD" channel is already open, or the
     *                                                              "MICROPHONES" channel is open, or power mode is
     *                                                              not PowerMode::FULL_POWER or PowerMode::STANDBY.
     *
     * If channelType is "MICROPHONES"
     *
     *  Raw microphone data is written to the channel's pipe at 16kHz sampling rate. Sample values are signed 32 bits
     *  per sample. The endian order of each sample value is that of the host processor's native endian order.
     *  Multiple microphones are interleaved by sample with the number of microphones being equal to the
     *  microphoneChannelCount field in the FFVhalCapabilities_t structure provided by FFVhal_GetCapabilities.
     *
     *  @pre The "MICROPHONES" channel must be in the closed state.
     *  @pre The "KEYWORD" channel must be in the closed state.
     *  @pre The power mode must be PowerMode::FULL_POWER.
     *
     *  @exception binder::Status::Exception::EX_ILLEGAL_STATE      The "MICROPHONES" channel is already open, or
     *                                                              the "KEYWORD" channel is open, or power mode is
     *                                                              not PowerMode::FULL_POWER.
     *
     * Common to all channel types:
     *
     * @param[in] channelType       Selected channel type.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT    Invalid channel type.
     * @exception binder::Status::Exception::EX_NULL_POINTER        Pipe create failed.
     * 
     * @returns ParcelFileDescriptor or null if an exception occurs.
     * 
     * @see closeChannel()
     */
    @nullable ParcelFileDescriptor openChannel(in @utf8InCpp String channelType);

    /**
     * Close an audio channel.
     *
     * The specified channel type audio processing is stopped, the channel's pipe is closed, and the
     * channel is in the closed state.
     *
     * @pre The specified channel type must be in the open state.
     *
     * @param[in] channelType       Selected channel type.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT   Invalid channel type.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE      Channel type is not open.
     * 
     * @see openChannel()
     */
    void closeChannel(in @utf8InCpp String channelType);

    /**
     * Set (activate or deactivate) privacy state.
     *
     * All audio input will be forced to silence when privacy state is active.
     * All audio input will use actual input when privacy state is inactive.
     *
     * @param[in] activate      true = activate privacy, false = deactivate privacy
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     */
    void setPrivacyState(in boolean activate);

    /**
     * Set power mode.
     *
     * If successful, the specified power mode is initialized.
     *
     * @pre All audio channels must be in the closed state.
     *
     * @param[in] powerMode       Selected power mode.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT    Invalid power mode.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE       All audio channels must be in the closed state.
     * @exception binder::Status::Exception::EX_NULL_POINTER        Power mode initialization failed.
     *
     * @see IFarFieldVoiceEventListener.onEnteredPowerMode(), IFarFieldVoiceEventListener.onHardwareFailed()
     */
    void setPowerMode(in PowerMode powerMode);

    /**
     * Start recording audio.
     *
     * Captures of audio will be written to wave files for test purposes. Each wave file name
     * will begin with the specified base path and file name and end with a vendor specific extension
     * correlating to the particular captured audio.
     *
     * @param[in] fileNamePrefix    File name prefix (path and base file name).
     * @param[in] audioSelect       Selected audio to capture (vendor specific code).
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT     Unknown audio selection.
     * @exception binder::Status::Exception::EX_NULL_POINTER         File create failed.
     */
    void startAudioRecording(in @utf8InCpp String fileNamePrefix, in long audioSelect);

    /**
     * Stop recording audio.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     */
    void stopAudioRecording();

    /**
     * Perform a test command.
     *
     * Performs a vendor specific test command for test and debug purposes.
     *
     * @param[in] command       Test command.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns string - Response to command.
     */
    @utf8InCpp String testCommand(in @utf8InCpp String command);
}
