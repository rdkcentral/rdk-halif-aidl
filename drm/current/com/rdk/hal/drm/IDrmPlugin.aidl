
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

import com.rdk.hal.drm.DrmMetricGroup;
import com.rdk.hal.drm.HdcpLevels;
import com.rdk.hal.drm.IDrmPluginListener;
import com.rdk.hal.drm.KeySetId;
import com.rdk.hal.drm.KeyRequest;
import com.rdk.hal.drm.KeyStatus;
import com.rdk.hal.drm.KeyType;
import com.rdk.hal.drm.KeyValue;
import com.rdk.hal.drm.NumberOfSessions;
import com.rdk.hal.drm.ProvideProvisionResponseResult;
import com.rdk.hal.drm.ProvisionRequest;
import com.rdk.hal.drm.SecurityLevel;


/**
 * IDrmPlugin is used to interact with a specific drm plugin that was
 * created by IDrmFactory::createPlugin.
 *
 * A drm plugin provides methods for obtaining drm keys to be used by a codec
 * to decrypt protected video content.
 */
@VintfStability
interface IDrmPlugin {
    /**
     * Close a session on the DrmPlugin object
     *
     * @param sessionId the session id the call applies to
     *
     * @return (implicit) the status of the call:
     *     BAD_VALUE if the sessionId is invalid
     *     ERROR_DRM_INVALID_STATE if the HAL is in a state where
     *         the session cannot be closed.
     *     ERROR_DRM_SESSION_NOT_OPENED if the session is not opened
     */
    void closeSession(in byte[] sessionId);

    /**
     * Decrypt the provided input buffer with the cipher algorithm
     * specified by setCipherAlgorithm and the key selected by keyId,
     * and return the decrypted data.
     *
     * @param sessionId the session id the call applies to
     * @param keyId the ID of the key to use for decryption
     * @param input the input data to decrypt
     * @param iv the initialization vector to use for decryption
     *
     * @return decrypted output buffer
     *     Implicit error codes:
     *       + BAD_VALUE if the sessionId is invalid
     *       + ERROR_DRM_INVALID_STATE if the HAL is in a state where
     *             the decrypt operation cannot be performed.
     *       + ERROR_DRM_SESSION_NOT_OPENED if the session is not opened
     */
    byte[] decrypt(in byte[] sessionId, in byte[] keyId, in byte[] input, in byte[] iv);

    /**
     * Encrypt the provided input buffer with the cipher algorithm specified by
     * setCipherAlgorithm and the key selected by keyId, and return the
     * encrypted data.
     *
     * @param sessionId the session id the call applies to
     * @param keyId the ID of the key to use for encryption
     * @param input the input data to encrypt
     * @param iv the initialization vector to use for encryption
     *
     * @return encrypted output buffer
     *     Implicit error codes:
     *       + BAD_VALUE if the sessionId is invalid
     *       + ERROR_DRM_INVALID_STATE if the HAL is in a state where
     *             the encrypt operation cannot be performed.
     *       + ERROR_DRM_SESSION_NOT_OPENED if the session is not opened
     */
    byte[] encrypt(in byte[] sessionId, in byte[] keyId, in byte[] input, in byte[] iv);

    /**
     * Return the currently negotiated and max supported HDCP levels.
     *
     * For a HDMI source device:
     * 
     * The current level is based on the display(s) the device is connected to.
     * If multiple HDCP-capable displays are simultaneously connected to
     * separate interfaces, this method returns the lowest negotiated HDCP level
     * of all interfaces.
     *
     * The maximum HDCP level is the highest level that can potentially be
     * negotiated. It is a constant for any device, i.e. it does not depend on
     * downstream receiving devices that could be connected. For example, if
     * the device has HDCP 1.x keys and is capable of negotiating HDCP 1.x, but
     * does not have HDCP 2.x keys, then the maximum HDCP capability would be
     * reported as 1.x. If multiple HDCP-capable interfaces are present, it
     * indicates the highest of the maximum HDCP levels of all interfaces.
     * 
     * For a HDMI sink device:
     * 
     * On a Smart TV where the SoC is wired directly to the internal panel, 
     * the DRM stack typically reports the Maximum Security Level the hardware can 
     * attest to.
     *
     * This method should only be used for informational purposes, not for
     * enforcing compliance with HDCP requirements. Trusted enforcement of HDCP
     * policies must be handled by the DRM system.
     * 
     * Polling should be avoided or at a level that has very low performance impact on the system.
     *
     * @return HdcpLevels parcelable
     *     Implicit error codes:
     *       + ERROR_DRM_INVALID_STATE if the HAL is in a state where
     *             the HDCP level cannot be queried
     */
    HdcpLevels getHdcpLevels();

