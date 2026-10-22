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

"""aidl_comment_inject.py - re-inject AIDL Doxygen comments into generated C++ headers.

The AIDL compiler strips every comment when it emits C++, so the headers
engineers actually include carry no documentation at all. This tool parses the
Doxygen blocks out of the AIDL sources and writes them back into the generated
headers, matching declarations by identifier name. See
docs/whitepapers/release_documentation_strategy.md for the rationale.

Module-local layout (one component, one version):

    <module>/<version>/com/rdk/hal/<...>/*.aidl     AIDL source (documented)
    <module>/<version>/include/com/rdk/hal/<...>/   generated headers (target)

Return values and exceptions are remapped onto the generated signature, since
aidl-cpp moves an AIDL return value into an `_aidl_return` out parameter and
makes every method return `::android::binder::Status` - see
map_to_binder_signature().

Every injected block is preceded by a `// @aidl-doc` marker line. Marked
blocks are removed before injection, so the tool is idempotent and can run on
every build.

Bn*/Bp* headers are skipped: they are binder stub/proxy machinery rather than
the public API surface.

`--validate` writes nothing and instead reports where the documentation does
not cover the AIDL - undocumented declarations, including enum values and
union fields, parameters that are not documented or do not exist, undocumented
or impossible return values, documentation with no matching generated
declaration, and generated headers that would change if documentation were
injected. Exit status is 1 when anything was reported and 0 otherwise.

Usage:
    scripts/aidl_comment_inject.py                      # all components, current/
    scripts/aidl_comment_inject.py broadcast bootreason # named components
    scripts/aidl_comment_inject.py drm --version 0.1.0.0
    scripts/aidl_comment_inject.py --dry-run --verbose
    scripts/aidl_comment_inject.py --validate           # check coverage, write nothing
    scripts/aidl_comment_inject.py --validate broadcast
    scripts/aidl_comment_inject.py --strip              # remove injected blocks
    scripts/aidl_comment_inject.py --aidl-dir <d> --include-dir <d>
"""

from __future__ import annotations

import argparse
import re
import sys
from dataclasses import dataclass, field
from pathlib import Path

# Marker line written above every injected block. It is a plain `//` comment,
# not a Doxygen one: inside the block, `@aidl-doc` would be read as the unknown
# command `@aidl` and warn once per injected comment.
SENTINEL = "@aidl-doc"
MARKER = f"// {SENTINEL}"

# --- AIDL source patterns -------------------------------------------------
# Annotations are stripped from the front of a declaration before matching, so
# `@VintfStability parcelable Id {` and a bare `parcelable Id {` look alike.
# `oneway` is an optional interface modifier and is part of the type declaration.
AIDL_ANNOTATION_RE = re.compile(r"^@\w+(?:\s*\([^)]*\))?\s*")
AIDL_TYPE_RE = re.compile(r"^(?:oneway\s+)?(interface|parcelable|union|enum)\s+(\w+)")
AIDL_PACKAGE_RE = re.compile(r"^\s*package\s+([\w.]+)\s*;")
AIDL_ENUM_MEMBER_RE = re.compile(r"^(\w+)")
# `int intValue; /**< 32-bit signed integer value. */` and
# `BRIGHTNESS = 0, /*!< Picture parameter is Brightness` - both spellings of a
# Doxygen comment trailing the declaration it documents.
AIDL_TRAILING_DOC_RE = re.compile(r"/\*(?:\*<?|!<)\s*(.*?)\s*\*/\s*$")
AIDL_TRAILING_LINE_DOC_RE = re.compile(r"//[!/]<\s*(.*?)\s*$")
AIDL_METHOD_RE = re.compile(r"\b(\w+)\s*\(")
# The statement scanner consumes the terminating `;`, so a field name is the
# last identifier before the default value or the end of the declaration.
AIDL_FIELD_RE = re.compile(r"\b(\w+)\s*(?:=|$)")

# --- Generated C++ patterns ----------------------------------------------
CPP_TYPE_OPEN_RE = re.compile(r"^(\s*)(class|struct|enum\s+class|enum)\s+(\w+)\b")
CPP_ENUM_MEMBER_RE = re.compile(r"^\s*(\w+)\s*(?:=|,|$)")
CPP_METHOD_RE = re.compile(r"\b(\w+)\s*\(")
CPP_FIELD_RE = re.compile(r"\b(\w+)\s*(?:\{[^;]*\})?\s*;?\s*$")
# Anything that can't carry AIDL documentation: labels, generated identity
# constants, and the binder interface macro.
CPP_SKIP_MEMBER_RE = re.compile(r"^\s*(?:public:|private:|protected:|DECLARE_META_INTERFACE|#)")
CPP_STRING_RE = re.compile(r"\"(?:[^\"\\]|\\.)*\"|'(?:[^'\\]|\\.)*'")

