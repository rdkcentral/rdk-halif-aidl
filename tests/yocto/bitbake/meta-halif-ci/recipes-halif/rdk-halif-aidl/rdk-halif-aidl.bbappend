# CI: build the branch under test.
#
# The upstream recipe pins branch=develop; point it at the branch we are testing
# (set HALIF_TEST_BRANCH in local.conf, default below) and take its latest commit.
# We fetch rather than use externalsrc on purpose: externalsrc broke fakeroot for
# do_package here (pseudo was inactive, so fixup_perms' lchown got EPERM) and made
# bitbake hash the whole in-repo build tree. Fetching is also what an integrator
# actually does.

HALIF_TEST_BRANCH ??= "feature/661-yocto-per-component-recipes"

SRC_URI = "git://github.com/rdkcentral/rdk-halif-aidl.git;protocol=https;branch=${HALIF_TEST_BRANCH}"
SRCREV = "aeb0e5103a6e85d1ee9ff3f67cfc3663a1ef730f"

# The CI container builds as a non-target uid (crops/poky's pokyuser, 1000). The
# recipe's do_install cp -a preserves that uid, and do_package rejects ownership
# with no matching target user ("host contamination"). Normalise to root here -
# a test-env accommodation, not a recipe change; the packaging logic (PACKAGES /
# FILES / -dbg split) is what we are exercising and it is unaffected.
do_install:append() {
    chown -R root:root ${D}
}
