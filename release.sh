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
# All release logic lives in scripts/release.sh. This top-level file is a
# thin pass-through so the documented `./release.sh` command keeps working
# and routes to the single source of truth.
#
# Usage (forwards to scripts/release.sh):
#   ./release.sh                     Read-only plan — next version and the
#                                    bump per module.
#   ./release.sh stage <module>|all  Write the release artefacts.
#   ./release.sh --apply [--commit]  Cut release/X.Y.Z from them.
#   ./release.sh --complete          Finish: tag via git flow, push, publish.
#   ./release.sh --help              scripts/release.sh usage.
#
set -euo pipefail
REPO_ROOT="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")" && pwd)"
exec "${REPO_ROOT}/scripts/release.sh" "$@"
