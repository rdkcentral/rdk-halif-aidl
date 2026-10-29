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
"""Header comparison in aidl_compat.py. Usage: python3 -m unittest discover scripts/tests"""

import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import aidl_compat  # noqa: E402

HEADER = """
class Foo : public ::android::Parcelable {
public:
  int32_t a = 0;
%s
  inline bool operator==(const Foo& _rhs) const {
    return std::tie(%s) == std::tie(%s);
  }
  inline bool operator<(const Foo& _rhs) const {
    return std::tie(%s) < std::tie(%s);
  }
};
"""


def header(fields):
    lhs = ", ".join(fields)
    rhs = ", ".join("_rhs." + f for f in fields)
    members = "\n".join("  int32_t %s = 0;" % f for f in fields[1:])
    return HEADER % (members, lhs, rhs, lhs, rhs)


class CompareHeaderTest(unittest.TestCase):
    def classify(self, old, new):
        with tempfile.TemporaryDirectory() as d:
            paths = []
            for name, text in (("old.h", old), ("new.h", new)):
                p = os.path.join(d, name)
                with open(p, "w") as fh:
                    fh.write(text)
                paths.append(p)
            evidence = []
            return aidl_compat.compare_header(paths[0], paths[1], "Foo.h", evidence), evidence

    def test_appended_field_is_minor(self):
        verdict, evidence = self.classify(header(["a"]), header(["a", "b"]))
        self.assertEqual(verdict, "minor", evidence)

    def test_removed_field_is_major(self):
        verdict, _ = self.classify(header(["a", "b"]), header(["a"]))
        self.assertEqual(verdict, "major")

    def test_identical_is_none(self):
        verdict, _ = self.classify(header(["a", "b"]), header(["a", "b"]))
        self.assertEqual(verdict, "none")


if __name__ == "__main__":
    unittest.main()
