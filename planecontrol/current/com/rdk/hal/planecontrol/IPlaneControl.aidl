/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
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
package com.rdk.hal.planecontrol;
import com.rdk.hal.planecontrol.IPlaneControlListener;
import com.rdk.hal.planecontrol.Capabilities;
import com.rdk.hal.planecontrol.SourcePlaneMapping;
import com.rdk.hal.planecontrol.Property;
import com.rdk.hal.planecontrol.PropertyKVPair;
import com.rdk.hal.PropertyValue;
 
/** 
 *  @brief     Plane Control HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
 
@VintfStability
interface IPlaneControl
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "PlaneControl";

    /**
     * Gets the platform plane resources and their capabilities.
     * 
     * This function can be called at any time and is not dependant on any Plane Control state.
     * The returned value is not allowed to change between calls.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns Capabilities[] array of plane resource instance capabilities.
     */
    Capabilities[] getCapabilities();
 
    /**
     * Gets the native graphics window handle to couple with an EGL display.
     * 
     * This function can be called multiple times, but will return the same native graphics window
     * handle on successive calls.  No reference counting is performed.
     * 
     * @param[in] planeResourceIndex    The plane resource index.
     * 
     * @returns Native graphics window handle.
     * 
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid value.
     * 
     * @see releaseNativeGraphicsWindowHandle()
     */
    long getNativeGraphicsWindowHandle(in int planeResourceIndex);
 
    /**
     * Releases the native graphics window handle previously returned from a call to getNativeGraphicsWindowHandle().
     * 
     * @param[in] planeResourceIndex    The plane resource index.
     * @param[in] nativeWindowHandle    A native window handle.
     * 
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid value.
     * 
     * @see getNativeGraphicsWindowHandle()
     */
    void releaseNativeGraphicsWindowHandle(in int planeResourceIndex, in long nativeWindowHandle);

    /**
     * Flips the latest swapped graphics buffer (e.g. provided by eglSwapBuffers) to the graphics plane for display.
     * 
     * @note Should be redundant if EGL can flip automatically during buffer swaps on all platforms.
     * 
     * @param[in] planeResourceIndex        The graphics plane resource index.
     * 
     * @returns boolean
     * @retval true     The flip was performed successfully.
     * @retval false    Invalid graphics plane resource index.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid value.
     *
     * @see getNativeGraphicsWindowHandle()
     */
    boolean flipGraphicsBuffer(in int planeResourceIndex);
 
    /**
     * Sets the destination plane for one or more video sources.
     * 
     * This function allows multiple video [source -> plane] mappings to be changed together.
     * Operations such as main and PIP video swaps can be performed using this call.
     * 
     * To unmap a source from its plane, map it to a `destinationPlaneIndex` of -1.
     * 
     * If a source type and source index appear multiple times in the mapping list then the call fails.
     * If a plane index appears multiple times in the mapping list then the call fails.
     * If a plane index is already mapped to a source, then the exception status ``binder::Status EX_ILLEGAL_STATE`` is returned.
     *
     * @param[in] listSourcePlaneMapping    An array of video source to video plane mappings.
     *
     * @return boolean
     * @retval true     The mapping was updated.
     * @retval false    One or more mappings were invalid.
     * 
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid value.
     *
     * @see getVideoSourceDestinationPlaneMapping()
     */
    boolean setVideoSourceDestinationPlaneMapping(in SourcePlaneMapping[] listSourcePlaneMapping);
  
    /**
     * Gets the video source to plane mapping for all video planes.
     * 
     * This function always returns an array with one element for each video plane.
     * If a video plane has no source mapped, then `SourceType.NONE` is mapped to it.
     * 
     * @returns SourcePlaneMapping[]    An array of video source to video plane mappings.
     * 
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @see setVideoSourceDestinationPlaneMapping()
     */
    SourcePlaneMapping[] getVideoSourceDestinationPlaneMapping();
  
    /**
     * Gets a property of a plane.
     * 
     * @param[in] planeResourceIndex    The plane resource index.
     * @param[in] property              Property enum.
     * 
     * @returns PropertyValue or null on invalid parameter.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid parameter value.
     *
     * @see setProperty(), getPropertyMulti()
     */
    @nullable PropertyValue getProperty(in int planeResourceIndex, in Property property);

    /**
     * Sets a property of a plane.
     * 
     * @param[in] planeResourceIndex    The plane resource index.
     * @param[in] property              Property enum.
     * @param[in] propertyValue         Property value.
     * 
     * @returns boolean
     * @retval true     Property was set successfully.
     * @retval false    Invalid plane index, property or property value parameter.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid value. 
     *
     * @see getProperty(), setPropertyMultiAtomic()
     */
    boolean setProperty(in int planeResourceIndex, in Property property, in PropertyValue propertyValue);

    /**
     * Gets multiple properties for a plane.
     *
     * Retrieves values for a list of property keys on the specified plane.
     *
     * Input `properties` is a non-null array of `Property` keys. Each key must be a
     * valid enum value; unknown or out-of-range values are treated as invalid.
     *
     * Output `propertyKVList` returns one `PropertyKVPair` per requested key, with
     * the same ordering as `properties`. For each pair, the `property` field echoes
     * the requested key and `propertyValue` is populated on success.
     *
     * Error handling and return semantics:
     * - Passing an empty `properties` array is an error.
     * - If any key in `properties` is invalid, no values are populated and the call
     *   returns `false` with `EX_ILLEGAL_ARGUMENT`.
     * - If a required out-parameter is null (e.g. `propertyKVList`), the call fails
     *   with `EX_NULL_POINTER`.
     *
     * @param[in] planeResourceIndex    The plane resource index.
     * @param[in] properties            Non-empty list of property keys to query.
     * @param[out] propertyKVList       Returned key/value pairs corresponding to `properties`.
     *
     * @returns boolean
     * @retval true                     All property values were returned successfully.
     * @retval false                    One or more keys are invalid, or input list is empty.
     *
     * @exception binder::Status::Exception::EX_NONE             Success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT Invalid plane index, property key(s) or empty input list.
     * @exception binder::Status::Exception::EX_NULL_POINTER     Null out-parameter.
     *
     * @see getProperty(), setPropertyMultiAtomic()
     */
    boolean getPropertyMulti(in int planeResourceIndex, in Property[] properties, out PropertyKVPair[] propertyKVList);
  
    /**
     * Sets multiple properties atomically for a plane.
     * 
     * For example, the `X`, `Y`, `WIDTH` and `HEIGHT` properties can be set in a single call.
     * Properties must only appear once in the list.
     * 
     * @param[in] planeResourceIndex    The plane resource index.
     * @param[in] propertyKVList        Array of property key-value pairs.
     * 
     * @returns boolean
     * @retval true     Properties were set successfully.
     * @retval false    Invalid plane index, property or property value parameter.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid parameters.
     * @exception binder::Statu::Exception::EX_NULL_POINTER for Null object. 
     *
     * @see setProperty(), getPropertyMulti()
     */
    boolean setPropertyMultiAtomic(in int planeResourceIndex, in PropertyKVPair[] propertyKVList);
 
    /**
     * Registers a callback listener for events generated by the Plane Control.
     *
     * An `IPlaneControlListener` can only be registered once and will fail on subsequent
     * registration attempts.
     *
     * @param[in] listener              IPlaneControlListener interface.
     * 
     * @return boolean
     * @retval true     The event listener was registered.
     * @retval false    The event listener is already registered.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object. 
     *
     * @see unregisterListener()
     */
    boolean registerListener(in IPlaneControlListener listener);
 
    /**
     * Unregisters a callback listener for events generated by the Plane Control.
     *
     * @param[in] listener              Reference to IPlaneControlListener interface.
     *
     * @return boolean
     * @retval true     The event listener was unregistered.
     * @retval false    The event listener was not found registered.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     *
     * @see registerListener()
     */
    boolean unregisterListener(in IPlaneControlListener listener);
}
