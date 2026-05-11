/*
 * If not stated otherwise in this file or in the LICENSE file distributed with this
 * file, this file is distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

package com.rdk.hal.audiomixer;

/**
 * @brief Audio capture operation status codes.
 * Enumeration of status/error codes used in IAudioCaptureListener callbacks.
 */
@VintfStability
enum AudioCaptureStatus {
    /**
     * Operation completed successfully.
     */
    SUCCESS = 0,

    /**
     * Requested audio capture format is not valid or not supported.
     */
    ERROR_INVALID_FORMAT = 1,

    /**
     * Audio capture operation is not supported by this output port.
     */
    ERROR_NOT_SUPPORTED = 2,

    /**
     * Audio capture resource is unavailable (e.g., already in use, port disconnected).
     */
    ERROR_RESOURCE_UNAVAILABLE = 3,

    /**
     * Audio capture operation invalid for current state (e.g., stop called when not started).
     */
    ERROR_INVALID_STATE = 4,

    /**
     * Ring buffer overflow occurred because client consumption was too slow.
     * New incoming audio data was dropped and is lost.
     */
    ERROR_OVERFLOW = 5,
}
