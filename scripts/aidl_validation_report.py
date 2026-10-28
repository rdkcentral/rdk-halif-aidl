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

"""aidl_validation_report.py - tabulate the validate_aidl.sh findings per component.

Runs the interface hygiene checks over every HAL component and writes the result
to VALIDATION_REPORT.md: a summary, a per-component table with a column per check,
and every finding against the file and line that has to change.

The checks are the seven that scripts/validate_aidl.sh runs interactively:

    1. aidl compiles          - valid AIDL at vintf stability
    2. generated C++ compiles - no circular includes between generated headers
    3. line length            - the 120-column limit from .clang-format
    4. formatting             - clang-format clean, trailing newline on every file
    5. documentation          - aidl_comment_inject.py --validate, run in-process
                                so the two can never disagree about a finding
    6. String annotation      - every String carries @utf8InCpp (HAL.AIDL.83)
    7. comment structure      - no block comment opens inside another

Checks 1 and 2 need the Binder SDK staged (./build_binder.sh). Without it they
are reported as skipped rather than passed, and the documentation check falls
back to the committed <component>/<version>/include tree, which may be older
than the AIDL beside it.

Generation happens in a temporary directory, so this is safe to run on a dirty
working tree and nothing in the component trees is touched.

Only the in-development `current/` tree is reported on. Released snapshots are
frozen and are covered only when one is named explicitly with --version.

Usage:
    scripts/aidl_validation_report.py                   # all components, current/
    scripts/aidl_validation_report.py broadcast drm     # named components
    scripts/aidl_validation_report.py --version 0.1.0.0 # audit a frozen snapshot
    scripts/aidl_validation_report.py --skip-cxx        # skip the slow compile
    scripts/aidl_validation_report.py --summary         # omit the per-finding detail
    scripts/aidl_validation_report.py --output -        # write to stdout
"""

from __future__ import annotations

import argparse
import os
import re
import shutil
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass, field
from datetime import date
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

from aidl_comment_inject import Finding, Report, Stats, process_tree, read_text, validate_tree  # noqa: E402

REPORT_NAME = "VALIDATION_REPORT.md"
# Released snapshots are frozen, so only the in-development tree is worth a
# status report; --version is there for the rare case of auditing one.
DEFAULT_VERSION = "current"
RELEASED_MANIFEST = "versions_released.yaml"
AIDL_BIN = "build/binder/aidl"
AIDL_FLAGS = ("--lang=cpp", "--min_sdk_version=33", "--structured", "--stability=vintf")
# Mirrors the candidate order used by the per-component CMakeLists, so the
# generated C++ check here agrees with the real build.
BINDER_INCLUDE_CANDIDATES = (
    "out/build/include/binder_sdk",
    "out/target/include/binder_sdk",
    "out/build/include",
    "out/target/include",
)
COLUMN_LIMIT = 120
# A comment line holding nothing but a URL cannot be wrapped, so it is exempt from the limit.
UNBREAKABLE_URL_RE = re.compile(r"^\s*(?:/\*\*?|\*|//[/!]?)?\s*https?://\S+\s*$")
# clang-format is configured for Java (see .clang-format); AIDL is close enough
# that the repo formats it that way, so the check has to claim the same.
ASSUME_FILENAME = "X.java"
# Ordered so the table columns read worst-to-least-structural, matching how the
# categories are explained at the foot of the report.
CATEGORIES = ("coverage", "params", "returns", "headers")
# The `- <name>@<version>` entries under `imports:` in interface.yaml.
IMPORT_RE = re.compile(r"^\s*-\s*([A-Za-z0-9_]+)@(\S+)")
STRING_RE = re.compile(r"(^|[^A-Za-z0-9_])String([^A-Za-z0-9_]|$)")
ANNOTATION_ONLY_RE = re.compile(r"^@[A-Za-z]")
SKIPPED = "⏭️"


@dataclass
class Location:
    """One line of one file, with the text that triggered the finding."""

    path: Path
    line: int
    text: str


@dataclass
class Toolchain:
    """The external tools the checks need, as far as they are available."""

    aidl: Path | None
    binder_include: Path | None
    cxx: str
    clang_format: str | None
    jobs: int
    skip_cxx: bool

    @property
    def can_generate(self) -> bool:
        return self.aidl is not None

    @property
    def can_compile(self) -> bool:
        return self.can_generate and self.binder_include is not None and not self.skip_cxx


