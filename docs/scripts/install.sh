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
MY_DIR="$(dirname ${MY_PATH})"
VENV_NAME="python_venv"
DOCS_DIR="${MY_DIR}/.."
VENV_DIR="${DOCS_DIR}/${VENV_NAME}"
EXTERNAL_CONTENT_DIR="${DOCS_DIR}/external_content"

NO_COLOR="\e[0m"
RED="\e[0;31m"
CYAN="\e[0;36m"
YELLOW="\e[1;33m"
GREEN="\e[0;32m"
RED_BOLD="\e[1;31m"
BLUE_BOLD="\e[1;34m"
YELLOW_BOLD="\e[1;33m"

# REMOVED: set -e 
# Reason: 'set -e' kills the interactive shell when sourced. 
# We use explicit error checking (|| return 1) instead.

function ECHO() { echo -e "$*"; }
function INFO() { ECHO "${GREEN}$*${NO_COLOR}"; }
function WARNING() { ECHO "${YELLOW_BOLD}Warning: ${YELLOW}$*${NO_COLOR}" > /dev/stderr; }

function ERROR()
{
    ECHO "${RED_BOLD}ERROR: ${RED}$*${NO_COLOR}" 
    return 1
}

function install_pip_requirements() {
    local requirements_file="$1"
    local requirements_sha_dir="${VENV_DIR}/requirements"
    local requirements_sha_file="${requirements_sha_dir}${requirements_file}.sha256"

    if [ ! -f "${requirements_file}" ]; then
        WARNING "No ${requirements_file} found"
        return 0
    fi

    INFO "install_pip_requirements( ${requirements_file} )"
    local requirements_file_dir=$(dirname "${requirements_sha_file}")

    # Explicit error handling for mkdir
    mkdir -p "${requirements_sha_dir}" || { ERROR "Failed to create dir: ${requirements_sha_dir}"; return 1; }
    mkdir -p "${requirements_file_dir}" || { ERROR "Failed to create dir: ${requirements_file_dir}"; return 1; }

    local current_sha=$(sha256sum "${requirements_file}" | awk '{print $1}')

    if [ -f "${requirements_sha_file}" ]; then
        local stored_sha=$(cat "${requirements_sha_file}")
        if [ "${current_sha}" == "${stored_sha}" ]; then
            INFO "SHA matches, skipping pip install."
            return 0
        else
            INFO "SHA mismatch. Reinstalling."
        fi
    else
        INFO "No SHA file found. Installing and creating one."
    fi

    # Pip install with error check
    if pip install -r "${requirements_file}" >/dev/null 2>&1; then
        INFO "pip install completed"
        echo "${current_sha}" > "${requirements_sha_file}" || { ERROR "Failed to write SHA file"; return 1; }
        return 0
    else
        # Capture the output to show the user why it failed
        ERROR "pip install failed. Running again without silence to show error:"
        pip install -r "${requirements_file}"
        return 1
    fi
}

function clone_repo()
{
    local repo_url="$1"
    local path="$2"
    local version="$3"
    local message="${4:-Cloning repo}"

    [ -z "${repo_url}" ] && { ERROR "clone_repo: Missing URL"; return 1; }
    [ -z "${version}" ] && { ERROR "clone_repo: Missing version"; return 1; }

    if [[ ! -z "${path}" ]]; then
        if [[ ! -d "${path}" ]]; then
            INFO "git clone ${repo_url} @ ${version} ${CYAN}${message}${NO_COLOR}"
            
            # Explicit error handling for git operations
            git clone ${repo_url} "${path}" > /dev/null 2>&1 || { ERROR "Git clone failed for ${repo_url}"; return 1; }
            
            pushd ${path} > /dev/null || { ERROR "Failed to enter directory ${path}"; return 1; }
            git checkout ${version} > /dev/null 2>&1 || { ERROR "Git checkout failed for version ${version}"; popd > /dev/null; return 1; }
            popd > /dev/null
        fi
    fi
}

function setup_and_enable_venv()
{
    # Create venv if missing
    if [[ ! -d "$VENV_DIR" ]]; then
        ECHO "Creating Virtual environment ${YELLOW}'$VENV_NAME'${NO_COLOR}"

        # Try normal venv first, capturing errors
        if ! python3 -m venv "$VENV_DIR" 2>venv_error.log; then
            if grep -qi "ensurepip" venv_error.log 2>/dev/null; then
                WARNING "python3 -m venv failed due to missing ensurepip."
                WARNING "Retrying with --without-pip (Ubuntu 20 style)..."
                if ! python3 -m venv --without-pip "$VENV_DIR"; then
                    ERROR "Failed to create python venv (even with --without-pip). See venv_error.log"
                    return 1
                fi
            else
                ERROR "Failed to create python venv. See venv_error.log"
                return 1
            fi
        fi

        ECHO "Virtual environment created."
    fi

    # Activate if not active
    if [[ -z "$VIRTUAL_ENV" ]]; then
        if [ -f "$VENV_DIR/bin/activate" ]; then
            # shellcheck disable=SC1090
            source "$VENV_DIR/bin/activate" || { ERROR "Failed to activate venv"; return 1; }
        else
            ERROR "Venv directory exists but cannot find bin/activate"
            return 1
        fi
    fi

    # Make sure pip exists in the venv
    if ! command -v pip >/dev/null 2>&1; then
        WARNING "pip not found in virtualenv, trying to bootstrap pip..."
        if ! python -m ensurepip --upgrade >/dev/null 2>&1; then
            WARNING "ensurepip not available inside venv."
            if command -v pip3 >/dev/null 2>&1; then
                WARNING "Using system pip3 to bootstrap pip..."
                pip3 install --upgrade pip
            else
                ERROR "No pip available. On Ubuntu, run: sudo apt install python3-venv python3-pip"
                return 1
            fi
        fi
    fi
}

# --- Main Execution Flow ---

QUIET=0
if [ "$1" == "--quiet" ]; then
    QUIET=1
fi

# 1. Setup Venv
setup_and_enable_venv || return 1

# 2. Clone Repos
mkdir -p ${EXTERNAL_CONTENT_DIR} || { ERROR "Failed to create ${EXTERNAL_CONTENT_DIR}"; return 1; }
clone_repo "https://github.com/rdkcentral/ut-core.wiki.git" "${EXTERNAL_CONTENT_DIR}/ut-core-wiki" "main" || return 1

# 3. Install Pip Req
install_pip_requirements ${DOCS_DIR}/requirements.txt || return 1

if [ ${QUIET} == 0 ]; then
    INFO "Run "${YELLOW}./build_docs.sh${NO_COLOR}" to generate the documentation"
fi