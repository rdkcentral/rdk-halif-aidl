# Release Runbook

The steps to cut release `X.Y.Z` with `scripts/release.sh`, in order. The rules the tool applies (change classes, version bumps, the structural audit) are in the [HAL Delivery & Versioning SOP](versioning-sop.md).

```mermaid
flowchart TD
    A[1. Milestone ready] --> B[2. Cut release/X.Y.Z from develop]
    B --> C[3. check: read the plan]
    C --> D{Doubts?}
    D -- decide each --> E[4. stage all, with every --confirm]
    D -- none --> E
    E --> F{Audit clean?}
    F -- no --> R[clean, fix, back to 4]
    F -- yes --> G[5. --apply: snapshots and builds]
    G --> H[6. Review git diff --cached]
    H --> I[7. --apply --commit: push branch, deploy docs]
    I --> J[8. --complete: tag on main, back-merge, publish]
```

Run every command from the repository root, in a clean worktree. Each step names the command and what to check before moving on.

## 1. Milestone ready

- The milestone `X.Y.Z` has no open issues or PRs.
- Every PR merged into `develop` since the last tag carries milestone `X.Y.Z`:

```bash
for n in $(git log --first-parent --format=%s <last-tag>..origin/develop \
           | grep -oE 'Merge pull request #[0-9]+' | grep -oE '[0-9]+$'); do
  gh api repos/rdkcentral/rdk-halif-aidl/issues/$n -q '"#\(.number) \(.milestone.title)"'
done | grep -v " X.Y.Z$"     # prints nothing when every PR is on X.Y.Z
```

- Set the milestone's due date to the release date.

## 2. Cut the release branch first

```bash
git fetch origin
git switch -c release/X.Y.Z origin/develop
```

Create the branch before anything else. `stage` takes the release version from the branch name; it has no `--release-version` option. Run on `develop`, it assumes the next minor (for example 0.24.0 after 0.23.0) and writes a whole release for that version. A point release such as 0.23.1 is only possible from `release/0.23.1`.

## 3. Read the plan

```bash
./scripts/release.sh check
```

Read-only. Note two things:

- **Release version** in the header must be `X.Y.Z`.
- **Doubts**: components where the PR labels and the compiler disagree. The tool releases each at the compiler's class unless you confirm a higher one. Confirm `minor` when behaviour changed behind an unchanged interface, and record what changed. Otherwise accept the compiler's class.

The first mutating run stages the AIDL toolchain and Binder SDK (`./build_binder.sh`), which takes several minutes.

## 4. Stage everything, with every decision, in one run

```bash
./scripts/release.sh stage all \
  audiodecoder --confirm minor "<what behaviour changed>" \
  videodecoder --confirm minor "<what behaviour changed>"
```

Give every `--confirm` (and every `--version` pin) in this one command. Staging writes each component's snapshot with imports pinned to the versions of the components it depends on. Re-staging one component later, by `drop` and `stage`, leaves its dependants importing the old version, and their snapshot builds then fail with `Unresolved versioned-import target`.

Check that the output ends with `✅ Audit clean`. A row marked ⚠️ blocks the release: run `clean` (below), fix the cause, and repeat this step.

Staging writes the snapshot directories, each `metadata.yaml`, `versions_released.yaml`, `mkdocs.yml`, `RAG_STATUS_REPORT.md`, a `CHANGELOG.md` section and `docs/releases/X.Y.Z.md`.

## 5. Apply

```bash
./scripts/release.sh --apply --release-version X.Y.Z
```

Regenerates the bindings, builds every snapshot and the documentation site, and stages the result on `release/X.Y.Z`. Nothing is committed. Each failed build names its log under `out/release-snapshot-<component>.log`.

## 6. Review

```bash
git diff --cached --stat
./scripts/release.sh --check-metadata     # RAG_STATUS_REPORT.md matches the new versions
```

Check the versions in each `metadata.yaml`, and that the `CHANGELOG.md` section lists every merged PR.

Then write the release notes in `docs/releases/X.Y.Z.md` and `git add` it. The tool fills in the component bumps; write the three sections it leaves as comments, following the previous release's notes:

- **Headline**: one paragraph on what the release changes.
- **Highlights**: the interface changes as a table (component, change, PR), then behaviour, specification and tooling changes.
- **Upgrade Guide**: numbered steps for HAL and client implementers.

`CHANGELOG.md` lists every merged change; the release notes are what readers act on, and `--complete` publishes them as the GitHub release.

## 7. Commit and push the release branch

```bash
./scripts/release.sh --commit --release-version X.Y.Z
```

Commits the staged release artefacts, pushes `release/X.Y.Z` and deploys the versioned documentation. Always pass `--release-version`: without it, `--commit` takes the next minor after the last tag, not the branch name, and would commit and deploy the wrong version. The hint printed at the end of `--apply` omits it.

## 8. Complete

```bash
./scripts/release.sh --complete
```

Runs `git flow release finish X.Y.Z` (merges to `main`, tags `X.Y.Z`, merges back to `develop`), pushes `main`, `develop` and the tag, publishes the documentation, and creates the GitHub release from `docs/releases/X.Y.Z.md`. A re-run after a partial failure resumes from the first incomplete step.

## Starting again

```bash
./scripts/release.sh clean
git rm -f --ignore-unmatch docs/releases/X.Y.Z.md
git status --short     # prints nothing
```

`clean` reverts every release artefact and forgets the pins and confirmations. It leaves `docs/releases/X.Y.Z.md` when staging added it to the index, so remove that by hand.
