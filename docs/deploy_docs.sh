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

MY_PATH="$(realpath ${BASH_SOURCE[0]})"
MY_DIR="$(dirname ${MY_PATH})/scripts"
SCRIPTS_DIR="$(dirname ${MY_PATH})"
GIT_ROOT="${MY_DIR}/../"

# --- Configuration ---
MKDOCS_DIR="${GIT_ROOT}"      # Path to your mkdocs directory
OUTPUT_DIR="${GIT_ROOT}site"        # Directory where mkdocs builds its site
GITHUB_REPO="rdkcentral/rdk-halif-aidl.git" # Your GitHub username and repo name
BRANCH="gh-pages"           # The branch to publish to
COMMIT_MESSAGE="Automated mkdocs deployment"

# --- Helper Functions ---
log_info() {
  echo "[INFO] $*"
}

log_error() {
  echo "[ERROR] $*"
  exit 1
}
# --- End Helper Functions ---

# --- Launch the pyenv ---
{
  ${PWD}/scripts/install.sh --quiet
  source ${PWD}/scripts/activate_venv.sh
}

# --- Main Script ---

log_info "Starting mkdocs deployment..."

# Check if mkdocs.yml exists
if [ ! -f "$MKDOCS_DIR/mkdocs.yml" ]; then
  log_error "mkdocs.yml not found in [$MKDOCS_DIR]"
fi

# Go and ensure the output directory exists
mkdir -p "${OUTPUT_DIR}"
cd "$OUTPUT_DIR" || log_error "Could not cd to [$OUTPUT_DIR]"

# Initialize a Git repository if it doesn't exist
if [ ! -d ".git" ]; then
  log_info "Initializing Git repository..."
  git init
fi

# Add the gh-pages remote if it doesn't exist
if ! git remote get-url origin > /dev/null 2>&1; then
  log_info "Adding remote origin..."
  git remote add origin "https://github.com/$GITHUB_REPO"
fi

# Checkout the gh-pages branch (create it if it doesn't exist)
log_info "Checking out/creating branch '$BRANCH'..."
git checkout --orphan "$BRANCH" 2>/dev/null || git checkout "$BRANCH"

# Clean the directory (important!)
log_info "Cleaning directory..."
git clean -fd

# Build the mkdocs site
log_info "Building mkdocs site..."
mkdocs build --clean --config-file "$MKDOCS_DIR/mkdocs.yml" || log_error "mkdocs build failed"

# Add .gitignore, .nojekyll
touch .gitignore
echo "python_venv" >> .gitignore
echo "*.sh" >> .gitignore
echo "requirements.txt" >> .gitignore
touch .nojekyll

# Add all files
log_info "Adding files..."
git add .

# Commit the changes
log_info "Committing changes..."
git commit -m "$COMMIT_MESSAGE"

# Push to GitHub Pages
log_info "Pushing to GitHub Pages..."
git push origin "$BRANCH" || log_error "Git push failed"

# Go back to the original directory
cd ..

log_info "Mkdocs site published successfully!"

deactivate

# --- End Main Script ---

