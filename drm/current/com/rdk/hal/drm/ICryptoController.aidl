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
package com.rdk.hal.drm;
import com.rdk.hal.PropertyValue;
import com.rdk.hal.drm.DecryptArgs;

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
 *  @brief     Crypto Controller HAL interface.
 *  @author    TBD
 */

@VintfStability
interface ICryptoController {

    /**
     * @brief Sets a property.
     *
     * @param[in] property              The key of a property.
     * @param[in] propertyValue         Holds the value to set.
     *
     * @returns Success flag indicating property update status.
     * @retval true     The property was successfully set.
     * @retval false    Invalid property key or value.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid property and propertyValue.
     */
    boolean setProperty(in int property, in PropertyValue propertyValue);

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
     * @param mime The content mime-type
     * @return must be true only if a secure decoder is required
     * for the specified mime-type
     */
    boolean requiresSecureDecoderComponent(in String mime);

//ToDO: Define supported mime types.

    /**
     * Associate a mediadrm session with this crypto session.
     *
     * @param sessionId the MediaDrm session ID to associate with
     *     this crypto session
     * @return (implicit) the status of the call, status can be:
     *     ERROR_DRM_SESSION_NOT_OPENED if the session is not opened, or
     *     ERROR_DRM_CANNOT_HANDLE if the operation is not supported by
     *         the drm scheme
     */
    void setMediaDrmSession(in byte[] sessionId);

// TODO: the session can be passed in at creation, or this call can be used. Potentially the sessionID can change if there is a key change.

    /**
     * Set a shared memory base for subsequent decrypt operations.
     * The buffer base is mmaped from a ParcelFileDesciptor in Ashmem
     * which maps shared memory in the HAL module.
     * After the shared buffer base is established, the decrypt() method
     * receives SharedBuffer instances which specify the buffer address range
     * for decrypt source and destination addresses.
     *
     * There can be multiple shared buffers per crypto plugin. The buffers
     * are distinguished by the bufferId.
     *
     * @param base the base of the memory buffer abstracted by
     *     SharedBuffer parcelable (bufferId, size, handle)
     */
    void setSharedBufferBase(in SharedBuffer base);

// TODO. We could change the way AVBuffer works to allow the complete buffer to be allocated and the offsets used?
// Is this a better way? 
// One alloc. Maybe the gstreamer appsrc issue disappears?
// It is closer to Android.


}
