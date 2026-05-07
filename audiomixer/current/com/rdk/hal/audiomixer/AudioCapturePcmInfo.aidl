/*
 * If not stated otherwise in this file or in the LICENSE file distributed with this
 * file, this file is distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

package com.rdk.hal.audiomixer;

/**
 * @brief PCM sample format descriptor for captured audio.
 * 
 * Describes the binary encoding of PCM samples within an AudioCaptureData frame.
 * Only populated when AudioCaptureData.format is AudioCaptureFormat.PCM_DECODED.
 */
@VintfStability
parcelable AudioCapturePcmInfo {
    /**
     * Number of significant bits per PCM sample (e.g., 16, 24, 32).
     */
    int bitsPerSample;

    /**
     * Container word size in bits that each sample is packed into (e.g., 32).
     * When equal to bitsPerSample, samples are tightly packed with no padding.
     * When greater (e.g., bitsPerSample=24, containerBitsPerSample=32), each sample
     * occupies a larger container word with the unused bits padded to zero.
     */
    int containerBitsPerSample;

    /**
     * True if samples are signed integers; false if unsigned.
     * Signed is typical for 16-bit and 32-bit PCM. 8-bit PCM is commonly unsigned.
     */
    boolean isSigned;

    /**
     * True if sample bytes are in little-endian order; false for big-endian.
     * Little-endian is standard on x86/ARM platforms.
     */
    boolean isLittleEndian;
}