@dataclass
class ComponentStatus:
    """One component's result for every check. `None` means the check was skipped."""

    name: str
    aidl_files: int
    released: str
    aidl_ok: bool | None = None
    aidl_error: str = ""
    cxx_total: int | None = None
    cxx_failures: list[tuple[str, str]] = field(default_factory=list)
    long_lines: list[Location] = field(default_factory=list)
    missing_newline: list[Path] = field(default_factory=list)
    unformatted: list[Path] = field(default_factory=list)
    formatting_checked: bool = True
    doc_findings: list[Finding] = field(default_factory=list)
    strings: list[Location] = field(default_factory=list)
    nested_comments: list[Location] = field(default_factory=list)

    @property
    def doc_counts(self) -> dict[str, int]:
        counts = {category: 0 for category in CATEGORIES}
        for finding in self.doc_findings:
            counts[finding.category] = counts.get(finding.category, 0) + 1
        return counts

    @property
    def passes(self) -> bool:
        """True when nothing that ran reported anything; a skipped check is not a failure."""
        return (
            self.aidl_ok is not False
            and not self.cxx_failures
            and not self.long_lines
            and not self.missing_newline
            and not self.unformatted
            and not self.doc_findings
            and not self.strings
            and not self.nested_comments
        )


def git(repo_root: Path, *args: str) -> str:
    """A git command's output, or "" where git cannot answer (tarball, no git)."""
    try:
        result = subprocess.run(
            ["git", "-C", str(repo_root), *args],
            capture_output=True,
            text=True,
            check=True,
        )
    except (OSError, subprocess.CalledProcessError):
        return ""
    return result.stdout.strip()


def released_versions(repo_root: Path) -> dict[str, str]:
    """component -> latest released snapshot, from versions_released.yaml.

    Read with a line scanner rather than a YAML parser: the manifest is a flat
    `name: version` map under `components:`, and this script is run from a bare
    checkout where PyYAML may not be installed.
    """
    manifest = repo_root / RELEASED_MANIFEST
    if not manifest.is_file():
        return {}

    versions: dict[str, str] = {}
    in_components = False
    for raw in manifest.read_text(encoding="utf-8").splitlines():
        line = raw.split("#", 1)[0].rstrip()
        if not line.strip():
            continue
        if not line.startswith((" ", "\t")):
            in_components = line.strip() == "components:"
            continue
        if in_components and ":" in line:
            name, _, version = line.strip().partition(":")
            versions[name.strip()] = version.strip()
    return versions


def discover_components(repo_root: Path, version: str) -> list[str]:
    """Every component holding AIDL for `version`."""
    return sorted(path.parent.parent.name for path in repo_root.glob(f"*/{version}/com"))


def find_toolchain(repo_root: Path, cxx: str, clang_format: str, jobs: int, skip_cxx: bool) -> Toolchain:
    """Locate the AIDL compiler, Binder SDK headers and formatter, where present."""
    aidl = repo_root / AIDL_BIN
    binder_include = next((repo_root / c for c in BINDER_INCLUDE_CANDIDATES if (repo_root / c).is_dir()), None)
    return Toolchain(
        aidl=aidl if os.access(aidl, os.X_OK) else None,
        binder_include=binder_include,
        cxx=cxx,
        clang_format=clang_format if shutil.which(clang_format) else None,
        jobs=jobs,
        skip_cxx=skip_cxx,
    )


def imports_of(repo_root: Path, component: str, version: str) -> list[tuple[str, str]]:
    """(component, version) for every import pinned in `component`'s interface.yaml."""
    manifest = repo_root / component / version / "interface.yaml"
    if not manifest.is_file():
        return []
    return [
        (match.group(1), match.group(2))
        for line in manifest.read_text(encoding="utf-8").splitlines()
        if (match := IMPORT_RE.match(line))
    ]


def stage(repo_root: Path, component: str, version: str, dest: Path, staged: set[tuple[str, str]]) -> None:
    """Copy a component's AIDL, and transitively that of everything it imports, into `dest`.

    Each import is staged at the version its interface.yaml pins, not at the
    version being reported on - a released snapshot imports released siblings,
    and those version numbers do not have to agree.
    """
    if (component, version) in staged:
        return
    source = repo_root / component / version / "com"
    if not source.is_dir():
        return
    staged.add((component, version))
    shutil.copytree(source, dest / "com", dirs_exist_ok=True)
    for dependency, pinned in imports_of(repo_root, component, version):
        stage(repo_root, dependency, pinned, dest, staged)


