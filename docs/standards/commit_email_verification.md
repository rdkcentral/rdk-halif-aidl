# Commit Email Verification

## Purpose

Pull requests targeting `develop` or `main` run the required **Commit email
check**. The check protects the provenance of commit metadata that a squash
merge copies into the target branch's history.

## Requirements

- Commit authors and committers must use a GitHub noreply address:
  `<id>+<login>@users.noreply.github.com`, shown in GitHub **Settings >
  Emails**. Commits made in the GitHub web UI may use `noreply@github.com`.
- Every email address in a commit trailer, such as `Co-authored-by:`,
  `Signed-off-by:` or `Cc:`, must also be a GitHub noreply address.
- Do not use a tool or service account as a co-author.
- A `Co-authored-by:` trailer for a GitHub account produces a reviewer warning
  to confirm the attribution. Bot co-authors also produce a warning, but
  warnings do not fail the check.

## Configure Git

Set the public noreply address shown in GitHub:

```bash
git config user.email "<id>+<login>@users.noreply.github.com"
```

Use `--global` if this identity applies to every repository on the machine:

```bash
git config --global user.email "<id>+<login>@users.noreply.github.com"
```

## Validate a branch locally

Run the same check as the pull-request workflow before pushing:

```bash
scripts/check_commit_emails.sh origin/develop..HEAD
```

Pass a different revision range when the pull request targets another branch.

## Correct rejected commits

If the check reports an incorrect author or committer address, rewrite the
commits on a branch containing only your own work, then update the pull
request:

```bash
git rebase -x 'git commit --amend --no-edit --reset-author' origin/develop
git push --force-with-lease
```

If the check reports an invalid trailer, use an interactive rebase to remove
or correct that trailer, then push with `--force-with-lease`.
