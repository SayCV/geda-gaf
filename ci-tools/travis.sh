#!/bin/sh

set -e

# ================================================================
# Continuous Integration / Deployment Rules
# ================================================================

# ----------------------------------------------------------------
# Build parameters
# ----------------------------------------------------------------

BUILD_DEPS='autopoint bison flex groff guile-2.0-dev
  libgettextpo-dev libgtk2.0-dev libstroke0-dev texinfo'

DEPLOY_BRANCH=master-ng

# ----------------------------------------------------------------
# Build steps
# ----------------------------------------------------------------

travis_before_install () {
    sudo apt-get update -y
    sudo apt-get install -y ${BUILD_DEPS}
}

travis_install () {
    ./autogen.sh
    ./configure --disable-xdg-database
}

travis_script () {
    # Run a full "distcheck" to make sure that no source files have
    # been added but left out of the tarball.  Force $CHANGELOG_BASE
    # to the commit that's being built in order to avoid problems with
    # ChangeLog generation.
    make -skj4 distcheck CHANGELOG_BASE="$TRAVIS_COMMIT"
}

# ----------------------------------------------------------------
# Run the requested build step
# ----------------------------------------------------------------

travis_${@}