      /**
     * A key request/response exchange occurs between the app and a License
     * Server to obtain the keys required to decrypt the content.
     * getKeyRequest() is used to obtain an opaque key request blob that is
     * delivered to the license server.
     *
     * @param scope either a sessionId or a keySetId, depending on the
     *     specified keyType. When the keyType is OFFLINE or STREAMING, scope
     *     must be set to the sessionId the keys will be provided to. When the
     *     keyType is RELEASE, scope must be set to the keySetId of the keys
     *     being released.
     * @param initData container-specific data, its meaning is interpreted
     *     based on the mime type provided in the mimeType parameter. It could
     *     contain, for example, the content ID, key ID or other data obtained
     *     from the content metadata that is required to generate the key
     *     request. initData must be empty when keyType is RELEASE.
     * @param mimeType identifies the mime type of the content
     * @param keyType specifies if the keys are to be used for streaming,
     *     offline or a release
     * @param optionalParameters included in the key request message to
     *     allow a client application to provide additional message parameters
     *     to the server.
     *
     * @return KeyRequest parcelable
     *     Implicit error codes:
     *       + BAD_VALUE if any parameters are invalid
     *       + ERROR_DRM_CANNOT_HANDLE if getKeyRequest is not supported at
     *             the time of the call
     *       + ERROR_DRM_INVALID_STATE if the HAL is in a state where
     *             a key request cannot be generated
     *       + ERROR_DRM_NOT_PROVISIONED if the device requires provisioning
     *             before it is able to generate a key request
     *       + ERROR_DRM_RESOURCE_CONTENTION if client applications using the
     *             hal are temporarily exceeding the available crypto resources
     *             such that a retry of the operation is likely to succeed
     *       + ERROR_DRM_SESSION_NOT_OPENED if the session is not opened
     */
    KeyRequest getKeyRequest(in byte[] scope, in byte[] initData, in String mimeType,
            in KeyType keyType, in KeyValue[] optionalParameters);

    /**
     * Returns the plugin-specific metrics. Multiple metric groups may be
     * returned in one call to getMetrics(). The scope and definition of the
     * metrics is defined by the plugin.
     *
     * @return collection of metric groups provided by the plugin
     *     Implicit error codes:
     *       + ERROR_DRM_INVALID_STATE if the metrics are not available to be
     *             returned.
     */
    List<DrmMetricGroup> getMetrics();


//We have to make a decission about how sessions are managed.
// We can use resource manager and the  IDrmManager to manage DRMs.
// You get one DRM for the DRM Scheme you want and then configure the key session.
// For each session of the same DRM scheme you repeat and the pool of DRM sessions reduces. 
//
// Android does not work that way.
// You get a IDrmPlugin for a DRM scheme and then open as many keys sessions that you are allowed to with openSession().
//
// For Android, to manage the DRM scheme session resources the approach implies that there is a central DRM resource manager that creates sessions.
// Only one client ever calls IDrmPlugin.  

    /**
     * Return the current number of open sessions and the maximum number of
     * sessions that may be opened simultaneously among all DRM instances
     * for the active DRM scheme.
     *
     * @return NumberOfSessions parcelable
     *     Implicit error codes:
     *       + ERROR_DRM_INVALID_STATE if the HAL is in a state where the
     *             number of sessions cannot be queried
     */
    NumberOfSessions getNumberOfSessions();

/**
     * Read a byte array property value given the property name.
     * See getPropertyString.
     *
     * @param propertyName the name of the property
     *
     * @return property value bye array
     *     Implicit error codes:
     *       + BAD_VALUE if the property name is invalid
     *       + ERROR_DRM_CANNOT_HANDLE if the property is not supported
     *       + ERROR_DRM_INVALID_STATE if the HAL is in a state where the
     *             property cannot be obtained
     */
    byte[] getPropertyByteArray(in String propertyName);

