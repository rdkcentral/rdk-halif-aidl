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
package com.rdk.hal.videosink;

/**
 *  @brief     Video Sink buffer memory type enumeration.
 *  @author    Gerald Weatherup
 *
 *  Identifies the buffer memory transport mechanisms that a Video Sink
 *  instance is able to accept for queued frames. Mirrors the
 *  `supportedMemoryTypes` field declared in the HFP (`hfp-videosink.yaml`).
 */
@VintfStability
@Backing(type="int")
enum MemoryType
{
    /** Unknown / unspecified memory type. */
    UNKNOWN = 0,

    /**
     * DMA-BUF shared memory descriptor (Linux dma-buf file descriptor).
     */
    DMABuf = 1,

    /**
     * Android NativeHandle wrapping one or more file descriptors and
     * associated integer payload, used to carry vendor-specific buffer
     * references (for example GBM/gralloc handles).
     */
    NativeHandle = 2,
}
