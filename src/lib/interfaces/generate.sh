#!/usr/bin/env bash
set -eu -o pipefail

SCRIPT_DIRECTORY="$(cd "$(dirname "$0")";pwd)"

pushd "${SCRIPT_DIRECTORY}/../include/mcm" >> /dev/null

qdbusxml2cpp-qt6 \
  -p displayconfig \
  -i types.h \
  "../../interfaces/org.gnome.Mutter.DisplayConfig.xml"

sed --in-place 's/"displayconfig.h"/"include\/mcm\/displayconfig.h"/g' displayconfig.cpp
mv displayconfig.cpp "${SCRIPT_DIRECTORY}/../"

popd >> /dev/null
