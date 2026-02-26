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
package com.rdk.hal.broadcast.frontend;
 
/** 
 * @brief Frontend component states.
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
 
@VintfStability
@Backing(type="int")
enum State {
    /** 
     * Initial state entered when the service connection is established. 
     */
    CLOSED = 1,
    
    /** 
     * The Frontend is transitioning from closed to ready state. 
     */
    OPENING = 2,
    
    /** 
     * The Frontend is open and ready to start, but in a stopped state. 
     */
    READY = 3,
    
    /** 
     * The Frontend is transitioning from ready to started state. 
     */
    STARTING = 4,
    
    /** 
     * The opened Frontend has been started. 
     */
    STARTED = 5,
    
    /** 
     * The started Frontend is stopping and flushing its internal state.
     * Once flushed, the Frontend enters the ready state. 
     */
    STOPPING = 7,
    
    /** 
     * The Frontend is transitioning from ready to closed state. 
     */
    CLOSING = 8
}
