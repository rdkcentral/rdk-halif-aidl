#!/usr/bin/env bash
# tests/manifest/test_plan.sh — the root CMake consumes its inputs correctly.
#
# Configure-only (HALIF_PLAN_ONLY=ON): no Binder SDK and no aidl compiler are
# needed. Each case states the inputs and the exact plan they must produce;
# every plan is also checked for dependency order. With origin/develop
# reachable, the released cohort, the two-commons fixture and a subset are
# cross-checked against develop's tests/yocto/meta-rdk-halif-aidl/halif_plan.py.
#
#   ./tests/manifest/test_plan.sh            # all cases
#   ORACLE=0 ./tests/manifest/test_plan.sh   # skip the halif_plan.py cross-check
set -uo pipefail

ROOT=$(cd "$(dirname "$0")/../.." && pwd)
FX="$ROOT/tests/manifest/fixtures"
WORK=${WORK:-$(mktemp -d)}
mkdir -p "$WORK"
ORACLE=${ORACLE:-1}
pass=0
fail=0

# plan <name> <cmake args...> — prints the plan ("comp ver" per line).
plan() {
    local n=$1; shift
    rm -rf "${WORK:?}/${n:?}"
    cmake -S "$ROOT" -B "$WORK/$n" -DHALIF_PLAN_ONLY=ON "$@" > "$WORK/$n.log" 2>&1 || return 1
    cat "$WORK/$n/halif_plan.txt"
}

# Every node's dependencies (from the configure log) must precede it.
check_order() {
    local n=$1 seen=" " line comp ver deps d
    while IFS= read -r line; do
        [[ "$line" =~ ^--\ \ \ ([a-z0-9_]+)\ ([^ ]+)\ \ \[(.*)\]$ ]] || continue
        comp=${BASH_REMATCH[1]}; ver=${BASH_REMATCH[2]}; deps=${BASH_REMATCH[3]}
        for d in $deps; do
            [[ "$seen" == *" $d "* ]] || { echo "  order: $comp@$ver before its dependency $d"; return 1; }
        done
        seen+="$comp@$ver "
    done < "$WORK/$n.log"
}

expect_plan() {
    local n=$1 want=$2; shift 2
    local got
    if ! got=$(plan "$n" "$@" | tr '\n' '|'); then
        echo "FAIL $n: configure failed"; grep -A3 "CMake Error" "$WORK/$n.log" | sed 's/^/  /'; fail=$((fail+1)); return
    fi
    if [[ "$got" != "$want" ]]; then
        echo "FAIL $n"; echo "  want: $want"; echo "  got:  $got"; fail=$((fail+1)); return
    fi
    if ! check_order "$n"; then echo "FAIL $n (order)"; fail=$((fail+1)); return; fi
    echo "ok   $n"; pass=$((pass+1))
}

expect_fail() {
    local n=$1 pat=$2; shift 2
    if plan "$n" "$@" > /dev/null 2>&1; then
        echo "FAIL $n: configure succeeded, expected '$pat'"; fail=$((fail+1)); return
    fi
    if grep -q "$pat" "$WORK/$n.log"; then echo "ok   $n"; pass=$((pass+1))
    else echo "FAIL $n: expected '$pat'"; grep -A3 "CMake Error" "$WORK/$n.log" | sed 's/^/  /'; fail=$((fail+1)); fi
}

expect_log() {
    local n=$1 pat=$2
    if grep -q "$pat" "$WORK/$n.log"; then echo "ok   $n (log: $pat)"; pass=$((pass+1))
    else echo "FAIL $n: log lacks '$pat'"; fail=$((fail+1)); fi
}

RELEASED='bootreason 0.1.0.0|common 0.2.0.0|deepsleep 0.1.0.0|deviceinfo 0.1.0.0|drm 0.1.0.0|firmwareupdate 0.2.0.0|indicator 0.1.0.0|sensor 0.2.0.0|audiodecoder 0.2.0.0|avclock 0.2.0.1|compositeinput 0.2.0.0|hdmicec 0.1.0.0|hdmiinput 0.1.0.0|hdmioutput 0.1.0.0|videodecoder 0.2.0.1|audiosink 0.2.0.0|avbuffer 0.2.0.0|panel 0.1.0.0|planecontrol 0.2.0.0|videosink 0.2.0.0|audiomixer 0.3.0.0|'