    /**
     * A drm scheme can have properties that are settable and readable
     * by an app. There are a few forms of property access methods,
     * depending on the data type of the property.
     *
     * Property values defined by the public API are:
     *   "vendor" [string] identifies the maker of the drm scheme
     *   "version" [string] identifies the version of the drm scheme
     *   "description" [string] describes the drm scheme
     *   'deviceUniqueId' [byte array] The device unique identifier is
     *   established during device provisioning and provides a means of
     *   uniquely identifying each device.
     *
     * Since drm scheme properties may vary, additional field names may be
     * defined by each DRM vendor. Refer to your DRM provider documentation
     * for definitions of its additional field names.
     *
     * Read a string property value given the property name.
     *
     * @param propertyName the name of the property
     *
     * @return the property value string.
     *     Implicit error codes:
     *       + BAD_VALUE if the property name is invalid
     *       + ERROR_DRM_CANNOT_HANDLE if the property is not supported
     *       + ERROR_DRM_INVALID_STATE if the HAL is in a state where the
     *             property cannot be obtained
     */
    String getPropertyString(in String propertyName);

    /**
     * A provision request/response exchange occurs between the app
     * and a provisioning server to retrieve a device certificate.
     * getProvisionRequest is used to obtain an opaque provisioning
     * request blob that is delivered to the provisioning server.
     *
     * @param certificateType the type of certificate requested, e.g. "X.509"
     * @param certificateAuthority identifies the certificate authority.
     *     A certificate authority (CA) is an entity which issues digital
     *     certificates for use by other parties. It is an example of a
     *     trusted third party.
     *
     * @return ProvisionRequest parcelable
     *     Implicit error codes:
     *       + ERROR_DRM_CANNOT_HANDLE if the drm scheme does not require
     *             provisioning
     *       + ERROR_DRM_INVALID_STATE if the HAL is in a state where
     *             the provision request cannot be generated
     *       + ERROR_DRM_RESOURCE_CONTENTION if client applications using
     *             the hal are temporarily exceeding the available crypto
     *             resources such that a retry of the operation is likely
     *             to succeed
     */
    ProvisionRequest getProvisionRequest(
            in String certificateType, in String certificateAuthority);

    /**
     * Return the current security level of a session. A session has an initial
     * security level determined by the robustness of the DRM system's
     * implementation on the device.
     *
     * @param sessionId the session id the call applies to
     *
     * @return the current security level for the session.
     *     Implicit error codes:
     *       + BAD_VALUE if the sessionId is invalid
     *       + ERROR_DRM_INVALID_STATE if the HAL is in a state where
     *             the security level cannot be queried
     *       + ERROR_DRM_SESSION_NOT_OPENED if the session is not opened
     */
    SecurityLevel getSecurityLevel(in byte[] sessionId);

    /**
     * Open a new session at a requested security level. The security level
     * represents the robustness of the device's DRM implementation. By default,
     * sessions are opened at the native security level of the device which is
     * the maximum level that can be supported. Overriding the security level is
     * necessary when the decrypted frames need to be manipulated, such as for
     * image compositing. The security level parameter must be equal to or lower
     * than the native level. If the requested level is not supported, the next
     * lower supported security level must be set. The level can be queried
     * using {@link #getSecurityLevel}. A session ID is returned.
     *
     * @param level the requested security level
     *
     * @return sessionId
     */
    byte[] openSession(in SecurityLevel securityLevel);

//We have a question here as above. Do we only allow one session per DRM scheme DrmController instance. 
// How to manage the resource?
// What is best? Do it the Android way everywhere?

    /**
     * After a key response is received by the app, it is provided to the
     * Drm plugin using provideKeyResponse.
     *
     * @param scope may be a sessionId or a keySetId depending on the
     *     type of the response. Scope should be set to the sessionId
     *     when the response is for either streaming or offline key requests.
     *     Scope should be set to the keySetId when the response is for
     *     a release request.
     * @param response the response from the key server that is being
     *     provided to the drm HAL.
     *
     * @return a keySetId that can be used to later restore the keys to a new
     *     session with the method restoreKeys when the response is for an
     *     offline key request.
     *     Implicit error codes:
     *       + BAD_VALUE if any parameters are invalid
     *       + ERROR_DRM_CANNOT_HANDLE if provideKeyResponse is not supported
     *             at the time of the call
     *       + ERROR_DRM_DEVICE_REVOKED if the device has been disabled by
     *             the license policy
     *       + ERROR_DRM_INVALID_STATE if the HAL is in a state where
     *             a key response cannot be handled.
     *       + ERROR_DRM_NOT_PROVISIONED if the device requires provisioning
     *             before it can handle the key response
     *       + ERROR_DRM_SESSION_NOT_OPENED if the session is not opened
     */
    KeySetId provideKeyResponse(in byte[] scope, in byte[] response);

