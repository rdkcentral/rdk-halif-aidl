/*
 * If not stated otherwise in this file or in the LICENSE file distributed with this
 * file, this file is distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

package com.rdk.hal.audiomixer;

/**
 * @brief Audio capture interface for output ports.
 * 
 * Provides stateful control over audio capture sessions on an output port.
 * Clients register a listener, call start() to begin streaming, receive async callbacks
 * via IAudioCaptureListener, then call stop() to end the session.
 * 
 * Example lifecycle:
 * @code
 *   capture.start(AudioCaptureFormat.PCM_DECODED);  // Listener receives onStarted()
 *   // Listener receives multiple onDataAvailable(AudioCaptureData) calls
 *   capture.stop();                                   // Listener receives onStopped()
 * @endcode
 * 
 * Thread safety:
 * All methods are serialised by the binder layer. Concurrent calls from multiple threads
 * are safe but serialised through the underlying service implementation.
 */
@VintfStability
interface IAudioCapture {
    /**
     * @brief Queries supported audio capture formats for this output port.
     * 
     * Returns list of AudioCaptureFormat values that this output port can provide.
     * Returned array must contain at least one format (typically PCM_DECODED or RAW_ENCODED).
     * 
     * @returns Array of supported AudioCaptureFormat enum values (non-empty).
     * 
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if capture not supported on this port.
     */
    AudioCaptureFormat[] getSupportedFormats();

    /**
     * @brief Start audio capture stream in the specified format.
     * 
     * Transitions capture interface from stopped to started state. Listener will receive
     * onStarted() callback, followed by repeated onDataAvailable() callbacks as audio
     * frames become available. Call stop() to end the stream.
     * 
     * @param[in] format Desired capture output format (RAW_ENCODED, PCM_DECODED, or AUTO).
     *                    Use getSupportedFormats() to discover available formats.
     * 
     * @returns true if capture stream started successfully.
     * 
     * @exception binder::Status EX_ILLEGAL_STATE if capture already started.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if requested format not supported by this port.
     */
    boolean start(in AudioCaptureFormat format);

    /**
     * @brief Stop audio capture stream.
     * 
     * Transitions capture interface from started to stopped state. Listener will receive
     * onStopped() callback after this method returns. No further onDataAvailable() callbacks
     * will be delivered.
     * 
     * @returns true if capture stream stopped successfully, false if already stopped.
     * 
     * @exception binder::Status EX_ILLEGAL_STATE if capture not started.
     */
    boolean stop();
}
