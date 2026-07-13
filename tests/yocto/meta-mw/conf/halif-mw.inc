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

# EXAMPLE build-configuration include for the middleware build. Require it from
# your local.conf / distro:
#   require ${TOPDIR}/../rdk-halif-aidl/tests/yocto/meta-mw/conf/halif-mw.inc
#
# Deliberately pins an OLDER cohort than the vendor example (0.1.x vs 0.2.x) to
# show the two configurations diverging from the same rdk-halif recipe.

HALIF_ROLE = "mw"
HALIF_LIBDIR = "${libdir}/halif"
HALIF_INCDIR = "${includedir}/halif"

# Pinning a base component (common) to an older version constrains the set to
# that version's closure, so this configuration builds the compatible subset.
HALIF_COMPONENTS = "avclock common"

HALIF_VERSIONS_FILE = "${THISDIR}/versions_mw.yaml"
