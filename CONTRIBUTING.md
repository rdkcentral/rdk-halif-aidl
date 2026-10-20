# Contributing

- If you wish to make code contributions to this project, the source is hosted at [github.com/rdkcentral](https://github.com/rdkcentral).

You can submit your changes for review via that site, by raising an issue in github, [ut-core/issues](https://github.com/rdkcentral/ut-core/issues), and following the sequence below.

- create a branch with a name follow the guidelines gh(x)_(synopsis)
- where x is the ticket number
- where synopsis is a short synopsis for the reason for the branch.
- create a pull request [https://github.com/rdkcentral/ut-core/compare](https://github.com/rdkcentral/ut-core/compare) when the code changes are ready for review.
- The team will review, and if accepted your changes will be merged to the mainline.

## Commit email verification

Pull requests targeting `develop` or `main` run the required **Commit email
check**. It verifies every commit in the pull request because a squash merge
copies each commit message into the target branch's history.

- Commit authors and committers must use a GitHub noreply address:
  `<id>+<login>@users.noreply.github.com`, shown in GitHub **Settings >
  Emails**. GitHub web commits may use `noreply@github.com`.
- Every email address in a commit trailer, such as `Co-authored-by:`,
  `Signed-off-by:` or `Cc:`, must also be a GitHub noreply address.

See the [Commit Email Verification guide](docs/standards/commit_email_verification.md)
to configure Git, run the check locally and correct rejected commits or
trailers.

- In order to contribute code, first-time users are requested to agree to the [license](https://wiki.rdkcentral.com/signup.action).

- Note: This contributing.md is draft, and is expected to change based on Tier1/Tier2 requirements TBC.
