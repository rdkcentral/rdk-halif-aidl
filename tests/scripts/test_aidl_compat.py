#!/usr/bin/env python3

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

"""Tests for scripts/aidl_compat.py: the class it gives small, known changes.

Needs the aidl compiler (./build_binder.sh); set AIDL to use another one.
Run: python3 -m unittest discover -s tests/scripts
"""

import json
import os
import subprocess
import sys
import tempfile
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SCRIPT = os.path.join(ROOT, "scripts", "aidl_compat.py")
AIDL = os.environ.get("AIDL", os.path.join(ROOT, "build-tools", "linux_binder_idl",
                                           "out", "host", "bin", "aidl"))

ENUM = """package com.x;
@VintfStability @Backing(type="int")
enum E {
    A = 0,
    %s
}
"""
PARCEL = """package com.x;
@VintfStability
parcelable P {
    %s
}
"""
IFACE = """package com.x;
@VintfStability
interface I {
    %s
}
"""


@unittest.skipUnless(os.access(AIDL, os.X_OK), "aidl compiler not built")
class ChangeClass(unittest.TestCase):

    def verdict(self, old, new):
        """aidl_compat.py's result for one component, old -> new sources."""
        with tempfile.TemporaryDirectory() as tmp:
            for side, files in (("old", old), ("new", new)):
                pkg = os.path.join(tmp, side, "comp", "current", "com", "x")
                os.makedirs(pkg)
                for name, body in files.items():
                    with open(os.path.join(pkg, name + ".aidl"), "w") as fh:
                        fh.write(body)
            r = subprocess.run([sys.executable, SCRIPT, "--repo", os.path.join(tmp, "new"),
                                "--old-repo", os.path.join(tmp, "old"), "--aidl", AIDL,
                                "comp", "current"], capture_output=True, text=True, check=True)
            return json.loads(r.stdout)

    def assertClass(self, old, new, expected):
        v = self.verdict(old, new)
        self.assertEqual(v["recommended"], expected, v)

    # Additive: minor

    def test_appended_field_is_minor(self):
        self.assertClass({"P": PARCEL % "int a;\n    int b;"},
                         {"P": PARCEL % "int a;\n    int b;\n    int c;"}, "minor")

    def test_first_field_on_empty_parcelable_is_minor(self):
        self.assertClass({"P": PARCEL % ""}, {"P": PARCEL % "int a;"}, "minor")

    def test_deprecated_enum_value_is_minor(self):
        self.assertClass({"E": ENUM % "M = 1000,"},
                         {"E": ENUM % "/** @deprecated use B */ M = 1000,\n    B = 1001,"}, "minor")

    def test_deprecated_method_is_minor(self):
        self.assertClass({"I": IFACE % "void f();"},
                         {"I": IFACE % "/** @deprecated use g */ void f();\n    void g();"}, "minor")

    def test_deprecated_field_is_minor(self):
        self.assertClass({"P": PARCEL % "int a;"},
                         {"P": PARCEL % "/** @deprecated use b */ int a;\n    int b;"}, "minor")

    def test_unchanged_is_none(self):
        self.assertClass({"P": PARCEL % "int a;"}, {"P": PARCEL % "int a;"}, "none")

    # Breaking: still major

    def test_removed_enum_value_is_major(self):
        self.assertClass({"E": ENUM % "M = 1000,"}, {"E": ENUM % ""}, "major")

    def test_removed_field_is_major(self):
        self.assertClass({"P": PARCEL % "int a;\n    int b;"}, {"P": PARCEL % "int a;"}, "major")

    def test_retyped_field_is_major(self):
        self.assertClass({"P": PARCEL % "int a;"}, {"P": PARCEL % "long a;"}, "major")

    def test_inserted_field_is_major(self):
        self.assertClass({"P": PARCEL % "int a;\n    int b;"},
                         {"P": PARCEL % "int a;\n    int c;\n    int b;"}, "major")

    def test_changed_method_signature_is_major(self):
        self.assertClass({"I": IFACE % "void f();"}, {"I": IFACE % "void f(int x);"}, "major")


if __name__ == "__main__":
    unittest.main()
