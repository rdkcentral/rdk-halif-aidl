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

/**
 *  @brief     Far Field Voice Controller interface.
 *  @author    Philip Stick
 *  @author    Gary Skrabutenas
 */

@VintfStability
interface IFarFieldVoiceController {

    /**
     * Open the Keyword channel.
     *
     * If successful, creates and returns a pipe for passing Keyword channel audio to the client.
     *
     * Audio data is signed 16 bits per sample at 16kHz sampling rate. The endian order of each sample
     * value is that of the host processor's native endian order.
     *
     * If successful, the Keyword channel is in the open state.
     * 
     * @returns ParcelFileDescriptor or null if the Keyword channel is already open or pipe create fails.
     *
     * @exception binder::Status EX_ILLEGAL_STATE           The Keyword channel is already open.
     * @exception binder::Status EX_NULL_POINTER            Pipe create failed.
     *
     * @pre The Keyword channel must be in the closed state.
     * 
     * @see closeKeywordChannel()
     */
    @nullable ParcelFileDescriptor openKeywordChannel();

    /**
     * Close the Keyword channel.
     *
     * The Keyword channel is stopped, the channel's pipe is closed, and the Keyword channel is in the
     * closed state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE       The Keyword channel is not open.
     *
     * @pre The Keyword channel must be in the open state.
     * 
     * @see openKeywordChannel()
     */
    void closeKeywordChannel();

    /**
     * Start the Keyword channel.
     *
     * Keyword channel audio processing is initialized and keyword detection is started. Upon keyword
     * detection, audio samples are written to the Keyword channel's pipe.
     *
     * Once a keyword is detected, the Far Field Voice service begins writing audio samples to the Keyword
     * channel's pipe whenever audio samples are available. Initially, samples may be written to the pipe
     * faster than real time as audio buffered within the service is provided as fast as possible. Once all
     * buffered audio is written to the pipe, audio will be written at a rate based on 16kHz sampling rate
     * (real time).
     *
     * The following IFarFieldVoiceControllerListener callbacks can occur after the Keyword channel is started.
     *   onKeywordDetected()
     *   onStartOfCommand()
     *   onEndOfCommand()
     *   onNoStartOfCommand()
     *   onNoEndOfCommand()
     *
     * The sample offset values provided in 'onKeywordDetected', 'onStartOfCommand', 'onEndOfCommand',
     * 'onNoStartOfCommand', and 'onNoEndOfCommand' are the relative sample number with respect to the audio
     * samples written to the Keyword channel's pipe. A sample offset value of zero corresponds to the first
     * sample written after starting the Keyword channel.
     *
     * A normal sequence of callbacks after the keyword is detected:
     *   onKeywordDetected()
     *   onStartOfCommand()
     *   onEndOfCommand()
     *
     * The sequence of callbacks when the start of a voice command is not detected:
     *   onKeywordDetected()
     *   onNoStartOfCommand()
     *
     * The sequence of callbacks when the end of a voice command is not detected:
     *   onKeywordDetected()
     *   onStartOfCommand()
     *   onNoEndOfCommand()
     *
     * If the Keyword channel is already started, keyword detection is reset, audio samples are not
     * written to the Keyword channel's pipe until after a keyword is detected, and SUCCESS is returned.
     *
     * @exception binder::Status EX_ILLEGAL_STATE       The Keyword channel is not open.
     *
     * @pre The Keyword channel must be in the open state.
     * 
     * @see openKeywordChannel()
     */
    void startKeywordChannel();

    /**
     * Stop the Keyword channel.
     *
     * Keyword channel audio processing is stopped. Audio samples are not written to the Keyword channel's pipe.
     *
     * If the Keyword channel is already stopped, no action occurs and SUCCESS is returned.
     *
     * @exception binder::Status EX_ILLEGAL_STATE       The Keyword channel is not open.
     *
     * @pre The Keyword channel must be in the open state.
     * 
     * @see openKeywordChannel(), startKeywordChannel()
     */
    void stopKeywordChannel();

    /**
     * Open the Continual channel.
     *
     * If successful, creates and returns a pipe for passing Continual channel audio to the client.
     *
     * Audio data is signed 16 bits per sample at 16kHz sampling rate. The endian order of each sample
     * value is that of the host processor's native endian order.
     *
     * The Continual channel can be opened only in Full Power mode.
     *
     * If successful, the Continual channel is in the open state.
     * 
     * @returns ParcelFileDescriptor or null if the Continual channel is already open, the power mode
     *          is not Full Power, or pipe create fails.
     *
     * @exception binder::Status EX_ILLEGAL_STATE           The Continual channel is already open or power mode is not Full Power.
     * @exception binder::Status EX_NULL_POINTER            Pipe create failed.
     *
     * @pre The Continual channel must be in the closed state.
     * @pre The power mode must be Full Power.
     * 
     * @see closeContinualChannel()
     */
    @nullable ParcelFileDescriptor openContinualChannel();

    /**
     * Close the Continual channel.
     *
     * The Continual channel is stopped, the channel's pipe is closed, and the Continual channel is in
     * the closed state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE       The Continual channel is not open.
     *
     * @pre The Continual channel must be in the open state.
     * 
     * @see openContinualChannel()
     */
    void closeContinualChannel();

    /**
     * Start the Continual channel.
     *
     * Continual channel audio processing is initialized and audio samples are written to the Continual
     * channel's pipe at 16kHz sampling rate.
     *
     * If the Continual channel is already started, no action occurs and SUCCESS is returned.
     *
     * @exception binder::Status EX_ILLEGAL_STATE       The Continual channel is not open.
     *
     * @pre The Continual channel must be in the open state.
     * 
     * @see openContinualChannel()
     */
    void startContinualChannel();

