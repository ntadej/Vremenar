#!/bin/bash -l

set -e
set -x

export CCACHE_DIR="$GITHUB_WORKSPACE/.ccache"
export PATH="$QT_ROOT_DIR/bin:$IQTA_TOOLS/CMake/bin:$PATH"
qmake --version
cmake --version

mkdir build && cd build

qt-cmake ../source/ \
  -G Ninja \
  -DCMAKE_BUILD_TYPE="Release" \
  -DCMAKE_C_COMPILER_LAUNCHER="ccache" \
  -DCMAKE_CXX_COMPILER_LAUNCHER="ccache" \
  -DCMAKE_INSTALL_PREFIX="/usr"
ninja
DESTDIR=../install ninja install