# --- Doc tags that have to follow the AIDL -> C++ signature change --------
TAG_LINE_RE = re.compile(r"^\s*@\w+")
RETURNS_TAG_RE = re.compile(r"^@returns?[ \t]*")
RETVAL_TAG_RE = re.compile(r"^@retval[ \t]+(\S+)[ \t]*")
EXCEPTION_TAG_RE = re.compile(r"^@(?:exception|throws)[ \t]*(.*)$")
# The AIDL sources spell the exception several ways - `EX_ILLEGAL_STATE`,
# `binder::Status EX_ILLEGAL_STATE`, `binder::Status::Exception::EX_NONE`,
# `::android::binder::Status::EX_NULL_POINTER` - so key off the value itself.
STATUS_VALUE_RE = re.compile(r"\bEX_[A-Z_]+\b")
DOC_PARAM_RE = re.compile(r"^@param(?:\s*\[[^\]]*\])?\s+(\w+)")
BINDER_STATUS = "::android::binder::Status"
# The out parameter aidl-cpp appends for an AIDL return value.
AIDL_RETURN_PARAM = "_aidl_return"


@dataclass
class Doc:
    """A Doxygen block as it appeared in the AIDL source."""

    lines: list[str]

    def render(
        self,
        indent: str,
        out_param: str | None = None,
        binder_method: bool = False,
        file_name: str | None = None,
    ) -> list[str]:
        """Re-emit the block at `indent`, preceded by the marker line.

        With `binder_method`, the AIDL return/exception documentation is mapped
        onto the generated C++ signature (see map_to_binder_signature).
        `file_name` retargets an `@file` tag at the header being written.
        """
        body = self.body()
        if binder_method:
            body = map_to_binder_signature(body, out_param)
        if file_name is not None:
            body = [re.sub(r"^\s*@file\b.*", f"@file {file_name}", text) for text in body]

        if len(body) == 1:
            return [f"{indent}{MARKER}", f"{indent}/** {body[0].strip()} */"]

        out = [f"{indent}{MARKER}", f"{indent}/**"]
        out.extend(f"{indent} * {text}".rstrip() for text in body)
        out.append(f"{indent} */")
        return out

    def body(self) -> list[str]:
        """The comment content, one entry per line, `/**`+`*` markers removed.

        Alignment inside a line is content - the AIDL blocks line up tag
        descriptions - so only the single separating space after `*` is taken
        off, and callers put it back.
        """
        first = self.lines[0].strip()
        last = self.lines[-1].strip()

        if len(self.lines) == 1:
            text = first[3:-2] if first.endswith("*/") else first[3:]
            return [text.strip()]

        body = []
        head = first[3:].strip()
        if head:
            body.append(head)
        body.extend(self._text(raw) for raw in self.lines[1:-1])
        tail = last[:-2] if last.endswith("*/") else last
        if tail.strip() not in ("", "*"):
            body.append(self._text(tail))
        return body

    def documents_return(self) -> bool:
        """True if the block describes a returned value."""
        return any(RETURNS_TAG_RE.match(text) or RETVAL_TAG_RE.match(text) for text in self.body())

    @staticmethod
    def _text(raw: str) -> str:
        stripped = raw.strip()
        text = stripped[1:] if stripped.startswith("*") else stripped
        return text[1:] if text.startswith(" ") else text


@dataclass
class Member:
    """One member declared inside an AIDL type."""

    name: str
    kind: str  # method | field | const | enum
    declaration: str
    doc: Doc | None
    line: int


@dataclass
class TypeDoc:
    """One AIDL type, its documentation and its members."""

    kind: str
    name: str
    qualified_name: str
    doc: Doc | None = None
    line: int = 0
    file: Path | None = None
    members: dict[str, Member] = field(default_factory=dict)

    def documented_members(self) -> dict[str, Doc]:
        return {name: member.doc for name, member in self.members.items() if member.doc is not None}


@dataclass
class AidlFile:
    """One parsed AIDL file."""

    path: Path
    package: str = ""
    # A block before the `package` statement documents the file, not the first
    # type in it (the sensor interfaces use `@file` blocks this way).
    file_doc: Doc | None = None
    types: dict[str, TypeDoc] = field(default_factory=dict)


@dataclass
class PackageDocs:
    """Everything one AIDL package contributes, keyed for header lookup."""

    types: dict[str, TypeDoc] = field(default_factory=dict)
    file_docs: dict[str, Doc] = field(default_factory=dict)  # AIDL file stem -> doc


@dataclass
class Stats:
    files_changed: int = 0
    changed_headers: list[Path] = field(default_factory=list)
    types_documented: int = 0
    members_documented: int = 0
    unmatched: list[str] = field(default_factory=list)
    return_drift: list[str] = field(default_factory=list)