def generate(repo_root: Path, component: str, version: str, work: Path, toolchain: Toolchain) -> tuple[bool, str]:
    """Compile a component's AIDL into `work`. Returns (succeeded, compiler output)."""
    src, gen, inc = work / "src", work / "gen", work / "inc"
    for directory in (src, gen, inc):
        directory.mkdir(parents=True, exist_ok=True)
    stage(repo_root, component, version, src, set())

    sources = sorted(str(path) for path in src.rglob("*.aidl"))
    if not sources:
        return False, "no AIDL staged"

    result = subprocess.run(
        [str(toolchain.aidl), *AIDL_FLAGS, "-I", str(src), "-o", str(gen), "-h", str(inc), *sources],
        capture_output=True,
        text=True,
    )
    return result.returncode == 0, (result.stderr or result.stdout).strip()


def compile_generated(work: Path, toolchain: Toolchain) -> tuple[int, list[tuple[str, str]]]:
    """Syntax-check every generated translation unit. Returns (total, failures).

    -w because the vendored SDK headers emit clang-only attribute warnings under
    gcc; this check is about the generated code, not about them.
    """
    sources = sorted((work / "gen").rglob("*.cpp"))
    includes = ["-I", str(work / "inc"), "-I", str(toolchain.binder_include)]

    def syntax_check(source: Path) -> tuple[str, str] | None:
        result = subprocess.run(
            [toolchain.cxx, "-fsyntax-only", "-std=c++17", "-w", *includes, str(source)],
            capture_output=True,
            text=True,
        )
        if result.returncode == 0:
            return None
        return source.name, (result.stderr or result.stdout).strip()

    with ThreadPoolExecutor(max_workers=toolchain.jobs) as pool:
        failures = [outcome for outcome in pool.map(syntax_check, sources) if outcome is not None]
    return len(sources), failures


def check_line_length(path: Path) -> list[Location]:
    """Lines over the column limit, except comment lines that are only a URL."""
    return [
        Location(path, number, f"{len(line)} cols")
        for number, line in enumerate(read_text(path).splitlines(), start=1)
        if len(line) > COLUMN_LIMIT and not UNBREAKABLE_URL_RE.match(line)
    ]


def check_formatting(path: Path, clang_format: str) -> bool:
    """True if clang-format would leave the file alone."""
    original = path.read_bytes()
    result = subprocess.run(
        [clang_format, f"-assume-filename={ASSUME_FILENAME}"],
        input=original,
        capture_output=True,
    )
    return result.returncode == 0 and result.stdout == original


def check_strings(path: Path) -> list[Location]:
    """Declarations using `String` without `@utf8InCpp`.

    Comments and string literals are stripped first: the word "String" appears
    in plenty of prose, and a literal may legitimately contain it.
    """
    findings: list[Location] = []
    in_comment = False
    carry = False

    for number, raw in enumerate(read_text(path).splitlines(), start=1):
        line = re.sub(r"//.*", "", raw)
        if in_comment:
            end = line.find("*/")
            if end < 0:
                continue
            line, in_comment = line[end + 2 :], False
        while (start := line.find("/*")) >= 0:
            before, rest = line[:start], line[start + 2 :]
            end = rest.find("*/")
            if end >= 0:
                line = before + rest[end + 2 :]
            else:
                line, in_comment = before, True
                break
        line = re.sub(r'"[^"]*"', '""', line).strip()
        if not line:
            continue

        if STRING_RE.search(line) and "@utf8InCpp" not in line and not carry:
            findings.append(Location(path, number, line))
        # An annotation on its own line applies to the declaration below it.
        carry = bool(ANNOTATION_ONLY_RE.match(line)) and not re.search(r"[;({]", line) and "@utf8InCpp" in line

    return findings


def check_comment_structure(path: Path) -> list[Location]:
    """Block comments that open inside another block comment.

    `/*` inside a string literal or after a `//` is not an opener, so both are skipped.
    """
    findings: list[Location] = []
    in_block = False

    for number, line in enumerate(read_text(path).splitlines(), start=1):
        in_string = False
        index = 0
        while index < len(line):
            pair, char = line[index : index + 2], line[index]
            if in_block:
                if pair == "/*":
                    findings.append(Location(path, number, line.strip()))
                    index += 2
                elif pair == "*/":
                    in_block = False
                    index += 2
                else:
                    index += 1
            elif in_string:
                if char == "\\":
                    index += 2
                else:
                    in_string = char != '"'
                    index += 1
            elif pair == "//":
                break
            elif pair == "/*":
                in_block = True
                index += 2
            else:
                in_string = char == '"'
                index += 1

    return findings