echo "== manifest and selection =="
expect_plan released   "$RELEASED"
expect_plan subset     'common 0.2.0.0|hdmicec 0.1.0.0|'                      -DHALIF_COMPONENTS=hdmicec
expect_plan inline_ver 'common 0.1.0.0|common 0.2.0.0|audiodecoder 0.1.0.0|hdmicec 0.1.0.0|' \
                       "-DHALIF_COMPONENTS=audiodecoder:0.1.0.0;hdmicec"
expect_plan two_commons 'common 0.1.0.0|common 0.2.0.0|audiodecoder 0.1.0.0|hdmicec 0.1.0.0|' \
                       -DHALIF_VERSIONS_FILE="$FX/two-commons.yaml"
expect_plan mixed      'common 0.2.0.0|common current|hdmicec 0.1.0.0|'       -DHALIF_VERSIONS_FILE="$FX/mixed.yaml"
expect_plan unpinned   'common 0.2.0.0|hdmicec 0.1.0.0|'                      -DHALIF_VERSIONS_FILE="$FX/unpinned.yaml"
expect_plan current    'common current|audiodecoder current|avclock current|audiosink current|audiomixer current|' \
                       -DHALIF_VERSIONS_FILE="$ROOT/versions_current.yaml" -DHALIF_COMPONENTS=audiomixer
expect_plan no_manifest 'common 0.2.0.0|avclock 0.2.0.1|'                     -DHALIF_VERSIONS_FILE= -DHALIF_COMPONENTS=avclock
expect_plan legacy     'common 0.2.0.0|hdmicec 0.1.0.0|'                      -DINTERFACE_TARGET=hdmicec -DAIDL_SRC_VERSION=0.1.0.0
expect_log  legacy     "DEPRECATION\|Deprecation"

echo "== a released snapshot whose interface.yaml imports current =="
expect_plan am020      'common current|audiodecoder current|avclock current|audiosink current|audiomixer 0.2.0.0|' \
                       -DHALIF_COMPONENTS=audiomixer:0.2.0.0
expect_log  am020      "needs refreezing"

echo "== rejected inputs =="
expect_fail bad_version   "is not a released snapshot"   -DHALIF_COMPONENTS=hdmicec:9.9.9.9
expect_fail bad_component "is not a component"           -DHALIF_COMPONENTS=nosuch
expect_fail bad_manifest  "HALIF_VERSIONS_FILE not found" -DHALIF_VERSIONS_FILE=/nonexistent.yaml

if [[ "$ORACLE" == 1 ]] && git -C "$ROOT" rev-parse --verify -q origin/develop > /dev/null; then
    echo "== cross-check against develop's halif_plan.py =="
    O="$WORK/oracle"
    rm -rf "${O:?}"; mkdir -p "$O"
    git -C "$ROOT" archive origin/develop | tar -x -C "$O"
    HP="$O/tests/yocto/meta-rdk-halif-aidl/halif_plan.py"
    cp "$FX/two-commons.yaml" "$O/"
    oracle() { # name, cmake-plan-dir, halif_plan args...
        local n=$1 dir=$2; shift 2
        if diff <(sort "$WORK/$dir/halif_plan.txt") <(python3 "$HP" "$@" | sort) > "$WORK/$n.diff"; then
            echo "ok   oracle:$n"; pass=$((pass+1))
        else echo "FAIL oracle:$n"; sed 's/^/  /' "$WORK/$n.diff"; fail=$((fail+1)); fi
    }
    oracle released    released    --versions "$O/versions_released.yaml"
    oracle two_commons two_commons --versions "$O/two-commons.yaml"
    oracle subset      subset      --versions "$O/versions_released.yaml" hdmicec
fi

echo
echo "passed $pass, failed $fail  (work: $WORK)"
[[ $fail -eq 0 ]]
