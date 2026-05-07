/*
 * If not stated otherwise in this file or in the LICENSE file distributed with this
 * file, this file is distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

package com.rdk.hal.audiomixer;

import com.rdk.hal.audiomixer.AudioCapturePcmInfo;

/**
 * @brief Audio capture data frame with metadata.
 * Encapsulates a single audio frame and its associated metadata (channels, sample rate, timestamp, format).
 *
 * When format is AudioCaptureFormat.PCM_DECODED, the pcmInfo field is populated with PCM sample
 * encoding details (bit depth, signedness, byte order).
 */
@VintfStability
parcelable AudioCaptureData {
    /**
     * Raw audio data bytes. Format and encoding determined by the `format` field.
     */
    byte[] audioData;

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
     * Format of captured audio (raw encoded or decoded PCM).
     */
    AudioCaptureFormat format;

    /**
     * Human-readable codec name (e.g., "AC3", "AAC", "PCM", "AAC-LC").
     * Populated only when relevant to the captured format.
     */
    String codecName;

    /**
     * PCM sample encoding details (bit depth, signedness, byte order).
     * Populated only when format is AudioCaptureFormat.PCM_DECODED; null otherwise.
     */
    @nullable AudioCapturePcmInfo pcmInfo;
}
