#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2026 RDK Management
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

# EXAMPLE build-configuration include for the middleware build. Require it from
# your local.conf / distro:
#   require ${TOPDIR}/../rdk-halif-aidl/tests/yocto/meta-mw/conf/halif-mw.inc

HALIF_ROLE = "mw"
HALIF_LIBDIR = "${libdir}/halif"
HALIF_INCDIR = "${includedir}/halif"

# HALIF_COMPONENTS is left at its default (the full component list) and
# HALIF_VERSIONS_FILE defaults to the source's versions_released.yaml, so this
# configuration builds EVERY HAL at its released version - identical to the
# vendor build but installed to the MW destination. Point HALIF_VERSIONS_FILE at
# another manifest to build a different cohort.