def collect(repo_root: Path, components: list[str], version: str, toolchain: Toolchain) -> list[ComponentStatus]:
    """Run every check over every component."""
    released = released_versions(repo_root)
    statuses = []

    with tempfile.TemporaryDirectory(prefix="aidl-status-") as scratch:
        for component in components:
            print(f"   {component} ...", file=sys.stderr, flush=True)
            statuses.append(
                _check_component(repo_root, component, version, released, toolchain, Path(scratch) / component)
            )
    return statuses


def _check_component(
    repo_root: Path,
    component: str,
    version: str,
    released: dict[str, str],
    toolchain: Toolchain,
    work: Path,
) -> ComponentStatus:
    aidl_dir = repo_root / component / version
    files = sorted((aidl_dir / "com").rglob("*.aidl"))
    status = ComponentStatus(name=component, aidl_files=len(files), released=released.get(component, ""))

    # 1. and 2. need the Binder SDK; without it they stay None, i.e. skipped.
    if toolchain.can_generate:
        status.aidl_ok, status.aidl_error = generate(repo_root, component, version, work, toolchain)
        if status.aidl_ok and toolchain.can_compile:
            status.cxx_total, status.cxx_failures = compile_generated(work, toolchain)

    # 3., 4., 6. and 7. are pure text checks on the component's own files.
    status.formatting_checked = toolchain.clang_format is not None
    for path in files:
        status.long_lines += check_line_length(path)
        if path.read_bytes()[-1:] not in (b"\n", b""):
            status.missing_newline.append(path)
        if status.formatting_checked and not check_formatting(path, toolchain.clang_format):
            status.unformatted.append(path)
        status.strings += check_strings(path)
        status.nested_comments += check_comment_structure(path)

    # 5. mirrors validate_aidl.sh: scratch headers are injected before validating,
    # and the committed headers are checked for staleness as well.
    include_dirs = [aidl_dir / "include"]
    if status.aidl_ok:
        process_tree(aidl_dir, work / "inc", Stats(), strip_only=False, dry_run=False, verbose=False)
        include_dirs.insert(0, work / "inc")
    report = Report()
    for include_dir in include_dirs:
        validate_tree(aidl_dir, include_dir, report)
    unique = {(f.path, f.line, f.category, f.message): f for f in report.findings}
    status.doc_findings = sorted(unique.values())

    return status


def render(repo_root: Path, version: str, statuses: list[ComponentStatus], toolchain: Toolchain, detail: bool) -> str:
    """The VALIDATION_REPORT.md body."""
    lines: list[str] = []
    lines += _header(repo_root, version, toolchain)
    lines += _summary(statuses, toolchain, version)
    lines += _per_component(statuses)
    lines += _checks(repo_root, statuses, toolchain, detail)
    lines += _footer(version)
    return "\n".join(lines) + "\n"


def _header(repo_root: Path, version: str, toolchain: Toolchain) -> list[str]:
    commit = git(repo_root, "rev-parse", "--short", "HEAD")
    branch = git(repo_root, "rev-parse", "--abbrev-ref", "HEAD")
    stamp = [f"**Generated:** {date.today().isoformat()}"]
    if commit:
        stamp.append(f"commit `{commit}`")
    if branch:
        stamp.append(f"branch `{branch}`")

    lines = [
        "# AIDL Validation Report",
        "",
        f"Interface hygiene and documentation state of every component's `{version}/` tree, as reported by the",
        "checks that `./scripts/validate_aidl.sh` runs.",
        "",
        " · ".join(stamp),
        "",
        "This is a snapshot of what the tooling can check mechanically. It says nothing about functional",
        "completeness, API review status or whether an interface is fit to freeze.",
        "",
        f"Only the `{version}/` tree is checked. Frozen snapshots are not re-checked; pass `--version <snapshot>`",
        "to audit one.",
        "",
    ]
    lines += _skipped_note(toolchain)
    return lines + ["---", ""]


