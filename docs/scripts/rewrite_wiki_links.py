#!/usr/bin/env python3
#!/usr/bin/env bash
#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2025 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# *
# http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#* ******************************************************************************
#!/usr/bin/env python3
import sys
import re
import os
import urllib.parse

# Matches the base "https://github.com/rdkcentral/ut-core/wiki/" plus
# everything following until a space or right parenthesis (includes optional #anchors).
WIKI_URL_PATTERN = re.compile(r'(https://github\.com/rdkcentral/ut-core/wiki/)([^\s)]+)')

def rewrite_wiki_links(file_path):
    """
    Rewrite GitHub wiki URLs to local .md references, decoding special chars.
    Also supports #anchors. Creates a .url_converted marker to prevent re-running.
    """

    marker_path = file_path + ".url_converted"
    if os.path.exists(marker_path):
        #print(f"[SKIP] {file_path}: marker file found ({marker_path}).")
        return

    # Read original content
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()

    def replace_url(match):
        """
        Callback to decode the wiki slug (and any #anchor), then produce local .md link.
        Example:
            https://github.com/rdkcentral/ut-core/wiki/SomePage#Section -> SomePage.md#Section
        """
        # Everything after "...wiki/"
        encoded_slug_with_anchor = match.group(2)
        # Decode any percent-encoded chars (e.g. %E2%80%90)
        decoded_slug_with_anchor = urllib.parse.unquote(encoded_slug_with_anchor)

        # Separate page slug from optional #anchor
        if '#' in decoded_slug_with_anchor:
            page_slug, anchor_part = decoded_slug_with_anchor.split('#', 1)
            anchor_part = '#' + anchor_part  # re-add the '#' prefix
        else:
            page_slug = decoded_slug_with_anchor
            anchor_part = ''

        # Optionally replace or sanitize certain characters in `page_slug` if needed
        # For example, if colons are problematic on your filesystem, do:
        # page_slug = page_slug.replace(':', '-')

        return f"{page_slug}.md{anchor_part}"

    # Perform the substitution
    new_content = WIKI_URL_PATTERN.sub(replace_url, content)

    if new_content == content:
        print(f"[INFO] No wiki URLs to rewrite in: {file_path}")
    else:
        # Write updated content back
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(new_content)
        print(f"[INFO] Rewrote wiki links in: {file_path}")

    # Create a marker to avoid re-processing this file
    with open(marker_path, 'w', encoding='utf-8') as marker_file:
        marker_file.write("Converted at least once.\n")
    print(f"[INFO] Created marker file: {marker_path}")

def main():
    for file_path in sys.argv[1:]:
        rewrite_wiki_links(file_path)

if __name__ == "__main__":
    main()
