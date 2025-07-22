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
package com.rdk.hal.avbuffer;
import com.rdk.hal.avbuffer.Pool;

/** 
 *  @brief     AV buffer pool metrics definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability 
parcelable PoolMetrics 
{
    /** Handle for a pool. */
    Pool poolHandle;

    /** Total bytes used by allocations created inside the pool. */
	int bytesUsed;

    /** Total bytes of pool storage. */
  	int bytesTotal; 
}