def _skipped_note(toolchain: Toolchain) -> list[str]:
    """Say plainly which checks did not run, so a skip cannot read as a pass."""
    notes = []
    if not toolchain.can_generate:
        notes.append(
            f"**AIDL and generated C++ not checked** - no AIDL compiler at `{AIDL_BIN}`. "
            "Stage the Binder SDK with `./build_binder.sh`. The documentation check fell back to the "
            "committed `include/` trees, which may be older than the AIDL beside them."
        )
    elif toolchain.skip_cxx:
        notes.append("**Generated C++ not checked** - run without `--skip-cxx` to include it.")
    elif toolchain.binder_include is None:
        notes.append("**Generated C++ not checked** - no Binder SDK headers found under `out/`.")
    if toolchain.clang_format is None:
        notes.append("**Formatting not checked** - `clang-format` is not on `PATH`.")
    return [f"⚠️  {note}" + "\n" for note in notes] if notes else []


def _summary(statuses: list[ComponentStatus], toolchain: Toolchain, version: str) -> list[str]:
    total = len(statuses)
    clean = [status.name for status in statuses if status.passes]
    doc_findings = [f for status in statuses for f in status.doc_findings]
    doc_totals = {c: sum(1 for f in doc_findings if f.category == c) for c in CATEGORIES}

    aidl_ok = sum(1 for s in statuses if s.aidl_ok)
    aidl_run = sum(1 for s in statuses if s.aidl_ok is not None)
    cxx_ok = sum(1 for s in statuses if s.cxx_total is not None and not s.cxx_failures)
    cxx_run = sum(1 for s in statuses if s.cxx_total is not None)

    lines = [
        "## Summary",
        "",
        "| | |",
        "|---|---:|",
        f"| Components | {total} |",
        f"| AIDL files (`{version}/`, excluding imports) | {sum(s.aidl_files for s in statuses)} |",
        f"| Components passing every check that ran | {_clean_cell(clean, total)} |",
        f"| AIDL compiles | {_ratio(aidl_ok, aidl_run)} |",
        f"| Generated C++ compiles | {_ratio(cxx_ok, cxx_run)} |",
        f"| Over-length lines | {sum(len(s.long_lines) for s in statuses)} |",
        f"| Files missing a trailing newline | {sum(len(s.missing_newline) for s in statuses)} |",
        f"| Files `clang-format` would rewrite | {_formatting_total(statuses, toolchain)} |",
        f"| Documentation findings | {len(doc_findings)} |",
    ]
    lines += [f"| &nbsp;&nbsp;`{category}` | {doc_totals[category]} |" for category in CATEGORIES]
    lines.append(f"| `String` without `@utf8InCpp` | {sum(len(s.strings) for s in statuses)} |")
    lines.append(f"| Nested block-comment openers | {sum(len(s.nested_comments) for s in statuses)} |")

    return lines + ["", "---", ""]


def _per_component(statuses: list[ComponentStatus]) -> list[str]:
    lines = [
        "## Per component",
        "",
        f"Numbers are finding counts; a bold number is a failing check and {SKIPPED} is a check that did not run.",
        "",
        "| Component | Files | Released | aidl | C++ | ≤120 col | newline | format | docs | `@utf8InCpp` | comments | Result |",
        "|---|---:|---|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|---|",
    ]

    for status in statuses:
        cells = [
            _bool_cell(status.aidl_ok),
            _cxx_cell(status),
            _count_cell(len(status.long_lines)),
            _count_cell(len(status.missing_newline)),
            _count_cell(len(status.unformatted)) if status.formatting_checked else SKIPPED,
            _count_cell(len(status.doc_findings)),
            _count_cell(len(status.strings)),
            _count_cell(len(status.nested_comments)),
        ]
        result = "✅ pass" if status.passes else "❌ fail"
        lines.append(
            f"| `{status.name}` | {status.aidl_files} | {status.released or '—'} | "
            f"{' | '.join(cells)} | {result} |"
        )

    return lines + [
        "",
        "`Released` is the latest frozen snapshot from `versions_released.yaml`, for reference only; `—` means",
        "never released.",
        "",
        "---",
        "",
    ]


def _checks(repo_root: Path, statuses: list[ComponentStatus], toolchain: Toolchain, detail: bool) -> list[str]:
    """One section per check, in the order validate_aidl.sh runs them."""
    return [
        "## By check",
        "",
        *_aidl_section(statuses),
        *_cxx_section(statuses),
        *_line_length_section(repo_root, statuses, detail),
        *_formatting_section(repo_root, statuses, toolchain, detail),
        *_documentation_section(repo_root, statuses, detail),
        *_strings_section(repo_root, statuses, detail),
        *_comment_structure_section(repo_root, statuses, detail),
    ]


