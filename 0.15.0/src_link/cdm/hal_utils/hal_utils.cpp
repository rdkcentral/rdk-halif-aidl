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

#include <string>
#include "hal_utils.h"

std::string HALUTIL_GetModuleName(const std::string& filePath)
{
    // Take the full path and remove the filename
    std::string module = filePath;
    size_t lastSlash = module.find_last_of("/");
    if(lastSlash != std::string::npos) {
        module = module.substr(0, lastSlash);
    }
    else {
        module = "";
    }

    // Remove the root path leaving only the module name
    size_t secondLastSlash = module.find_last_of("/");
    if(secondLastSlash != std::string::npos) {
        module = module.substr(secondLastSlash + 1);
    }

    return module;
}
    