def map_to_binder_signature(body: list[str], out_param: str | None) -> list[str]:
    """Rewrite an AIDL method's documentation to match the generated C++.

    aidl-cpp turns `Foo bar()` into
    `::android::binder::Status bar(Foo* _aidl_return)`, so the AIDL
    documentation describes a signature that no longer exists:

      @returns <text>                  ->  @param[out] _aidl_return <text>
      @retval <value> <text>           ->  a list item under that out parameter
      @exception <...>EX_FOO <text>    ->  @retval <Status>::EX_FOO <text>

    and a `@returns` describing the returned `Status` itself is added, since
    that is what the C++ method now returns.
    """
    kept: list[list[str]] = []
    exceptions: list[list[str]] = []
    values: list[list[str]] = []
    out_block: list[str] | None = None

    for block in _tag_blocks(body):
        head = block[0]
        if out_param and RETURNS_TAG_RE.match(head):
            out_block = _retag(block, RETURNS_TAG_RE, f"@param[out] {out_param} ")
            kept.append(out_block)
        elif out_param and RETVAL_TAG_RE.match(head):
            if out_block is None:
                # Values documented without a @returns summary: give them an
                # out parameter to hang off, where the first @retval was.
                out_block = [f"@param[out] {out_param}"]
                kept.append(out_block)
            values.append(block)
        elif EXCEPTION_TAG_RE.match(head):
            converted = _exception_to_retval(block)
            # An exception line with no EX_ value in it (`@exception None`)
            # can't be mapped, so it stays where the author put it.
            (exceptions if converted else kept).append(converted or block)
        else:
            kept.append(block)

    for block in values:
        out_block.extend(_retval_to_list_item(block))

    lines: list[str] = [line for block in kept for line in block]
    while lines and not lines[-1].strip():
        lines.pop()

    status_doc = []
    if not any(RETURNS_TAG_RE.match(block[0]) for block in kept):
        if any("EX_NONE" in block[0] for block in exceptions):
            # The author already documented the success status; don't repeat it.
            summary = "one of the values below."
        elif exceptions:
            summary = f"{BINDER_STATUS}::EX_NONE on success, or one of the values below."
        else:
            summary = f"{BINDER_STATUS}::EX_NONE on success."
        status_doc = [f"@returns {BINDER_STATUS} - {summary}"]

    trailing = status_doc + [line for block in exceptions for line in block]
    if lines and trailing:
        lines.append("")
    lines += trailing
    while lines and not lines[-1].strip():
        lines.pop()
    return lines


def _tag_blocks(body: list[str]) -> list[list[str]]:
    """Split a comment body into blocks, one per Doxygen tag.

    Anything that isn't a tag line - the description, wrapped tag text, blank
    separators - belongs to the block it follows.
    """
    blocks: list[list[str]] = []
    for text in body:
        if TAG_LINE_RE.match(text) or not blocks:
            blocks.append([text])
        else:
            blocks[-1].append(text)
    return blocks


def _retag(block: list[str], tag: re.Pattern[str], replacement: str) -> list[str]:
    """Swap a block's leading tag, keeping the wrapped text aligned under it."""
    head = tag.sub(replacement, block[0], count=1).rstrip()
    shift = len(replacement) - len(tag.match(block[0]).group(0))
    return [head, *(_shift(line, shift) for line in block[1:])]


def _shift(line: str, columns: int) -> str:
    """Move a wrapped continuation line `columns` to the right (or left)."""
    if not line.strip() or columns == 0:
        return line
    if columns > 0:
        return " " * columns + line
    return line[: len(line) - len(line.lstrip())][:columns] + line.lstrip()


def _exception_to_retval(block: list[str]) -> list[str] | None:
    """`@exception <any spelling of>EX_FOO <text>` -> `@retval <Status>::EX_FOO <text>`."""
    remainder = EXCEPTION_TAG_RE.match(block[0]).group(1)
    status = STATUS_VALUE_RE.search(remainder)
    if status is None:
        return None
    text = remainder[status.end() :].strip()
    head = f"@retval {BINDER_STATUS}::{status.group(0)}"
    shift = len(head) - (len(block[0]) - len(remainder) + status.end())
    return [f"{head} {text}".rstrip(), *(_shift(line, shift) for line in block[1:])]


def _retval_to_list_item(block: list[str]) -> list[str]:
    """`@retval <value> <text>` -> a list item under the out parameter."""
    match = RETVAL_TAG_RE.match(block[0])
    text = block[0][match.end() :].strip()
    return [f"  - {match.group(1)}: {text}".rstrip(), *(f"    {line.strip()}" for line in block[1:] if line.strip())]


def read_text(path: Path) -> str:
    """Read a source file, tolerating the odd latin-1 byte in an AIDL comment."""
    data = path.read_bytes()
    try:
        return data.decode("utf-8")
    except UnicodeDecodeError:
        return data.decode("latin-1")


def strip_code(line: str) -> str:
    """Drop string literals and trailing comments so braces can be counted."""
    line = CPP_STRING_RE.sub('""', line)
    line = re.sub(r"//.*$", "", line)
    return re.sub(r"/\*.*?\*/", "", line)


def _strip_line_comment(text: str) -> str:
    """Drop a trailing `//` comment, leaving any `//` inside a string literal alone."""
    in_string = False
    index = 0
    while index < len(text):
        char = text[index]
        if in_string and char == "\\":
            index += 2
            continue
        if char == '"':
            in_string = not in_string
        elif not in_string and text.startswith("//", index):
            return text[:index]
        index += 1
    return text