def _aidl_section(statuses: list[ComponentStatus]) -> list[str]:
    checked = [s for s in statuses if s.aidl_ok is not None]
    if not checked:
        return ["### 1. AIDL compiles — skipped", "", "No AIDL compiler available.", ""]

    failed = [s for s in checked if not s.aidl_ok]
    if not failed:
        return [
            f"### 1. AIDL compiles — all {len(checked)} pass",
            "",
            "Every component is valid AIDL at `--stability=vintf`.",
            "",
        ]

    lines = [f"### 1. AIDL compiles — {len(failed)} of {len(checked)} fail", ""]
    for status in failed:
        lines += [f"**`{status.name}`**", "", "```", status.aidl_error or "(no output)", "```", ""]
    return lines


def _cxx_section(statuses: list[ComponentStatus]) -> list[str]:
    checked = [s for s in statuses if s.cxx_total is not None]
    if not checked:
        return ["### 2. Generated C++ compiles — skipped", "", "Not run; see the note above.", ""]

    units = sum(s.cxx_total for s in checked)
    failed = [s for s in checked if s.cxx_failures]
    if not failed:
        return [
            f"### 2. Generated C++ compiles — all {len(checked)} pass ({units} translation units)",
            "",
            "No circular includes between generated headers.",
            "",
        ]

    lines = [f"### 2. Generated C++ compiles — {len(failed)} of {len(checked)} fail", ""]
    for status in failed:
        lines.append(f"**`{status.name}`** — {len(status.cxx_failures)} of {status.cxx_total} translation units")
        lines.append("")
        for unit, output in status.cxx_failures:
            lines += [f"`{unit}`", "", "```", output, "```", ""]
    return lines


def _line_length_section(repo_root: Path, statuses: list[ComponentStatus], detail: bool) -> list[str]:
    offenders = [s for s in statuses if s.long_lines]
    total = sum(len(s.long_lines) for s in statuses)
    if not offenders:
        return [f"### 3. Line length — all {len(statuses)} pass", "", f"No line exceeds {COLUMN_LIMIT} columns.", ""]

    lines = [f"### 3. Line length — {_plural(len(offenders), 'component')}, {_plural(total, 'line')}", ""]
    lines += [f"- `{s.name}` — {len(s.long_lines)}" for s in offenders]
    lines.append("")
    if detail:
        for status in offenders:
            lines += [f"<details><summary><code>{status.name}</code></summary>", ""]
            lines += [f"- {_relative(loc.path, repo_root)}:{loc.line} ({loc.text})" for loc in status.long_lines]
            lines += ["", "</details>", ""]
    return lines


def _formatting_section(
    repo_root: Path, statuses: list[ComponentStatus], toolchain: Toolchain, detail: bool
) -> list[str]:
    missing = [s for s in statuses if s.missing_newline]
    newline_total = sum(len(s.missing_newline) for s in statuses)

    if missing:
        lines = [
            f"### 4. Trailing newline — {_plural(len(missing), 'component')}, {_plural(newline_total, 'file')}",
            "",
        ]
        lines += [f"- `{s.name}` — {len(s.missing_newline)}" for s in missing]
        lines.append("")
        if detail:
            lines += [f"  - {_relative(p, repo_root)}" for s in missing for p in s.missing_newline]
            lines.append("")
    else:
        lines = [f"### 4. Trailing newline — all {len(statuses)} pass", "", "Present on every file.", ""]

    if toolchain.clang_format is None:
        return lines + ["### 5. Formatting — skipped", "", "`clang-format` is not on `PATH`.", ""]

    unformatted = [s for s in statuses if s.unformatted]
    format_total = sum(len(s.unformatted) for s in statuses)
    if not unformatted:
        return lines + [f"### 5. Formatting — all {len(statuses)} pass", "", "`clang-format` clean.", ""]

    lines += [f"### 5. Formatting — {_plural(len(unformatted), 'component')}, {_plural(format_total, 'file')}", ""]
    lines += [f"- `{s.name}` — {len(s.unformatted)}" for s in unformatted]
    lines += ["", "Mechanical: `./scripts/format_aidl.sh <component>` fixes every one of these.", ""]
    if detail:
        for status in unformatted:
            lines += [f"<details><summary><code>{status.name}</code></summary>", ""]
            lines += [f"- {_relative(path, repo_root)}" for path in status.unformatted]
            lines += ["", "</details>", ""]
    return lines


