#!/usr/bin/env bash
#/**
# * Copyright 2025 Comcast Cable Communications Management, LLC
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
# * SPDX-License-Identifier: Apache-2.0
# */
############################################
# Script Description
## This script activates the Python virtual environment
# located in the ./docs/scripts/ directory.
############################################
set -euo pipefail
# ----------------------------------------------------------------------------
# Setup and run the install and the venv
# ----------------------------------------------------------------------------
{
  cd ./docs
  ./scripts/install.sh --quiet
  source ./scripts/activate_venv.sh
  cd ..
}
