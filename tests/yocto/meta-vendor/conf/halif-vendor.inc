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

# EXAMPLE build-configuration include for the vendor build. Require it from your
# local.conf / distro:
#   require ${TOPDIR}/../rdk-halif-aidl/tests/yocto/meta-vendor/conf/halif-vendor.inc

HALIF_ROLE = "vendor"
HALIF_LIBDIR = "${libdir}/halif"
HALIF_INCDIR = "${includedir}/halif"

# HALIF_COMPONENTS defaults to the full component list (halif-components.inc);
# leave it unset to build every HAL. This example subsets it to the components
# that have divergent versions, purely to show vendor/MW divergence concisely.
HALIF_COMPONENTS = "avclock common"

# Versions consumed directly from the manifest; unlisted components build latest.
HALIF_VERSIONS_FILE = "${THISDIR}/versions_vendor.yaml"
