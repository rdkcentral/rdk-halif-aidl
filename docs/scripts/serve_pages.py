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

# Serve a gh-pages tree the way GitHub Pages does, for `build_docs.sh preview`:
# under the site's path prefix, and with the root 404.html answering every
# missing path.
#
#   serve_pages.py <root> <prefix> <port>     e.g.  /tmp/x /rdk-halif-aidl/ 8000

import http.server
import os
import sys

ROOT, PREFIX, PORT = sys.argv[1], sys.argv[2], int(sys.argv[3])


class PagesHandler(http.server.SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=ROOT, **kwargs)

    def translate_path(self, path):
        path = path.split("?", 1)[0].split("#", 1)[0]
        if not path.startswith(PREFIX):
            return os.path.join(ROOT, ".not-under-site-prefix")
        return super().translate_path("/" + path[len(PREFIX):])

    def do_GET(self):
        if self.path in ("/", PREFIX.rstrip("/")):
            self.send_response(301)
            self.send_header("Location", PREFIX)
            self.end_headers()
            return
        super().do_GET()

    def send_error(self, code, message=None, explain=None):
        not_found = os.path.join(ROOT, "404.html")
        if code != 404 or not os.path.isfile(not_found):
            super().send_error(code, message, explain)
            return
        with open(not_found, "rb") as f:
            body = f.read()
        self.send_response(404)
        self.send_header("Content-Type", "text/html; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)


if __name__ == "__main__":
    print(f"[INFO] Serving the published site at http://localhost:{PORT}{PREFIX}  (Ctrl+C to stop)")
    http.server.ThreadingHTTPServer(("0.0.0.0", PORT), PagesHandler).serve_forever()
