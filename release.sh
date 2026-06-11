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
# *     http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#** ******************************************************************************
#
# release.sh — repo-root entry point.
#
# All release logic now lives in scripts/release.sh: version computation,
# dry-run vs --apply, snapshot creation, mkdocs nav, branch + tag. This
# top-level file is a thin pass-through so the documented `./release.sh`
# command keeps working and routes to the single source of truth.
#
# Usage (forwards to scripts/release.sh):
#   ./release.sh                 Dry-run — auto-detects next release version
#                                from the latest tag, prints the exact
#                                --apply command to run.
#   ./release.sh --apply         Apply the release.
#   ./release.sh --help          scripts/release.sh usage.
#
set -euo pipefail
REPO_ROOT="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")" && pwd)"
exec "${REPO_ROOT}/scripts/release.sh" "$@"
