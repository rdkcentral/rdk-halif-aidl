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
HELPER = """#pragma once
#include <cstdint>
class IHelper
{
%s:
    struct Map {
        uint32_t offset;
    };
    virtual ~IHelper() = default;
};
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
                comp = os.path.join(tmp, side, "comp", "current")
                pkg = os.path.join(comp, "com", "x")
                os.makedirs(pkg)
                for name, body in files.items():
                    # A name ending .h is a hand-authored header at the
                    # module root; anything else is an .aidl source.
                    path = (os.path.join(comp, name) if name.endswith(".h")
                            else os.path.join(pkg, name + ".aidl"))
                    with open(path, "w") as fh:
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

    def test_hand_header_member_made_private_is_major(self):
        self.assertClass({"P": PARCEL % "int a;", "helper.h": HELPER % "public"},
                         {"P": PARCEL % "int a;", "helper.h": HELPER % "private"}, "major")

    def test_hand_header_member_made_private_with_two_bases_is_major(self):
        # The class head is split at the comma between its bases; it must
        # still open a class scope.
        bases = "class IHelper : public Base1, public Base2"
        old = "struct Base1 {};\nstruct Base2 {};\n" + (HELPER % "public").replace("class IHelper", bases)
        new = "struct Base1 {};\nstruct Base2 {};\n" + (HELPER % "private").replace("class IHelper", bases)
        self.assertClass({"P": PARCEL % "int a;", "helper.h": old},
                         {"P": PARCEL % "int a;", "helper.h": new}, "major")

    def test_hand_header_unnamed_struct_member_made_private_is_major(self):
        # An unnamed struct body starts public, whatever access encloses it.
        body = ("class IHelper\n{\n    typedef struct {\n        %sint value;\n    } Data;\n"
                "public:\n    Data data;\n};\n")
        self.assertClass({"P": PARCEL % "int a;", "helper.h": body % ""},
                         {"P": PARCEL % "int a;", "helper.h": body % "private:\n        "}, "major")

    def test_first_constant_on_interface_is_minor(self):
        # aidl writes the first constant as an inline enum, whose closing
        # brace sits on the constant itself.
        self.assertClass({"I": IFACE % "void f();"},
                         {"I": IFACE % "const int ADDED = 1;\n    void f();"}, "minor")

    def test_hand_header_label_repeated_is_none(self):
        # Every member keeps its access; only where public: is written
        # changes.
        repeated = (HELPER % "public").replace("    virtual", "public:\n    virtual")
        self.assertClass({"P": PARCEL % "int a;", "helper.h": HELPER % "public"},
                         {"P": PARCEL % "int a;", "helper.h": repeated}, "none")

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
