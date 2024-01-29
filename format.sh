#!/usr/bin/env bash
set -eu -o pipefail
SCRIPT_DIRECTORY="$(cd "$(dirname "$0")";pwd)"

find "${SCRIPT_DIRECTORY}/src" \
  ! -iname 'displayconfig.*' -a \( -iname '*.h' -o -iname '*.cpp' \) \
  -exec clang-format "--style=file:${SCRIPT_DIRECTORY}/.clang-format" -i {} \;
