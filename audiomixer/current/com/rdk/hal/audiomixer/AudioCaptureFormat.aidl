/*
 * If not stated otherwise in this file or in the LICENSE file distributed with this
 * file, this file is distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

package com.rdk.hal.audiomixer;

/**
 * @brief Audio capture output format selection.
 * Specifies the desired format for captured audio data from an output port.
 */
@VintfStability
enum AudioCaptureFormat {
    /**
     * Capture audio in raw encoded format (passthrough).
     * Audio is captured in the same codec/format as present at the input before mixing.
     */
    RAW_ENCODED = 0,

    /**
     * Capture audio as decoded linear PCM.
     * Audio is decoded and provided as PCM samples regardless of input codec.
     */
    PCM_DECODED = 1,

    /**
     * Automatically select format based on port capabilities.
     * Defaults to PCM_DECODED if available, otherwise RAW_ENCODED.
     */
    AUTO = 2,
}
