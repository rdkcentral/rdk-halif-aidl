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

cd ..

function ECHO()
{
    echo -e "$*"
}

# Function to clone a repository if it doesn't have a.done file
function clone_repo
{
  repo_url="$1"
  target_dir="$2"
  done_file="$target_dir/.done"

  # Check if directory exists (using -d)
  if [ ! -d "$target_dir" ]; then
    mkdir -p "$target_dir"
  fi

  # Check if.done file exists (using -f)
  if [ ! -f "$done_file" ]; then
    echo "Cloning $repo_url to $target_dir"
    git clone "$repo_url" "$target_dir"
    touch "$done_file"  # Create.done file
  else
    echo "$target_dir already cloned. Skipping."
  fi
}

# Request that the user re-run this script from the vendorexit
# Check if already inside a virtual environment
if [[ ! -n "$VIRTUAL_ENV" ]]; then
    # Activate virtual environment
    ECHO "please run ${YELLOW}install.sh${NO_COLOR} to ensure setup:"
    ECHO ${YELLOW}"./install.sh"${NO_COLOR}
    return 1  # Exit the function if already in a venv
fi

# Clone repositories (call the function directly)
clone_repo "https://github.com/rdkcentral/ut-core.wiki.git" "docs/external_content/ut-core-wiki"
#clone_repo "https://github.com/rdkcentral/another-repo.git" "docs/external_content/another-repo"  # Example
#... add more repo clones like this...

# Run MkDocs in service mode
mkdocs serve