    /**
     * After a provision response is received by the app from a provisioning
     * server, it is provided to the Drm HAL using provideProvisionResponse.
     * The HAL implementation must receive the provision request and
     * store the provisioned credentials.
     *
     * @param response the opaque provisioning response received by the
     * app from a provisioning server.
     *
     * @return ProvideProvisionResponseResult parcelable, which contains
     *     the public certificate and encrypted private key that can be
     *     used by signRSA to compute an RSA signature on a message.
     *     Implicit error codes:
     *       + BAD_VALUE if any parameters are invalid
     *       + ERROR_DRM_DEVICE_REVOKED if the device has been disabled by
     *             the license policy
     *       + ERROR_DRM_INVALID_STATE if the HAL is in a state where the
     *             provision response cannot be handled
     */
    ProvideProvisionResponseResult provideProvisionResponse(in byte[] response);

    /**
     * Request an informative description of the license for the session.
     * The status is in the form of {name, value} pairs. Since DRM license
     * policies vary by vendor, the specific status field names are
     * determined by each DRM vendor. Refer to your DRM provider
     * documentation for definitions of the field names for a particular
     * drm scheme.
     *
     * @param sessionId the session id the call applies to
     *
     * @return a list of name value pairs describing the license.
     *     Implicit error codes:
     *       + ERROR_DRM_SESSION_NOT_OPENED if the session is not opened
     *       + BAD_VALUE if any parameters are invalid
     *       + ERROR_DRM_INVALID_STATE if the HAL is in a state where the
     *             key status cannot be queried.
     */
    List<KeyValue> queryKeyStatus(in byte[] sessionId);

    /**
     * Remove the current keys from a session
     *
     * @param sessionId the session id the call applies to
     *
     * @return (implicit) the status of the call:
     *     BAD_VALUE if the sessionId is invalid
     *     ERROR_DRM_INVALID_STATE if the HAL is in a state where
     *         the keys cannot be removed.
     *     ERROR_DRM_SESSION_NOT_OPENED if the session is not opened
     */
    void removeKeys(in byte[] sessionId);

// Question. Do we need offline License support?
// restoreKeys()? removeOfflineLicense()? etc.

    /**
     * Check if the specified mime-type & security level require a secure decoder
     * component.
     *
     * @param mime The content mime-type
     * @param level the requested security level
     *
     * @return must be true if and only if a secure decoder is
     *     required for the specified mime-type & security level
     */
    boolean requiresSecureDecoder(in String mime, in SecurityLevel level);

//TODO: Add mime types.

    /**
     * The following methods implement operations on a CryptoSession to support
     * encrypt, decrypt, sign verify operations on operator-provided
     * session keys.
     *
     *
     * Set the cipher algorithm to be used for the specified session.
     *
     * @param sessionId the session id the call applies to
     * @param algorithm the algorithm to use. The string conforms to JCA
     *     Standard Names for Cipher Transforms and is case insensitive. An
     *     example algorithm is "AES/CBC/PKCS5Padding".
     *
     * @return (implicit) the status of the call:
     *     BAD_VALUE if any parameters are invalid
     *     ERROR_DRM_INVALID_STATE  if the HAL is in a state where
     *         the algorithm cannot be set.
     *     ERROR_DRM_SESSION_NOT_OPENED if the session is not opened`
     */
    void setCipherAlgorithm(in byte[] sessionId, in String algorithm);

