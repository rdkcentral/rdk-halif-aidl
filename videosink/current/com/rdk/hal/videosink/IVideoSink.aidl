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
package com.rdk.hal.videosink;
import com.rdk.hal.videosink.Capabilities;
import com.rdk.hal.videosink.IVideoSinkController;
import com.rdk.hal.videosink.IVideoSinkControllerListener;
import com.rdk.hal.videosink.IVideoSinkEventListener;
import com.rdk.hal.videosink.Property;
import com.rdk.hal.PropertyValue;
import com.rdk.hal.videosink.State;
import com.rdk.hal.metrics.MetricSnapshot;
import com.rdk.hal.videosink.Metric;

/**
 *  @brief     Video Sink HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */

@VintfStability
interface IVideoSink
{
    /** Video Sink resource ID type */
    @VintfStability
    parcelable Id {
        /** The undefined ID value. */
        const int UNDEFINED = -1;

        /** The actual resource ID */
        int value;
    }

    /**
     * Gets the capabilities for this Video Sink.
     *
     * This function can be called at any time and is not dependant on any Video Sink state.
     * The returned value is not allowed to change between calls.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @returns Capabilities parcelable.
     *
     */
    Capabilities getCapabilities();

    /**
     * Gets a property.
     *
     * @param[in] property              The key of a property from the Property enum.
     *
     * @returns PropertyValue or null if the property key is unknown.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT for invalid property value.
     *
     *
     * @see setProperty()
     */
    @nullable PropertyValue getProperty(in Property property);




    /**
	 * Gets the current Video Sink state.
     *
     * @returns State enum value.
	 *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     *
     * @see IVideoSinkListener.onStateChanged().
     */
    State getState();

    /**
	 * Opens the Video Sink.
     *
     * If successful the Video Sink transitions to an OPENING state and then a READY state.
     *
     * If the client that opened the `IVideoSinkController` crashes,
     * then the `IVideoSinkController` has `stop()` and `close()` implicitly called to perform clean up.
     *
     * @param[in] videoSinkControllerListener       Callback listener for controller events.
     *
     * @returns IVideoSinkController or null on error.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If the resource is not in the CLOSED state.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     *
     * @pre The resource must be in State::CLOSED.
     *
     * @see close(), IVideoSinkController.start()
     */
    @nullable IVideoSinkController open(in IVideoSinkControllerListener videoSinkControllerListener);

    /**
     * Closes the Video Sink.
     *
     * The Video Sink must be in a `READY` state before it can be closed.
     * If successful the Video Sink transitions to a `CLOSING` state and then a `CLOSED` state.
     *
     * @param[in] videoSinkController     Instance of the IVideoSinkController.
     *
     * @return boolean
     * @retval true     Successfully closed.
     * @retval false    Invalid state or unrecognised parameter.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE If instance is not in OPENED State.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     *
     *
     * @see open()
     */
    boolean close(in IVideoSinkController videoSinkController);

    /**
	 * Registers a Video Sink event listener.
     *
     * An `IVideoSinkEventListener` can only be registered once and will fail on subsequent
     * registration attempts.
     *
     * @param[in] videoSinkEventListener	    Listener object for callbacks.
     *
     * @return boolean
     * @retval true     The event listener was registered.
     * @retval false    The event listener is already registered.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     *
     *
     * @see unregisterEventListener()
     */
    boolean registerEventListener(in IVideoSinkEventListener videoSinkEventListener);

    /**
	 * Unregisters a Video Sink event listener.
     *
     * @param[in] videoSinkEventListener	    Listener object for callbacks.
     *
     * @return boolean
     * @retval true     The event listener was unregistered.
     * @retval false    The event listener was not found registered.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * @exception binder::Status::Exception::EX_NULL_POINTER for Null object.
     *
     *
     * @see registerEventListener()
     */
    boolean unregisterEventListener(in IVideoSinkEventListener videoSinkEventListener);

    /* ---------------------------------------------------------------------
     * Metrics. Appended last, and any future addition is appended after
     * these: a method's transaction ID is its declaration order, so
     * inserting one above shifts every ID below it and breaks the ABI.
     * ------------------------------------------------------------------ */

    /**
     * Gets metrics as one coherent snapshot.
     *
     * Every value in the returned snapshot is latched at the one instant the
     * snapshot records, so paired figures can never be read torn. This is an
     * obligation on the implementation, not a property to be discovered — an
     * implementation whose figures span two hardware blocks latches both.
     *
     * Passing null asks for everything this resource serves, which is the call a
     * consumer polling at a cadence should use: one round trip, one sampling
     * instant. Figures the product cannot measure are then simply absent, because
     * nothing named them.
     *
     * Passing a list asks for those keys by name, and the snapshot carries one
     * value per requested key — including a key this product cannot measure,
     * which comes back as `MetricStatus::NOT_SUPPORTED` so a caller that named a
     * figure always learns its fate. That difference is the reason to name keys
     * rather than filter the full set client-side.
     *
     * Ordering of values within a group is not significant; a caller matches on
     * `MetricValue.id` rather than on position. A value is never a sentinel: `0`
     * means it measured zero.
     *
     * @param[in] metrics             Metric keys to query, or null for every served metric.
     *
     * @returns MetricSnapshot latched at a single monotonic instant.
     *
     * @exception binder::Status::Exception::EX_NONE             Success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT An empty (but non-null) list, or an invalid metric key.
     */
    MetricSnapshot getMetrics(in @nullable Metric[] metrics);
}