# -------------------------------------------------------------------------
# AIDL parsing
# -------------------------------------------------------------------------


def parse_aidl(path: Path) -> AidlFile:
    """Extract the package, file documentation and every type from one AIDL file."""
    return _AidlParser(path).parse()


class _AidlParser:
    """Scanner for the AIDL subset used by these interfaces.

    Declarations are accumulated character by character rather than line by
    line, because a declaration and its braces do not line up: `interface I`
    opens its body on the next line, and a method's parameters can be wrapped
    over several. A statement ends at `;`, at `{`/`}`, or - inside an enum -
    at a `,`.
    """

    def __init__(self, path: Path):
        self.path = path
        self.file = AidlFile(path)
        # (type or None for a non-type block, brace depth of its body)
        self.frames: list[tuple[TypeDoc | None, int]] = []
        self.depth = 0
        self.parens = 0
        self.in_string = False
        self.statement = ""
        self.statement_line = 0
        self.statement_doc: Doc | None = None
        self.pending_doc: Doc | None = None
        self.line_doc: Doc | None = None

    def parse(self) -> AidlFile:
        lines = read_text(self.path).splitlines()
        index = 0
        while index < len(lines):
            raw = lines[index]
            stripped = raw.strip()
            lineno = index + 1
            index += 1

            if not stripped or stripped.startswith("//"):
                continue

            if stripped.startswith("/**") or stripped.startswith("/*!"):
                block = [raw]
                while "*/" not in block[-1] and index < len(lines):
                    block.append(lines[index])
                    index += 1
                block[0] = re.sub(r"^(\s*)/\*[*!]<?", r"\1/**", block[0])
                self._add_doc(Doc(block))
                continue

            if stripped.startswith("/*"):
                # License header or other non-Doxygen block comment.
                while "*/" not in stripped and index < len(lines):
                    stripped = lines[index].strip()
                    index += 1
                continue

            # `int intValue; /**< ... */` documents the declaration it follows,
            # so it has to be in hand before the statement is flushed.
            trailing = AIDL_TRAILING_DOC_RE.search(stripped) or AIDL_TRAILING_LINE_DOC_RE.search(stripped)
            if trailing:
                self.line_doc = Doc([f"/** {trailing.group(1)} */"])
                stripped = stripped[: trailing.start()].rstrip()
            # Whatever `//` comment is left is not documentation, and must not
            # reach the scanner: its text would become part of the declaration.
            stripped = _strip_line_comment(stripped).rstrip()
            self._scan(stripped, lineno)
            # A trailing block on an unterminated declaration - the last enum
            # value, which needs no comma - must survive to the flush.
            if self.line_doc and self.statement.strip() and self.statement_doc is None:
                self.statement_doc = self.line_doc
            self.line_doc = None

        return self.file

    def _add_doc(self, doc: Doc) -> None:
        # An `@file` tag makes the block file documentation wherever it sits,
        # which is how Doxygen reads it too. Some of these blocks come before
        # the `package` statement, others after the imports.
        if any(text.strip().startswith("@file") for text in doc.body()):
            self.file.file_doc = doc
            return
        # A block that arrives mid-statement sits between the annotations and
        # the declaration; the nearest block wins, as it does in Doxygen.
        if self.statement.strip():
            self.statement_doc = doc
        else:
            self.pending_doc = doc

    def _scan(self, text: str, lineno: int) -> None:
        for char in text:
            if self.in_string:
                self.statement += char
                self.in_string = char != '"'
            elif char == '"':
                self._begin(lineno)
                self.statement += char
                self.in_string = True
            elif char in "()":
                self._begin(lineno)
                self.statement += char
                self.parens += 1 if char == "(" else -1
                self.parens = max(self.parens, 0)
            elif self.parens:
                self.statement += char
            elif char == "{":
                self._open()
            elif char == "}":
                self._flush()  # a last enum value needs no trailing comma
                self._close()
            elif char == ";" or (char == "," and self._in_enum()):
                self._flush()
            elif char.strip() or self.statement.strip():
                self._begin(lineno)
                self.statement += char
        # The newline itself separates the parts of a wrapped declaration.
        self.statement += " "

    def _begin(self, lineno: int) -> None:
        """Claim the pending documentation when a statement starts."""
        if not self.statement.strip():
            self.statement_line = lineno
            self.statement_doc = self.pending_doc
            self.pending_doc = None

    def _take(self) -> tuple[str, Doc | None]:
        text = re.sub(r"\s+", " ", self.statement).strip()
        while True:
            shortened = AIDL_ANNOTATION_RE.sub("", text)
            if shortened == text:
                break
            text = shortened
        doc, self.statement, self.statement_doc = self.statement_doc or self.line_doc, "", None
        return text, doc

    def _open(self) -> None:
        text, doc = self._take()
        self.depth += 1
        match = AIDL_TYPE_RE.match(text)
        if match is None:
            self.frames.append((None, self.depth))
            return
        parent = next((type_doc for type_doc, _ in reversed(self.frames) if type_doc is not None), None)
        qualified_name = f"{parent.qualified_name}::{match.group(2)}" if parent else match.group(2)
        type_doc = TypeDoc(
            kind=match.group(1),
            name=match.group(2),
            qualified_name=qualified_name,
            doc=doc,
            line=self.statement_line,
            file=self.path,
        )
        self.file.types[type_doc.qualified_name] = type_doc
        self.frames.append((type_doc, self.depth))

    def _close(self) -> None:
        self.depth -= 1
        while self.frames and self.frames[-1][1] > self.depth:
            self.frames.pop()

    def _flush(self) -> None:
        text, doc = self._take()
        if not text:
            return
        enclosing = self.frames[-1][0] if self.frames else None
        if enclosing is None:
            if text.startswith("package "):
                self.file.package = text.split(None, 1)[1].strip()
                # A block before the package statement documents the file even
                # without an `@file` tag; one with a tag is already captured.
                self.file.file_doc = self.file.file_doc or doc
            return
        name = _aidl_member_name(text, enclosing.kind)
        if name:
            enclosing.members[name] = Member(
                name=name,
                kind=_member_kind(text, enclosing.kind),
                declaration=text,
                doc=doc,
                line=self.statement_line,
            )

    def _in_enum(self) -> bool:
        return bool(self.frames) and self.frames[-1][0] is not None and self.frames[-1][0].kind == "enum"


