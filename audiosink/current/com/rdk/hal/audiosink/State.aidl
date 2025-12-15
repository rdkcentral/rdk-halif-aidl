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
package com.rdk.hal.audiosink;
 
/** 
 * @brief Audio Sink component states.
 * @author Luc Kennedy-Lamb
 * @author Peter Stieglitz
 * @author Douglas Adler
 */
 
@VintfStability
@Backing(type="int")
enum State {
	/** 
	 * Initial state entered when the service connection is established. 
	 */
    CLOSED = 0,
	
	/** 
	 * The Audio Sink is transitioning from closed to ready state. 
	 */
    OPENING = 1,
	
	/** 
	 * The Audio Sink is open and ready to start, but in a stopped state. 
	 */
    READY = 2,
	
	/** 
	 * The Audio Sink is transitioning from ready to started state. 
	 */
    STARTING = 3,
	
	/** 
	 * The opened Audio Sink has been started. 
	 */
    STARTED = 4,
	
	/** 
	 * The started Audio Sink is stopping and flushing its internal state.
	 * Once flushed, the Audio Sink enters the ready state. 
	 */
    STOPPING = 5,
	
	/** 
	 * The Audio Sink is transitioning from ready to closed state. 
	 */
    CLOSING = 6
}
