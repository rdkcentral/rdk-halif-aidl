#!/usr/bin/env bash
#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2025 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# *
# http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#* ******************************************************************************
MY_PATH="$(realpath ${BASH_SOURCE[0]})"
SCRIPTS_DIR="$(dirname ${MY_PATH})"
DOCS_DIR="${SCRIPTS_DIR}/.."
VENV_DIR="${DOCS_DIR}/python_venv"

# Check if the script is sourced (required to activate venv in the current shell)
if [[ "${BASH_SOURCE[0]}" != "${0}" ]]; then
    
    # 1. Activate the Venv
    if [ -f "$VENV_DIR/bin/activate" ]; then
        source "$VENV_DIR"/bin/activate
        echo "Virtual environment '$VENV_DIR' activated."
    else
        # If venv doesn't exist yet, we can't activate it, but install.sh might create it.
        # We'll let install.sh handle the creation.
        echo "Virtual environment not found. install.sh will attempt to create it."
    fi

    # 2. Run the install script safely
    # We use source (.) so it runs in this shell, but we don't use set -e
    . ${SCRIPTS_DIR}/install.sh --quiet
    
    # 3. Check if install.sh succeeded
    if [ $? -ne 0 ]; then
        echo "------------------------------------------------"
        echo "⚠️  Setup encountered errors. Please check logs."
        echo "------------------------------------------------"
        # We do NOT exit here because that would close the terminal.
        # We just stop processing.
        return 1
    fi

else
    echo "Error: This script must be sourced."
    echo "Usage: source ./activate_venv.sh"
fi