def _documentation_section(repo_root: Path, statuses: list[ComponentStatus], detail: bool) -> list[str]:
    offenders = [s for s in statuses if s.doc_findings]
    total = sum(len(s.doc_findings) for s in statuses)
    if not offenders:
        return [
            f"### 6. Documentation — all {len(statuses)} pass",
            "",
            "Every declaration is documented and the documentation matches the generated headers.",
            "",
        ]

    lines = [
        f"### 6. Documentation — {_plural(len(offenders), 'component')}, {_plural(total, 'finding')}",
        "",
        "| Component | Findings | Breakdown |",
        "|---|---:|---|",
    ]
    for status in offenders:
        counts = status.doc_counts
        breakdown = ", ".join(f"{c}: {counts[c]}" for c in CATEGORIES if counts[c]) or "—"
        lines.append(f"| `{status.name}` | {len(status.doc_findings)} | {breakdown} |")
    lines.append("")

    if detail:
        for status in offenders:
            lines += [f"<details><summary><code>{status.name}</code></summary>", ""]
            for path in sorted({f.path for f in status.doc_findings}):
                entries = [f for f in status.doc_findings if f.path == path]
                lines += [
                    f"**{_relative(path, repo_root)}**",
                    "",
                    "| Line | Category | Finding |",
                    "|---:|---|---|",
                ]
                lines += [f"| {f.line} | `{f.category}` | {f.message} |" for f in entries]
                lines.append("")
            lines += ["</details>", ""]
    return lines


def _strings_section(repo_root: Path, statuses: list[ComponentStatus], detail: bool) -> list[str]:
    offenders = [s for s in statuses if s.strings]
    total = sum(len(s.strings) for s in statuses)
    if not offenders:
        return [
            f"### 7. `String` annotation — all {len(statuses)} pass",
            "",
            "Every `String` carries `@utf8InCpp`.",
            "",
        ]

    lines = [
        f"### 7. `String` annotation — {_plural(len(offenders), 'component')}, "
        f"{_plural(total, 'declaration')}",
        "",
    ]
    lines += [f"- `{s.name}` — {len(s.strings)}" for s in offenders]
    lines += [
        "",
        "`HAL.AIDL.83`: a bare `String` generates `android::String16`, `@utf8InCpp String` generates `std::string`.",
        "",
    ]
    if detail:
        for status in offenders:
            lines += [f"<details><summary><code>{status.name}</code></summary>", ""]
            lines += [f"- {_relative(loc.path, repo_root)}:{loc.line} — `{loc.text}`" for loc in status.strings]
            lines += ["", "</details>", ""]
    return lines


def _comment_structure_section(repo_root: Path, statuses: list[ComponentStatus], detail: bool) -> list[str]:
    offenders = [s for s in statuses if s.nested_comments]
    total = sum(len(s.nested_comments) for s in statuses)
    if not offenders:
        return [
            f"### 8. Comment structure — all {len(statuses)} pass",
            "",
            "No block comment opens inside another.",
            "",
        ]

    lines = [
        f"### 8. Comment structure — {_plural(len(offenders), 'component')}, {_plural(total, 'line')}",
        "",
    ]
    lines += [f"- `{s.name}` — {len(s.nested_comments)}" for s in offenders]
    lines += [
        "",
        "A nested `/*` inside a block comment swallows or garbles the Doxygen text that follows it.",
        "",
    ]
    if detail:
        for status in offenders:
            lines += [f"<details><summary><code>{status.name}</code></summary>", ""]
            lines += [f"- {_relative(loc.path, repo_root)}:{loc.line} — `{loc.text}`" for loc in status.nested_comments]
            lines += ["", "</details>", ""]
    return lines


