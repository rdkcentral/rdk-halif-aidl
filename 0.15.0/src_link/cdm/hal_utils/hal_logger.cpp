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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "hal_logger.h"

static bool s_VerboseLog = false;

void HALUTIL_Logger_Message(eMessageLevel level, const char* function, int line, const char * format, ...)
{
#define LOG_MESSAGE_SIZE 4096
    char logMessage[LOG_MESSAGE_SIZE];
    // Generate the log string
    va_list ap;
    va_start(ap, format);
    //snprintf(logMessage, LOG_MESSAGE_SIZE, ap);
    vsnprintf(logMessage, LOG_MESSAGE_SIZE, format, ap);
    va_end(ap);

    if(s_VerboseLog == true) {
        level = eError;
    }

    if(level < eWarning) {
        return;
    }

    // printf for now.
    FILE* fpOut = stdout;
    if(level == eError) {
        fpOut = stderr;
    }

    fprintf(fpOut, "%s(%d) : %s\n", function, line, logMessage);
    fflush(fpOut);

    return;
}

#if 1 
static void __attribute__((constructor)) HALUTIL_LogModuleInit();
static void __attribute__((destructor)) HALUTIL_LogModuleTerminate();

// This function is assigned to execute as a library init
//  using __attribute__((constructor))
static void HALUTIL_LogModuleInit()
{
    LOG(eWarning, "RDK_MEDIA Logging initialize extending logging set to %d\n", s_VerboseLog);
    // Check Latency
    FILE *f = fopen("/opt/enable_hal_media_logging", "r");
    if(f != NULL) {
        s_VerboseLog = true;
        fclose(f);
        LOG(eWarning, "/opt/enable_rdk_media_logging present, Enabling RDK_HAL_MEDIA extended logging %d", s_VerboseLog);
    }
    else {
        const char *env_log_level = getenv("HAL_MEDIA_EXTENDED_LOGGING");
        if(env_log_level != NULL && strncasecmp(env_log_level, "true", strlen("true")) == 0) {
            s_VerboseLog = true;
            LOG(eWarning, "Environment HAL_MEDIA_EXTENDED_LOGGING=true, Enabling RDK_HAL_MEDIA extended logging %d", s_VerboseLog);
        }
    }
}

// This function is assigned to execute as library unload
// using __attribute__((destructor))
static void HALUTIL_LogModuleTerminate()
{
    LOG(eWarning, "RDK_HAL_MEDIA Logging terminate\n");
}

#endif