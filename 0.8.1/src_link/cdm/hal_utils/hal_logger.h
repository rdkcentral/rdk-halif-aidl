/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2022 RDK Management
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

#define LOG(level, ...) HALUTIL_Logger_Message(level, __FUNCTION__, __LINE__, __VA_ARGS__)

typedef enum eMessageLevel_
{
    eTrace      = 0,
    eWarning    = 1,
    eError      = 2
} eMessageLevel;

void HALUTIL_Logger_Message(eMessageLevel level, const char* function, int line, const char * format, ...);