    /**
     * Set the MAC algorithm to be used for computing hashes in a session.
     *
     * @param sessionId the session id the call applies to
     * @param algorithm the algorithm to use. The string conforms to JCA
     *     Standard Names for Mac Algorithms and is case insensitive. An example MAC
     *     algorithm string is "HmacSHA256".
     *
     * @return (implicit) the status of the call:
     *     BAD_VALUE if any parameters are invalid
     *     ERROR_DRM_INVALID_STATE  if the HAL is in a state where
     *         the algorithm cannot be set.
     *     ERROR_DRM_SESSION_NOT_OPENED if the session is not opened`
     */
    void setMacAlgorithm(in byte[] sessionId, in String algorithm);

    /**
     * Set playback id of a drm session. The playback id can be used to join drm session metrics
     * with metrics from other low level media components, e.g. codecs, or metrics from the high
     * level player.
     *
     * @param sessionId drm session id
     * @param playbackId high level playback id
     *
     * @return (implicit) the status of the call:
     *    ERROR_DRM_SESSION_NOT_OPENED if the drm session cannot be found
     */
    void setPlaybackId(in byte[] sessionId, in String playbackId);

    /**
     * Write a property byte array value given the property name
     *
     * @param propertyName the name of the property
     * @param value the value to write
     *
     * @return (implicit) the status of the call:
     *     BAD_VALUE if the property name is invalid
     *     ERROR_DRM_CANNOT_HANDLE if the property is not supported
     *     ERROR_DRM_INVALID_STATE if the HAL is in a state where the
     *         property cannot be set
     */
    void setPropertyByteArray(in String propertyName, in byte[] value);

    /**
     * Write a property string value given the property name
     *
     * @param propertyName the name of the property
     * @param value the value to write
     *
     * @return (implicit) status of the call:
     *     BAD_VALUE if the property name is invalid
     *     ERROR_DRM_CANNOT_HANDLE if the property is not supported
     *     ERROR_DRM_INVALID_STATE if the HAL is in a state where the
     *         property cannot be set
     */
    void setPropertyString(in String propertyName, in String value);

    /**
     * Compute a signature over the provided message using the mac algorithm
     * specified by setMacAlgorithm and the key selected by keyId and return
     * the signature.
     *
     * @param sessionId the session id the call applies to
     * @param keyId the ID of the key to use for decryption
     * @param message the message to compute a signature over
     *
     * @return signature computed over the message
     *     Implicit error codes:
     *       + ERROR_DRM_SESSION_NOT_OPENED if the session is not opened
     *       + BAD_VALUE if any parameters are invalid
     *       + ERROR_DRM_INVALID_STATE if the HAL is in a state where the
     *             sign operation cannot be performed.
     */
    byte[] sign(in byte[] sessionId, in byte[] keyId, in byte[] message);

    /**
     * Compute an RSA signature on the provided message using the specified
     * algorithm.
     *
     * @param sessionId the session id the call applies to
     * @param algorithm the signing algorithm, such as "RSASSA-PSS-SHA1"
     *     or "PKCS1-BlockType1"
     * @param message the message to compute the signature on
     * @param wrappedKey the private key returned during provisioning as
     *     returned by provideProvisionResponse.
     *
     * @return signature computed over the message
     *     Implicit error codes:
     *       + BAD_VALUE if any parameters are invalid
     *       + ERROR_DRM_INVALID_STATE if the HAL is in a state where the
     *             signRSA operation operation cannot be performed
     *       + ERROR_DRM_SESSION_NOT_OPENED if the session is not opened
     */
    byte[] signRSA(
            in byte[] sessionId, in String algorithm, in byte[] message,
            in byte[] wrappedkey);

    /**
     * Compute a hash of the provided message using the mac algorithm specified
     * by setMacAlgorithm and the key selected by keyId, and compare with the
     * expected result.
     *
     * @param sessionId the session id the call applies to
     * @param keyId the ID of the key to use for decryption
     * @param message the message to compute a hash of
     * @param signature the signature to verify
     *
     * @return true if the signature is verified positively, false otherwise.
     *     Implicit error codes:
     *       + ERROR_DRM_SESSION_NOT_OPENED if the session is not opened
     *       + BAD_VALUE if any parameters are invalid
     *       + ERROR_DRM_INVALID_STATE if the HAL is in a state where the
     *             verify operation cannot be performed.
     */
    boolean verify(
            in byte[] sessionId, in byte[] keyId, in byte[] message,
            in byte[] signature);

}