def _member_kind(declaration: str, enclosing_kind: str) -> str:
    if enclosing_kind == "enum":
        return "enum value"
    if declaration.startswith("const "):
        return "constant"
    return "method" if "(" in declaration else "field"


def _aidl_member_name(decl: str, enclosing_kind: str) -> str | None:
    """Name of the member declared by `decl`, or None if it isn't one."""
    if enclosing_kind == "enum":
        match = AIDL_ENUM_MEMBER_RE.match(decl)
        return match.group(1) if match else None
    if "(" in decl:
        match = AIDL_METHOD_RE.search(decl)
        return match.group(1) if match else None
    match = AIDL_FIELD_RE.search(decl)
    return match.group(1) if match else None


def load_docs(aidl_dir: Path) -> dict[str, PackageDocs]:
    """Map package name -> PackageDocs for a component's AIDL tree."""
    by_package: dict[str, PackageDocs] = {}
    for path in sorted(aidl_dir.rglob("*.aidl")):
        parsed = parse_aidl(path)
        if not parsed.types:
            continue
        package = by_package.setdefault(parsed.package, PackageDocs())
        package.types.update(parsed.types)
        if parsed.file_doc is not None:
            package.file_docs[path.stem] = parsed.file_doc
    return by_package


# -------------------------------------------------------------------------
# Generated header injection
# -------------------------------------------------------------------------


def strip_injected(lines: list[str]) -> list[str]:
    """Remove every previously injected block, marker line included."""
    out: list[str] = []
    index = 0
    while index < len(lines):
        stripped = lines[index].strip()
        marked = stripped == MARKER
        # `/** @aidl-doc ...` is the marker's earlier in-comment form; still
        # recognised so trees injected by it can be cleaned up.
        if marked or (stripped.startswith("/**") and SENTINEL in stripped):
            if marked:
                index += 1
                if index >= len(lines) or not lines[index].strip().startswith("/**"):
                    continue
            while index < len(lines) and "*/" not in lines[index]:
                index += 1
            index += 1
            continue
        out.append(lines[index])
        index += 1
    return out


@dataclass
class Frame:
    """A C++ type body we are currently inside."""

    type_doc: TypeDoc | None
    depth: int
    is_enum: bool
    scope_name: str
    injected: set[str] = field(default_factory=set)


