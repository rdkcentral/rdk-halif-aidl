/*
 * Copyright (C) 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * -------------------------------------------------------------------
 * This file is derived from Android 16 drm interface definitions:
 *
 * https://android.googlesource.com/platform/hardware/interfaces/+/refs/tags/android-16.0.0_r4/drm/aidl/android/hardware/drm    
 * 
 * Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0.
 * -------------------------------------------------------------------
 */
package com.rdk.hal.drm;
import com.rdk.hal.drm.DecryptArgs;
import com.rdk.hal.drm.DestinationBuffer;
import com.rdk.hal.drm.Mode;
import com.rdk.hal.drm.Pattern;
import com.rdk.hal.drm.SharedBuffer;
import com.rdk.hal.drm.Status;
import com.rdk.hal.drm.SubSample;

/*
Notes: 
In android.
SessionID created by IDrmPlugin for the DRM scheme.
SessionID is passed to ICryptoPlugin to link it to the DRM so keys can be used securely.
The initialized decoder is used to create the Buffer Pool for receiving the decrypted stream data.
The pool is passed to ICryptoPlugin this allows the link between Buffer pool and DRM to be made. Since it comes from decoder then there is then a secure linked bewteen DRM,decrypt, and decoder.   
Now the pipeline can start.

A Secure buffer pool is conceptually "tied" to the decoder that will consume data from it.
Therefore:

The decoder must be opened and configurd to be a secure decoder.
The Buffer pool for the DecoderID will by default be configured inaccordance to its maximum capabilities.
For Video decoders the size of the buffer pool can be constrained by setting the maximum height and width.
This can allow for more lower resolution capable decoders and decrypt streams.
e.g. 1xUHD + 1xFHD or 4xFHD.

*/


/**
 * ICryptoPlugin is the HAL for vendor-provided crypto plugins.
 *
 * It allows crypto sessions to be opened and operated on, to
 * load crypto keys for a codec to decrypt protected video content.
 */
@VintfStability
interface ICryptoPlugin {
    /**
     * Decrypt an array of subsamples from the source memory buffer to the
     * destination memory buffer.
     *
     * @return number of decrypted bytes
     *     Implicit error codes:
     *       + ERROR_DRM_CANNOT_HANDLE in other failure cases
     *       + ERROR_DRM_DECRYPT if the decrypt operation fails
     *       + ERROR_DRM_FRAME_TOO_LARGE if the frame being decrypted into
     *             the secure output buffer exceeds the size of the buffer
     *       + ERROR_DRM_INSUFFICIENT_OUTPUT_PROTECTION if required output
     *             protections are not active
     *       + ERROR_DRM_INSUFFICIENT_SECURITY if the security level of the
     *             device is not sufficient to meet the requirements in
     *             the license policy
     *       + ERROR_DRM_INVALID_STATE if the device is in a state where it
     *             is not able to perform decryption
     *       + ERROR_DRM_LICENSE_EXPIRED if the license keys have expired
     *       + ERROR_DRM_NO_LICENSE if no license keys have been loaded
     *       + ERROR_DRM_RESOURCE_BUSY if the resources required to perform
     *             the decryption are not available
     *       + ERROR_DRM_SESSION_NOT_OPENED if the decrypt session is not
     *             opened
     */
    int decrypt(in DecryptArgs args);

    /**
     * Notify a plugin of the currently configured resolution.
     *
     * @param width - the display resolutions's width
     * @param height - the display resolution's height
     */
    void notifyResolution(in int width, in int height);

    /**
     * Check if the specified mime-type requires a secure decoder
     * component.
     *
     * Video:	video/avc (H.264), video/hevc (H.265), video/x-vnd.on2.vp9, video/av1, video/mp4v-es
     * Audio:	audio/mp4a-latm (AAC), audio/ac3, audio/eac3, audio/vnd.dts, audio/opus
     *
     * @param mime The content mime-type
     * @return must be true only if a secure decoder is required
     * for the specified mime-type
     */
    boolean requiresSecureDecoderComponent(in String mime);

    /**
     * Associate a mediadrm session with this crypto session.
     *
     * The session (if known) can be passed in at creation, or this call can be used. 
     * Potentially the sessionID can change if there is a key change.
     *
     * @param sessionId the MediaDrm session ID to associate with
     *     this crypto session
     * @return (implicit) the status of the call, status can be:
     *     ERROR_DRM_SESSION_NOT_OPENED if the session is not opened, or
     *     ERROR_DRM_CANNOT_HANDLE if the operation is not supported by
     *         the drm scheme
     */
    void setMediaDrmSession(in byte[] sessionId);



}
