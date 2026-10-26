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

# Make the root of a checked-out gh-pages tree hold only what mike publishes,
# and a 404.html that sends a path with no version to the same page in the
# default version. Run by `build_docs.sh preview` and `release` (#831).
#
#   tidy_pages.py <gh-pages tree> <site path prefix> <default version>
#
# Kept at the root: every version and alias directory in versions.json,
# versions.json, index.html (mike's redirect to the default), .nojekyll, CNAME
# and 404.html. Everything else is a page from an unversioned deploy, which
# would otherwise answer a path that has no version.

import json
import os
import shutil
import sys

TREE, PREFIX, DEFAULT = sys.argv[1], sys.argv[2], sys.argv[3]
KEEP_FILES = {".git", "versions.json", "index.html", ".nojekyll", "CNAME", "404.html"}

NOT_FOUND = """<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>Page not found</title>
<script>
// A path with no version opens the same page in the default version.
(function () {
  var prefix = __PREFIX__, fallback = __DEFAULT__, versions = __VERSIONS__;
  var path = window.location.pathname;
  if (path.indexOf(prefix) !== 0) { return; }
  var rest = path.slice(prefix.length);
  if (rest === "" || versions.indexOf(rest.split("/")[0]) !== -1) { return; }
  window.location.replace(prefix + fallback + "/" + rest + window.location.search + window.location.hash);
})();
</script>
</head>
<body>
<p>Page not found. <a href="__HOME__">Open the documentation home page.</a></p>
</body>
</html>
"""


def main():
    with open(os.path.join(TREE, "versions.json"), encoding="utf-8") as f:
        published = json.load(f)
    versions = sorted({v["version"] for v in published} |
                      {a for v in published for a in v.get("aliases", [])})

    removed = []
    for entry in sorted(os.listdir(TREE)):
        if entry in KEEP_FILES or entry in versions:
            continue
        path = os.path.join(TREE, entry)
        if os.path.isdir(path) and not os.path.islink(path):
            shutil.rmtree(path)
        else:
            os.remove(path)
        removed.append(entry)

    page = (NOT_FOUND
            .replace("__PREFIX__", json.dumps(PREFIX))
            .replace("__DEFAULT__", json.dumps(DEFAULT))
            .replace("__VERSIONS__", json.dumps(versions))
            .replace("__HOME__", PREFIX))
    with open(os.path.join(TREE, "404.html"), "w", encoding="utf-8") as f:
        f.write(page)

    for entry in removed:
        print(f"[INFO]   removed unversioned /{entry}")


if __name__ == "__main__":
    main()
