#!/bin/bash
#
# setup-env.sh - Initialize Yocto build environment for Orange Pi R1
#

# Stop on error
set -e

# Where this script is located (project root)
PROJECT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "$PROJECT_DIR"

BUILD_DIR="$PROJECT_DIR/build"
POKY_DIR="$PROJECT_DIR/poky"

# Check submodules
if [ ! -d "$POKY_DIR" ]; then
    echo ">>> Poky submodule not found - update submodules..."
    git submodule update --init --recursive
fi

mkdir -p "$BUILD_DIR"
# Check config files
if [ ! -d "$BUILD_DIR/conf" ]; then
    echo ">>> First time setup - copying default conf files..."
    mkdir -p "$BUILD_DIR/conf"
    cp "$PROJECT_DIR/conf/local.conf" "$BUILD_DIR/conf/local.conf"
    cp "$PROJECT_DIR/conf/bblayers.conf" "$BUILD_DIR/conf/bblayers.conf"
fi

# Source Poky environment
echo ">>> Setting up Yocto environment..."
source "$POKY_DIR/oe-init-build-env" "$BUILD_DIR"