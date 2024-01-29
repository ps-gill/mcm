#!/usr/bin/env bash
set -eu -o pipefail
ROOT_DIRECTORY="$(cd "$(dirname "$0")/..";pwd)"

CMAKE_BUILD_DIR="${ROOT_DIRECTORY}/cmake-build-release-app-image"
[ -e "$CMAKE_BUILD_DIR" ] && rm -r "$CMAKE_BUILD_DIR"

cmake -D CMAKE_BUILD_TYPE=Release \
      -D CMAKE_INSTALL_PREFIX=/usr \
      -S "$ROOT_DIRECTORY" \
      -B "$CMAKE_BUILD_DIR"

pushd "$CMAKE_BUILD_DIR"
cmake --build "$CMAKE_BUILD_DIR" --config "Release" -- "-j$(nproc)"
DESTDIR=AppDir cmake --install "$CMAKE_BUILD_DIR"
linuxdeploy-x86_64.AppImage --appdir AppDir --output appimage