def _footer(version: str) -> list[str]:
    return [
        "---",
        "",
        "## Documentation categories",
        "",
        "| Category | Finding |",
        "|---|---|",
        "| `coverage` | a type, method, field, constant, enum value or union field carries no documentation |",
        "| `params` | a parameter has no `@param`, or a `@param` names a parameter that does not exist |",
        "| `returns` | a value-returning method documents no return, or a `void` method documents one |",
        "| `headers` | a documented member has no matching declaration in the generated C++ (drift) |",
        "",
        "## Reproducing",
        "",
        "```bash",
        f"scripts/aidl_validation_report.py               # regenerate this file ({version}/)",
        "scripts/aidl_validation_report.py --skip-cxx    # same, without the slow compile",
        "./scripts/validate_aidl.sh <component>          # the same checks, one component, to the terminal",
        "```",
    ]


def _count_cell(count: int) -> str:
    return f"**{count}**" if count else "✅"


def _plural(count: int, noun: str) -> str:
    return f"{count} {noun}" + ("" if count == 1 else "s")


def _bool_cell(value: bool | None) -> str:
    if value is None:
        return SKIPPED
    return "✅" if value else "**fail**"


def _cxx_cell(status: ComponentStatus) -> str:
    if status.cxx_total is None:
        return SKIPPED
    return f"**{len(status.cxx_failures)}**" if status.cxx_failures else "✅"


def _ratio(passing: int, run: int) -> str:
    return f"{passing} / {run}" if run else "not checked"


def _formatting_total(statuses: list[ComponentStatus], toolchain: Toolchain) -> str:
    if toolchain.clang_format is None:
        return "not checked"
    return str(sum(len(status.unformatted) for status in statuses))


def _clean_cell(clean: list[str], total: int) -> str:
    if not clean:
        return f"0 / {total}"
    return f"{len(clean)} / {total} ({_names(clean)})"


def _names(names: list[str]) -> str:
    return ", ".join(f"`{name}`" for name in names)


def _relative(path: Path, repo_root: Path) -> Path:
    try:
        return path.relative_to(repo_root)
    except ValueError:
        return path


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=f"Generate {REPORT_NAME} from the AIDL interface hygiene checks.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__.split("Usage:")[-1],
    )
    parser.add_argument("components", nargs="*", default=[], help="components to report on (default: every component)")
    parser.add_argument(
        "--repo-root",
        type=Path,
        default=Path(__file__).resolve().parent.parent,
        help="repository root (default: the checkout holding this script)",
    )
    parser.add_argument(
        "--version",
        default=DEFAULT_VERSION,
        help=f"version directory to report on (default: {DEFAULT_VERSION}); "
        "name a released snapshot such as 0.1.0.0 to audit a frozen tree instead",
    )
    parser.add_argument(
        "--output",
        default=None,
        help=f"file to write (default: <repo-root>/{REPORT_NAME}; '-' for stdout)",
    )
    parser.add_argument("--summary", action="store_true", help="omit the per-finding detail sections")
    parser.add_argument("--skip-cxx", action="store_true", help="skip the generated C++ compile (much faster)")
    parser.add_argument("--cxx", default=os.environ.get("CXX", "g++"), help="compiler for the generated C++ check")
    parser.add_argument(
        "--clang-format",
        default=os.environ.get("CLANG_FORMAT", "clang-format"),
        help="formatter to check against",
    )
    parser.add_argument(
        "--jobs",
        type=int,
        default=os.cpu_count() or 4,
        help="translation units to compile at once (default: one per CPU)",
    )
    args = parser.parse_args(argv)

    repo_root = args.repo_root.resolve()
    components = [c for c in args.components if c != "all"] or discover_components(repo_root, args.version)
    if not components:
        print(f"❌ No components with AIDL found under {repo_root}/*/{args.version}/com", file=sys.stderr)
        return 1

    missing = [c for c in components if not (repo_root / c / args.version / "com").is_dir()]
    if missing:
        print(f"❌ No AIDL for: {', '.join(missing)}", file=sys.stderr)
        return 1

    toolchain = find_toolchain(repo_root, args.cxx, args.clang_format, args.jobs, args.skip_cxx)
    statuses = collect(repo_root, components, args.version, toolchain)
    content = render(repo_root, args.version, statuses, toolchain, detail=not args.summary)

    if args.output == "-":
        print(content, end="")
        return 0

    target = Path(args.output) if args.output else repo_root / REPORT_NAME
    target.write_text(content, encoding="utf-8")

    clean = sum(1 for status in statuses if status.passes)
    print(
        f"📝 Wrote {_relative(target.resolve(), repo_root)}: "
        f"{clean} of {len(statuses)} component(s) pass every check that ran"
    )
    return 0


if __name__ == "__main__":
    sys.exit(main())