    /**
     * Stop the Continual channel.
     *
     * Continual channel audio processing is stopped. Audio samples are not written to the Continual
     * channel's pipe.
     *
     * If the Continual channel is already stopped, no action occurs and SUCCESS is returned.
     *
     * @exception binder::Status EX_ILLEGAL_STATE       The Continual channel is not open.
     *
     * @pre The Continual channel must be in the open state.
     * 
     * @see openContinualChannel(), startContinualChannel()
     */
    void stopContinualChannel();

    /**
     * Open the Microphone channels.
     *
     * If successful, creates and returns a pipe for passing raw microphone data to the client.
     *
     * Audio data is signed 32 bits per sample at 16kHz sampling rate. The endian order of each sample
     * value is that of the host processor's native endian order. Multiple microphones are interleaved
     * by sample with the number of microphones being equal to the microphoneChannelCount field in the
     * Far Field Voice service's Capabilities.
     *
     * The Microphone channels can be opened only in Full Power mode.
     *
     * If successful, the Microphone channels is in the open state.
     * 
     * @returns ParcelFileDescriptor or null if the Microphone channels is already open, the power mode is not
     *          Full Power, or pipe create fails.
     *
     * @exception binder::Status EX_ILLEGAL_STATE           The Microphone channels is already open or power mode is not Full Power.
     * @exception binder::Status EX_NULL_POINTER            Pipe create failed.
     *
     * @pre The Microphone channels must be in the closed state.
     * @pre The power mode must be Full Power.
     * 
     * @see closeMicrophoneChannels()
     */
    @nullable ParcelFileDescriptor openMicrophoneChannels();

    /**
     * Close the Microphone channels.
     *
     * The Microphone channels is stopped, the channel's pipe is closed, and the Microphone channels is in the
     * closed state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE       The Microphone channels is not open.
     *
     * @pre The Microphone channel(s) must be in the open state.
     * 
     * @see openMicrophoneChannels()
     */
    void closeMicrophoneChannels();

    /**
     * Start the Microphone channels.
     *
     * Microphone channels raw microphone samples are written to the Microphone channel's pipe at 16kHz
     * sampling rate.
     *
     * If the Microphone channels is already started, no action occurs and SUCCESS is returned.
     *
     * @exception binder::Status EX_ILLEGAL_STATE       The Microphone channels is not open.
     *
     * @pre The Microphone channels must be in the open state.
     * 
     * @see openMicrophoneChannels()
     */
    void startMicrophoneChannels();

    /**
     * Stop the Microphone channels.
     *
     * Microphone channels audio processing is stopped. Audio samples are not written to the Microphone
     * channel's pipe.
     *
     * If the Microphone channels is already stopped, no action occurs and SUCCESS is returned.
     *
     * @exception binder::Status EX_ILLEGAL_STATE       The Microphone channels is not open.
     *
     * @pre The Microphone channels must be in the open state.
     * 
     * @see openMicrophoneChannels(), startMicrophoneChannels()
     */
    void stopMicrophoneChannels();

    /**
     * Start (activate) privacy state.
     *
     * All audio input will be forced to silence when privacy state is active.
     */
    void startPrivacyState();

    /**
     * Stop (inactivate) privacy state.
     *
     * All audio input will use actual input when privacy state is inactive.
     */
    void stopPrivacyState();

    /**
     * Enter Full Power mode processing state.
     *
     * If successful, Full Power mode audio processing will be initialized.
     *
     * @exception binder::Status EX_ILLEGAL_STATE       All audio channels must be in the closed state.
     *
     * @pre All audio channels must be in the closed state.
     *
     * @see IFarFieldVoiceEventListener.onEnteredFullPowerMode(), IFarFieldVoiceEventListener.onFullPowerModeFailed()
     */
    void enterFullPowerMode();

    /**
     * Enter Standby mode processing state.
     *
     * If successful, Standby (low power) mode audio processing will be initialized.
     *
     * @exception binder::Status EX_ILLEGAL_STATE       All audio channels must be in the closed state.
     *
     * @pre All audio channels must be in the closed state.
     *
     * @see IFarFieldVoiceEventListener.onEnteredStandbyMode(), IFarFieldVoiceEventListener.onStandbyModeFailed()
     */
    void enterStandbyMode();

    /**
     * Enter Deep Sleep mode processing state.
     *
     * All channels will be closed and Deep Sleep (no power) mode will be initiated.
     *
     * @see IFarFieldVoiceEventListener.onEnteredDeepSleepMode()
     */
    void enterDeepSleepMode();

    /**
     * Start recording audio.
     *
     * Captures of audio I/O will be written to wave files for test purposes. Each wave file name
     * will begin with the specified base path and file name and end with a vendor specific extension
     * correlating to the particular captured audio I/O.
     *
     * @param[in] fileNamePrefix    File name prefix (path and base file name).
     * @param[in] ioSelect          Selected I/O to capture (vendor specific code).
     *
     * @return boolean
     * @retval true             Successfully started recording.
     * @retval false            An error occurred opening file(s).
     */
    boolean startAudioRecording(in @utf8InCpp String fileNamePrefix, in long ioSelect);

    /**
     * Stop recording audio.
     *
     * @return boolean
     * @retval true             Successfully stopped recording.
     * @retval false            An error occurred closing file(s).
     */
    boolean stopAudioRecording();

    /**
     * Perform a test command.
     *
     * Performs a vendor specific test command for test and debug purposes.
     *
     * @param[in] command       Test command.
     *
     * @returns string - Response to command.
     */
    @utf8InCpp String testCommand(in @utf8InCpp String command);
}