def inject_header(
    path: Path,
    types: dict[str, TypeDoc],
    stats: Stats,
    strip_only: bool,
    dry_run: bool,
    verbose: bool,
    file_doc: Doc | None = None,
) -> bool:
    """Rewrite one generated header. Returns True if its content changed."""
    original = read_text(path)
    lines = strip_injected(original.splitlines())
    matched: set[str] = set()

    if strip_only:
        return _write(path, original, lines, dry_run)

    out: list[str] = []
    frames: list[Frame] = []
    pending: Frame | None = None
    depth = 0

    for raw in lines:
        code = strip_code(raw)
        stripped = code.strip()

        if file_doc is not None and stripped.startswith("#pragma once"):
            out.append(raw)
            out.extend(file_doc.render("", file_name=path.name))
            stats.types_documented += 1
            file_doc = None
            continue

        type_match = CPP_TYPE_OPEN_RE.match(code)
        if type_match and not stripped.endswith(";"):
            indent, keyword, name = type_match.groups()
            parent_scope = frames[-1].scope_name if frames else ""
            scope_name = f"{parent_scope}::{name}" if parent_scope else name
            type_doc = types.get(scope_name)
            if type_doc is None and name == "Tag" and frames and frames[-1].type_doc and frames[-1].type_doc.kind == "union":
                # aidl-cpp lowers union fields to a `Tag` enumerator each, so
                # the union's field docs belong on the Tag values.
                parent = frames[-1].type_doc
                type_doc = TypeDoc(kind="union", name="Tag", qualified_name=parent.qualified_name, members=parent.members)
            pending = Frame(type_doc=type_doc, depth=0, is_enum=keyword.startswith("enum"), scope_name=scope_name)
            if type_doc is not None and type_doc.doc is not None:
                out.extend(type_doc.doc.render(indent))
                stats.types_documented += 1
                matched.add(type_doc.qualified_name)
        elif frames and frames[-1].type_doc is not None and depth == frames[-1].depth:
            frame = frames[-1]
            name = _cpp_member_name(code, frame.is_enum)
            if name and name not in frame.injected:
                member = frame.type_doc.members.get(name)
                doc = member.doc if member else None
                if doc is not None:
                    indent = raw[: len(raw) - len(raw.lstrip())]
                    out_param, binder_method = _binder_signature(stripped)
                    out.extend(doc.render(indent, out_param, binder_method))
                    if binder_method and out_param is None and doc.documents_return():
                        # The AIDL documents a return value the method does not
                        # have, so there is nothing to map it onto - the fix
                        # belongs in the AIDL source.
                        stats.return_drift.append(f"{path.name}: {frame.type_doc.qualified_name}.{name}")
                    frame.injected.add(name)
                    stats.members_documented += 1
                    matched.add(f"{frame.type_doc.qualified_name}.{name}")

        out.append(raw)

        for char in code:
            if char == "{":
                depth += 1
                if pending is not None:
                    pending.depth = depth
                    frames.append(pending)
                    pending = None
            elif char == "}":
                depth -= 1
                while frames and frames[-1].depth > depth:
                    frames.pop()

    _report_unmatched(path, types, matched, stats)

    return _write(path, original, out, dry_run)


def _binder_signature(declaration: str) -> tuple[str | None, bool]:
    """(out parameter, is a Status-returning method) for a generated declaration."""
    if BINDER_STATUS not in declaration or "(" not in declaration.split("=", 1)[0]:
        return None, False
    return (AIDL_RETURN_PARAM if AIDL_RETURN_PARAM in declaration else None), True


def _strip_attributes(code: str) -> str:
    """Remove `__attribute__((...))` clauses, which aidl-cpp adds to deprecated members."""
    while (start := code.find("__attribute__")) >= 0:
        end = code.find("(", start)
        if end < 0:
            break
        depth = 0
        while end < len(code):
            depth += (code[end] == "(") - (code[end] == ")")
            end += 1
            if depth == 0:
                break
        code = code[:start] + code[end:]
    return code


def _cpp_member_name(code: str, is_enum: bool) -> str | None:
    """Name of the member declared on this line of generated C++."""
    code = _strip_attributes(code)
    stripped = code.strip()
    if not stripped or stripped.startswith("}") or CPP_SKIP_MEMBER_RE.match(code):
        return None
    if is_enum:
        match = CPP_ENUM_MEMBER_RE.match(code)
        return match.group(1) if match else None
    # Only what precedes the initialiser: a default such as
    # `= SignalDetectMode(0)` would otherwise read as a method call, and the
    # generated parcelables default every enum-typed field that way.
    head = stripped.split("=", 1)[0].strip()
    if "(" in head:
        match = CPP_METHOD_RE.search(head)
        return match.group(1) if match else None
    if not stripped.endswith(";"):
        return None
    match = CPP_FIELD_RE.search(head)
    return match.group(1) if match else None


def _report_unmatched(path: Path, types: dict[str, TypeDoc], matched: set[str], stats: Stats) -> None:
    """Note AIDL docs that found no home in this header (drift indicator)."""
    stem = path.stem
    for qualified_name, type_doc in types.items():
        if type_doc.file is None or type_doc.file.stem != stem:
            continue
        if type_doc.doc is not None and qualified_name not in matched:
            stats.unmatched.append(f"{path.name}: {qualified_name}")
        for name in type_doc.documented_members():
            member_name = f"{qualified_name}.{name}"
            if member_name not in matched:
                stats.unmatched.append(f"{path.name}: {member_name}")


def _write(path: Path, original: str, lines: list[str], dry_run: bool) -> bool:
    content = "\n".join(lines)
    if original.endswith("\n"):
        content += "\n"
    if content == original:
        return False
    if not dry_run:
        path.write_text(content, encoding="utf-8")
    return True


def is_binder_machinery(path: Path, types: dict[str, TypeDoc]) -> bool:
    """True for Bn*/Bp* stub/proxy headers, unless an AIDL type has that name."""
    return bool(re.match(r"^(Bn|Bp)[A-Z]", path.stem)) and path.stem not in types


