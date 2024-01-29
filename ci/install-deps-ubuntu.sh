#!/usr/bin/env bash
set -eu -o pipefail

add-apt-repository universe
apt update
#apt upgrade --assume-yes
apt install --assume-yes \
  appstream \
  build-essential \
  cmake \
  cmake-extras \
  libfuse2 \
  qt6-base-dev \
  wget

pushd /usr/bin
wget 'https://github.com/linuxdeploy/linuxdeploy/releases/download/1-alpha-20240109-1/linuxdeploy-x86_64.AppImage'
chmod 0755 linuxdeploy-x86_64.AppImage
wget 'https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases/download/1-alpha-20240109-1/linuxdeploy-plugin-qt-x86_64.AppImage'
chmod 0755 linuxdeploy-plugin-qt-x86_64.AppImage
popd
