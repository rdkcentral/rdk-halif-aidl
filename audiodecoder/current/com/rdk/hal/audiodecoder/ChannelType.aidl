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
package com.rdk.hal.audiodecoder;

/**
 *  @brief     Channel Types.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
@Backing(type = "int")
enum ChannelType {
    /** Single mono channel. */
    MONO = 0,
    /** Front left channel. */
    FRONT_LEFT = 1,
    /** Front right channel. */
    FRONT_RIGHT = 2,
    /** Front centre channel. */
    FRONT_CENTER = 3,
    /** Low-frequency effects channel. */
    LFE = 4,
    /** Side left channel. */
    SIDE_LEFT = 5,
    /** Side right channel. */
    SIDE_RIGHT = 6,
    /** Upper left channel. */
    UP_LEFT = 7,
    /** Upper right channel. */
    UP_RIGHT = 8,
    /** Back left channel. */
    BACK_LEFT = 9,
    /** Back right channel. */
    BACK_RIGHT = 10,
    /** Back centre channel. */
    BACK_CENTER = 11,
}