def process_tree(aidl_dir: Path, include_dir: Path, stats: Stats, strip_only: bool, dry_run: bool, verbose: bool) -> None:
    """Inject (or strip) documentation across one component's generated headers."""
    docs = load_docs(aidl_dir)

    for header in sorted(include_dir.rglob("*.h")):
        package = docs.get(".".join(header.relative_to(include_dir).parent.parts), PackageDocs())
        if not package.types and not strip_only:
            continue
        if is_binder_machinery(header, package.types):
            continue
        file_doc = package.file_docs.get(header.stem)
        if inject_header(header, package.types, stats, strip_only, dry_run, verbose, file_doc):
            stats.files_changed += 1
            stats.changed_headers.append(header)
            if verbose:
                print(f"   {'would update' if dry_run else 'updated'} {header}")


# -------------------------------------------------------------------------
# Validation
# -------------------------------------------------------------------------


@dataclass(order=True)
class Finding:
    """One documentation problem, against the AIDL that has to change."""

    path: Path
    line: int
    category: str
    message: str


@dataclass
class Report:
    """Documentation problems found by --validate."""

    findings: list[Finding] = field(default_factory=list)

    def add(self, path: Path, line: int, category: str, message: str) -> None:
        self.findings.append(Finding(path, line, category, message))

    def show(self, root: Path) -> None:
        if not self.findings:
            print("✅ AIDL documentation is complete and matches the generated headers")
            return

        for path in sorted({f.path for f in self.findings}):
            entries = sorted(f for f in self.findings if f.path == path)
            print(f"❌ {_label(path, root)} ({len(entries)} issue(s))")
            for finding in entries:
                location = f"{finding.line}: " if finding.line else ""
                print(f"     {location}[{finding.category}] {finding.message}")

        print(f"\n❌ {len(self.findings)} documentation issue(s) - {_breakdown(self.findings)}")


def _label(path: Path, root: Path) -> Path:
    try:
        return path.relative_to(root)
    except ValueError:
        return path


def _breakdown(findings: list[Finding]) -> str:
    counts: dict[str, int] = {}
    for finding in findings:
        counts[finding.category] = counts.get(finding.category, 0) + 1
    return ", ".join(f"{category}: {count}" for category, count in sorted(counts.items()))


def validate_tree(aidl_dir: Path, include_dir: Path | None, report: Report) -> None:
    """Check AIDL coverage, generated declaration matching, and header freshness."""
    # (type, member) -> where it is declared, so a mismatch found in a header
    # can be reported against the AIDL the author has to edit.
    locations: dict[tuple[str, str], tuple[Path, int]] = {}

    for path in sorted(aidl_dir.rglob("*.aidl")):
        parsed = parse_aidl(path)
        for type_doc in parsed.types.values():
            if type_doc.doc is None and not (parsed.file_doc is not None and type_doc.qualified_name == path.stem):
                report.add(path, type_doc.line, "coverage", f"{type_doc.kind} {type_doc.qualified_name} is not documented")
            locations[("", type_doc.qualified_name)] = (path, type_doc.line)
            for member in type_doc.members.values():
                locations[(type_doc.qualified_name, member.name)] = (path, member.line)
                _validate_member(path, type_doc, member, report)

    if include_dir is None or not include_dir.is_dir():
        # Nothing generated yet, so the AIDL -> header cross-check is skipped;
        # the coverage checks above stand on their own.
        return

    # Run the injection over the generated headers without writing anything:
    # a documented member that finds no declaration is documentation drift.
    stats = Stats()
    process_tree(aidl_dir, include_dir, stats, strip_only=False, dry_run=True, verbose=False)
    for header in stats.changed_headers:
        report.add(
            header,
            0,
            "headers",
            "would change during reinjection because documentation is missing or stale; rerun the injector",
        )
    for entry in stats.unmatched:
        header, _, qualified = entry.partition(": ")
        type_name, _, member_name = qualified.rpartition(".")
        path, line = locations.get((type_name, member_name), (include_dir / header, 0))
        report.add(path, line, "headers", f"{qualified} is documented but is not declared in {header}")


def _validate_member(path: Path, type_doc: TypeDoc, member: Member, report: Report) -> None:
    if member.doc is None:
        report.add(path, member.line, "coverage", f"{member.kind} {type_doc.qualified_name}.{member.name} is not documented")
        return
    if member.kind != "method":
        return

    where = f"{type_doc.qualified_name}.{member.name}"
    declared = _aidl_params(member.declaration)
    documented = _documented_params(member.doc)
    for name in declared:
        if name not in documented:
            report.add(path, member.line, "params", f"{where}: parameter '{name}' is not documented")
    for name in documented:
        if name not in declared:
            report.add(path, member.line, "params", f"{where}: documents unknown parameter '{name}'")

    returns_value = _aidl_returns_value(member.declaration)
    if returns_value and not member.doc.documents_return():
        report.add(path, member.line, "returns", f"{where}: return value is not documented")
    if not returns_value and member.doc.documents_return():
        report.add(path, member.line, "returns", f"{where}: documents a return value but returns void")


