/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
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
package com.rdk.hal.avbuffer;

/**
 *  @brief     Names a Video Decoder instance from this interface's side.
 *
 *  Same wire layout as `IVideoDecoder.Id`: a client builds one from the `value` that
 *  `IVideoDecoder.Id` carries, and binaries built against either type interoperate.
 */
@VintfStability
parcelable VideoDecoderId {
    /** No Video Decoder is associated. */
    const int UNDEFINED = -1;

    /** The source is an external non-HAL component rather than a HAL Video Decoder. */
    const int EXTERNAL = -2;

    /** The Video Decoder resource ID. */
    int value;
}
