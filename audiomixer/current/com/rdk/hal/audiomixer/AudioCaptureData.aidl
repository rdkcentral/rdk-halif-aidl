/*
 * If not stated otherwise in this file or in the LICENSE file distributed with this
 * file, this file is distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

package com.rdk.hal.audiomixer;

import com.rdk.hal.audiomixer.AudioCapturePcmInfo;
import com.rdk.hal.audiomixer.OutputFormat;

/**
 * @brief Audio capture data frame with metadata.
 * Encapsulates metadata for a single audio frame stored in shared-memory ring buffer.
 *
 * The data captured by the Audio Capture interface is the same as the data output by the port.
 * When a capture port provides a capture interface for a physical output (e.g. HDMI, Speakers, etc.) 
 * then the captured data is a copy. 
 */
@VintfStability
parcelable AudioCaptureData {
    /**
     * Number of audio channels (e.g., 1 for mono, 2 for stereo, 6 for 5.1 surround).
     */
    int channels;

    /**
     * Audio sample rate in Hertz (e.g., 48000, 96000).
     */
    int sampleRateHz;

    /**
     * Timestamp in microseconds (μs).
     * Typically monotonic time or frame-relative timestamp depending on implementation.
     */
    long timestampUs;

    /**
     * Format of captured audio.
     */
    OutputFormat format;

    /**
     * Human-readable codec name (e.g., "AC3", "AAC", "PCM", "AAC-LC").
     * Populated only when relevant to the captured format.
     */
    String codecName;

    /**
     * PCM sample encoding details (bit depth, signedness, byte order).
     * Populated only when format is PCM, null otherwise.
     */
    @nullable AudioCapturePcmInfo pcmInfo;
}