def _aidl_params(declaration: str) -> list[str]:
    """Parameter names of an AIDL method declaration, in order."""
    inner = declaration[declaration.find("(") + 1 : declaration.rfind(")")]
    parts: list[str] = [""]
    depth = 0
    for char in inner:
        depth += (char == "<") - (char == ">")
        if char == "," and depth == 0:
            parts.append("")
        else:
            parts[-1] += char
    return [words[-1] for part in parts if (words := re.findall(r"\w+", part))]


def _documented_params(doc: Doc) -> list[str]:
    """Parameter names the documentation block claims to describe."""
    names = []
    for text in doc.body():
        match = DOC_PARAM_RE.match(text.strip())
        if match:
            names.append(match.group(1))
    return names


def _aidl_returns_value(declaration: str) -> bool:
    """True if the AIDL method returns something other than void."""
    tokens = declaration.split("(", 1)[0].replace("oneway", " ").split()
    return len(tokens) >= 2 and tokens[-2] != "void"


def discover_components(repo_root: Path, version: str) -> list[str]:
    """Components with interface metadata for `version`."""
    return sorted(
        path.parent.parent.name
        for path in repo_root.glob(f"*/{version}/interface.yaml")
    )


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description="Inject or validate AIDL Doxygen comments in generated C++ headers.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__.split("Usage:")[-1],
    )
    parser.add_argument("modules", nargs="*", default=[], help="components to process ('all' or omit for every component)")
    parser.add_argument("--repo-root", type=Path, default=Path(__file__).resolve().parent.parent, help="repository root (default: the checkout holding this script)")
    parser.add_argument("--version", default="current", help="version directory to process (default: current)")
    parser.add_argument("--aidl-dir", type=Path, help="explicit AIDL tree, bypassing component discovery (requires --include-dir)")
    parser.add_argument("--include-dir", type=Path, help="explicit generated header tree (requires --aidl-dir)")
    parser.add_argument("--strip", action="store_true", help="remove injected blocks instead of writing them")
    parser.add_argument(
        "--validate",
        action="store_true",
        help="check AIDL documentation and generated headers without writing; exits 1 on any finding",
    )
    parser.add_argument("--dry-run", action="store_true", help="report what would change without writing")
    parser.add_argument("--verbose", action="store_true", help="list touched headers and unmatched documentation")
    args = parser.parse_args(argv)

    if bool(args.aidl_dir) != bool(args.include_dir):
        parser.error("--aidl-dir and --include-dir must be given together")
    if args.validate and args.strip:
        parser.error("--validate writes nothing, so it cannot be combined with --strip")

    stats = Stats()

    if args.aidl_dir:
        trees = [(args.aidl_dir, args.include_dir)]
    else:
        modules = [m for m in args.modules if m != "all"]
        if not modules:
            modules = discover_components(args.repo_root, args.version)
        trees = []
        for module in modules:
            component = args.repo_root / module / args.version
            if not component.is_dir():
                print(f"❌ AIDL directory not found: {component}", file=sys.stderr)
                return 1
            include_dir = component / "include"
            # Validation only needs the AIDL, so a component whose bindings
            # have not been generated yet is still worth checking.
            if not include_dir.is_dir() and not args.validate:
                # Nothing generated for this component (e.g. a build that
                # targeted a single module) - not an error.
                if args.verbose:
                    print(f"   skipping {module}: no {include_dir.relative_to(args.repo_root)}")
                continue
            trees.append((component, include_dir))

    if args.validate:
        report = Report()
        for aidl_dir, include_dir in trees:
            if not aidl_dir.is_dir():
                print(f"❌ AIDL directory not found: {aidl_dir}", file=sys.stderr)
                return 1
            validate_tree(aidl_dir, include_dir, report)
        report.show(args.repo_root)
        return 1 if report.findings else 0

    for aidl_dir, include_dir in trees:
        if not aidl_dir.is_dir():
            print(f"❌ AIDL directory not found: {aidl_dir}", file=sys.stderr)
            return 1
        if not include_dir.is_dir():
            print(f"❌ Generated header directory not found: {include_dir}", file=sys.stderr)
            return 1
        process_tree(aidl_dir, include_dir, stats, args.strip, args.dry_run, args.verbose)

    verb = "would be" if args.dry_run else ""
    if args.strip:
        print(f"🧹 Removed injected documentation from {stats.files_changed} header(s){' (dry run)' if args.dry_run else ''}")
    else:
        print(
            f"📝 Injected {stats.types_documented} type and {stats.members_documented} member comment(s) "
            f"into {stats.files_changed} header(s){' (dry run)' if args.dry_run else ''}"
        )
    if args.verbose and stats.unmatched:
        print(f"ℹ️  {len(stats.unmatched)} documented AIDL member(s) had no matching declaration{(' ' + verb).rstrip()}:")
        for entry in stats.unmatched:
            print(f"     {entry}")
    if args.verbose and stats.return_drift:
        print(f"ℹ️  {len(stats.return_drift)} method(s) document a return value but return nothing in AIDL:")
        for entry in stats.return_drift:
            print(f"     {entry}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
