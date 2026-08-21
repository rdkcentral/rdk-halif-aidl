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
package com.rdk.hal.capture;

/**
 *  @brief     Properties of a capture session.
 *
 *  The shape of the frames a session delivers. Set in the `READY` state before
 *  `ICaptureController.start()`; the pool is built from them.
 *
 *  A capture owns its own frame size because it is an output in its own right.
 *  The size is bounded by `CaptureCapabilities.maxFrameWidth` and `maxFrameHeight`,
 *  and unless `CaptureCapabilities.resize` is true it must equal the resolution the
 *  bound source is producing.
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type="int")
enum Property {

    /** Width in pixels of the captured frame. Integer value. */
    WIDTH = 0,

    /** Height in pixels of the captured frame. Integer value. */
    HEIGHT = 1,
}
