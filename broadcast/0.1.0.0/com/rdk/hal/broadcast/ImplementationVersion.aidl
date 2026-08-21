/*
 * If not stated otherwise in this file or this component's LICENSE file the following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 */
package com.rdk.hal.broadcast;

/**
 * HAL Implementation Version structure.
 *
 * This version has to be filled by the service implementation and has to follow semantic versioning. It is not bound to
 * the interface version.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
parcelable ImplementationVersion {
    @VintfStability
    parcelable Version {
        /** Major version number. */
        int major;
        /** Minor version number. */
        int minor;
        /** Patch version number. */
        int patch;
    }

    /** Implementation version. */
    Version version;

    /**
     * Implementation name.
     *
     * This is a implementation specific string, that has no semantics attached to it. The only requirements are that it
     * is unique for each implementation, allows to identify the implementation and should not change between releases
     * of the same implementation.
     */
    @utf8InCpp String name;

    /** Reserved for future use. */
    ParcelableHolder extension;
}
