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

#
# validate_hfp.sh — validate HAL Feature Profile files against their schemas.
#
# Each <component>/current/hfp-<component>.yaml is validated against its
# sibling <component>/current/hfp-<component>-schema.yaml. A component with
# no schema is reported as unchecked and does not fail the run.
#
# Usage:
#   scripts/validate_hfp.sh [component ...]   # default: every component
#
# Requires: python3 with pykwalify. To provision one:
#   python3 -m venv .hfpvenv && .hfpvenv/bin/pip install pykwalify
#   PYTHON=.hfpvenv/bin/python scripts/validate_hfp.sh

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PYTHON="${PYTHON:-python3}"

if ! "$PYTHON" -c "import pykwalify" >/dev/null 2>&1; then
    echo "ERROR: pykwalify is not available to ${PYTHON}." >&2
    echo "       python3 -m venv .hfpvenv && .hfpvenv/bin/pip install pykwalify" >&2
    echo "       PYTHON=.hfpvenv/bin/python scripts/validate_hfp.sh" >&2
    exit 2
fi

if [ "$#" -gt 0 ]; then
    components=("$@")
else
    mapfile -t components < <(
        find "$REPO_ROOT" -maxdepth 3 -name 'hfp-*.yaml' -path '*/current/*' \
            ! -name 'hfp-*-schema.yaml' -printf '%h\n' \
            | sed "s|^${REPO_ROOT}/||;s|/current$||" | sort -u
    )
fi

FAILED=0
UNCHECKED=0
PASSED=0

for comp in "${components[@]}"; do
    hfp="${REPO_ROOT}/${comp}/current/hfp-${comp}.yaml"
    schema="${REPO_ROOT}/${comp}/current/hfp-${comp}-schema.yaml"

    if [ ! -f "$hfp" ]; then
        echo "  ${comp}: no hfp-${comp}.yaml — skipped"
        continue
    fi
    if [ ! -f "$schema" ]; then
        echo "  ${comp}: no schema — unchecked"
        UNCHECKED=$((UNCHECKED + 1))
        continue
    fi

    if "$PYTHON" - "$hfp" "$schema" <<'PY'
import logging, sys
logging.disable(logging.CRITICAL)
from pykwalify.core import Core
try:
    Core(source_file=sys.argv[1], schema_files=[sys.argv[2]]).validate(raise_exception=True)
except Exception as exc:
    for line in str(exc).splitlines():
        line = line.strip()
        if not line.startswith("-"):
            continue
        # The final finding carries the exception's own trailing context.
        line = line.split(": Path: '/'>")[0]
        print("      " + line)
    sys.exit(1)
PY
    then
        echo "  ${comp}: OK"
        PASSED=$((PASSED + 1))
    else
        echo "  ${comp}: FAILED (above)"
        FAILED=$((FAILED + 1))
    fi
done

echo
echo "hfp validation: ${PASSED} passed, ${FAILED} failed, ${UNCHECKED} unchecked"
[ "$FAILED" -eq 0 ]
