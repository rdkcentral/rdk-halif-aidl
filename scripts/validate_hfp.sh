#!/usr/bin/env bash

#/**
# * Copyright 2026 RDK Management
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

# Validate HAL Feature Profiles (HFPs) against the Pykwalify schema generated
# beside each reference HFP.
#
#   scripts/validate_hfp.sh                      validate every reference HFP
#   scripts/validate_hfp.sh my-hfp.yaml ...      validate product HFPs; the
#                                                schema is found by component
#   scripts/validate_hfp.sh --schema S f.yaml    validate f.yaml against S
#   scripts/validate_hfp.sh --release 0.3.0.0 f.yaml
#                                                use the schema frozen in that
#                                                release of the component
#   scripts/validate_hfp.sh --generate           regenerate every schema from
#                                                its HFP and the module's AIDL
#   scripts/validate_hfp.sh --check              fail if a schema is out of date
#
# The first run creates a Python environment in build/hfp-venv holding
# pykwalify.

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
VENV="${REPO_ROOT}/build/hfp-venv"
PYKWALIFY="pykwalify==1.8.0"

if [[ ! -x "${VENV}/bin/python" ]] || ! "${VENV}/bin/python" -c "import pykwalify" 2>/dev/null; then
    echo "Creating ${VENV#${REPO_ROOT}/} with ${PYKWALIFY}" >&2
    mkdir -p "${REPO_ROOT}/build"
    python3 -m venv "${VENV}"
    "${VENV}/bin/python" -m pip install --quiet --disable-pip-version-check "${PYKWALIFY}"
fi

case "${1:-}" in
    --generate) shift; cmd=(generate) ;;
    --check)    shift; cmd=(check) ;;
    *)          cmd=(validate) ;;
esac

exec "${VENV}/bin/python" "${REPO_ROOT}/scripts/hfp_schema.py" "${cmd[@]}" "$@"
