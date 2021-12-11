#!/bin/bash -l

source scl_source enable devtoolset-8 rh-git218

set -e
set -x

export VREMENAR_PATH="../source"
export CCACHE_DIR="$GITHUB_WORKSPACE/.ccache"
export PATH="$Qt5_Dir/bin:$PATH"
qmake --version

cd build

qmake $VREMENAR_PATH/Vremenar.pro -spec linux-g++ CONFIG+=release CONFIG+=qtquickcompiler
make -j2
make INSTALL_ROOT=appdir -j2 install ; find appdir/
/root/linuxdeployqt/AppRun \
  appdir/usr/share/applications/vremenar.desktop \
  -qmldir=$VREMENAR_PATH/src/qml/ \
  -extra-plugins=geoservices/libqtgeoservices_maplibre.so,geoservices/libqtgeoservices_osm.so,sqldrivers/libqsqlite.so \
  -bundle-non-qt-libs
