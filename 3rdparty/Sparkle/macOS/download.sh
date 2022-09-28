#!/bin/bash

LOCATION=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

SPARKLE_VERSION="2.2.2"

echo "Downloading Sparkle"
wget -nv -O "${LOCATION}/Sparkle-${SPARKLE_VERSION}.tar.xz" "https://github.com/sparkle-project/Sparkle/releases/download/${SPARKLE_VERSION}/Sparkle-${SPARKLE_VERSION}.tar.xz"
tar -C "${LOCATION}" -xvf "${LOCATION}/Sparkle-${SPARKLE_VERSION}.tar.xz"
