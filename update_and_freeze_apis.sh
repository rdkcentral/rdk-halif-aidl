#!/usr/bin/env bash
#/**
# * Copyright 2024 Comcast Cable Communications Management, LLC
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
#
# This script scans the current directory tree
# for all `interface.yaml` files while skipping
# any folders listed in EXCLUDE_DIRS.
#
# For each interface found (folder name before /current/),
# it runs:
#   aidl_ops -u <interface>
#   aidl_ops -f <interface>
#
# If DRY_RUN=true, it prints the commands instead
# of executing them.
# Note :  This script is only to simplify the users life 
# and not spending time to find and run aidl_ops on the 
# interfaces with interface.yaml. 
# Once aidl repo attains stability this script can be removed.
############################################


set -euo pipefail

############################################
# User settings
############################################
EXCLUDE_DIRS=("examples")   # Add more dirs if needed

# No default — user *must* pass a value
DRY_RUN=""

# Parse arguments
for arg in "$@"; do
  case "$arg" in
    --dry-run=true)
      DRY_RUN=true
      ;;
    --dry-run=false)
      DRY_RUN=false
      ;;
    *)
      echo "Unknown or missing argument: $arg"
      echo "Usage: $0 --dry-run=true|false"
      exit 1
      ;;
  esac
done

# Check if user forgot required argument
if [[ -z "$DRY_RUN" ]]; then
  echo "Error: --dry-run=true|false is required"
  exit 1
fi
############################################

# Operating on common and videodecoder as other interfaces may be dependent on this
aidl_ops -u common
aidl_ops -f common
aidl_ops -u videodecoder
aidl_ops -f videodecoder

# Build prune arguments for find
PRUNE_ARGS=()
for dir in "${EXCLUDE_DIRS[@]}"; do
  PRUNE_ARGS+=(-path "./$dir" -prune -o)
done

# Find all interface.yaml files respecting excludes
mapfile -t yaml_files < <(
  find . "${PRUNE_ARGS[@]}" -iname "interface.yaml" -print
)

for file in "${yaml_files[@]}"; do
  # Extract interface name: ./<name>/current/interface.yaml
  interface_name="$(echo "$file" | awk -F'/' '{print $(NF-2)}')"

  echo ""
  echo "==> Processing interface: $interface_name"
  echo "    File: $file"

  if [[ "$DRY_RUN" == true ]]; then
    echo "DRY-RUN: would run: aidl_ops -u \"$interface_name\""
    echo "DRY-RUN: would run: aidl_ops -f \"$interface_name\""
  else
    aidl_ops -u "$interface_name"
    aidl_ops -f "$interface_name"
  fi
done

echo ""
echo "Completed. DRY_RUN=$DRY_RUN"
