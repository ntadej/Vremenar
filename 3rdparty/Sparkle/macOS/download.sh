#!/bin/bash

LOCATION=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

SPARKLE_VERSION="2.4.2"

echo "Downloading Sparkle"

set -x

if [[ ! -f "${LOCATION}/Sparkle-${SPARKLE_VERSION}.tar.xz" ]]; then
  wget -nv -O "${LOCATION}/Sparkle-${SPARKLE_VERSION}.tar.xz" "https://github.com/sparkle-project/Sparkle/releases/download/${SPARKLE_VERSION}/Sparkle-${SPARKLE_VERSION}.tar.xz"
fi
tar -C "${LOCATION}" -xf "${LOCATION}/Sparkle-${SPARKLE_VERSION}.tar.xz"
