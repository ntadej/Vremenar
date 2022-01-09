if ($args.count -eq 0) {
  write-host "No arguments set!"
  exit 1
}

$vremenar = $args[0]
write-host "Vremenar path: $vremenar"

Copy-Item "..\release\Vremenar.exe" "."

if (-Not (Test-Path "setup")) { mkdir "setup" > $null }
Copy-Item "..\setup.iss" "setup\setup.iss"
Copy-Item "$vremenar\resources\Windows\vremenar.ico" "setup\vremenar.ico"

Copy-Item "$vremenar\3rdparty\Sparkle\Windows\lib\WinSparkle.dll" "WinSparkle.dll"

Copy-Item "$env:Qt5_BaseDir\Tools\OpenSSL\Win_x64\bin\libcrypto-1_1-x64.dll" "."
Copy-Item "$env:Qt5_BaseDir\Tools\OpenSSL\Win_x64\bin\libssl-1_1-x64.dll" "."

windeployqt Vremenar.exe --qmldir "$vremenar\src\qml" --angle --no-opengl-sw --no-qmltooling --no-serialport --no-svg

if (Test-Path "geoservices\qtgeoservices_esri.dll") { Remove-Item "geoservices\qtgeoservices_esri.dll" }
if (Test-Path "geoservices\qtgeoservices_itemsoverlay.dll") { Remove-Item "geoservices\qtgeoservices_itemsoverlay.dll" }
if (Test-Path "geoservices\qtgeoservices_mapbox.dll") { Remove-Item "geoservices\qtgeoservices_mapbox.dll" }
if (Test-Path "geoservices\qtgeoservices_nokia.dll") { Remove-Item "geoservices\qtgeoservices_nokia.dll" }

if (Test-Path "iconengines") { Remove-Item -r "iconengines" }

if (Test-Path "imageformats\qgif.dll") { Remove-Item "imageformats\qgif.dll" }
if (Test-Path "imageformats\qicns.dll") { Remove-Item "imageformats\qicns.dll" }
if (Test-Path "imageformats\qico.dll") { Remove-Item "imageformats\qico.dll" }
if (Test-Path "imageformats\qsvg.dll") { Remove-Item "imageformats\qsvg.dll" }
if (Test-Path "imageformats\qtga.dll") { Remove-Item "imageformats\qtga.dll" }
if (Test-Path "imageformats\qtiff.dll") { Remove-Item "imageformats\qtiff.dll" }
if (Test-Path "imageformats\qwbmp.dll") { Remove-Item "imageformats\qwbmp.dll" }
if (Test-Path "imageformats\qwebp.dll") { Remove-Item "imageformats\qwebp.dll" }

if (Test-Path "qmltooling") { Remove-Item -r "qmltooling" }

if (Test-Path "sqldrivers\qsqlodbc.dll") { Remove-Item "sqldrivers\qsqlodbc.dll" }
if (Test-Path "sqldrivers\qsqlpsql.dll") { Remove-Item "sqldrivers\qsqlpsql.dll" }

if (Test-Path "Qt5RemoteObjects.dll") { Remove-Item "Qt5RemoteObjects.dll" }
if (Test-Path "QtQml\RemoteObjects") { Remove-Item -r "QtQml\RemoteObjects" }

if (Test-Path "QtQuick\Controls.2\Fusion") { Remove-Item -r "QtQuick\Controls.2\Fusion" }
if (Test-Path "QtQuick\Controls.2\Imagine") { Remove-Item -r "QtQuick\Controls.2\Imagine" }
if (Test-Path "QtQuick\Controls.2\Material") { Remove-Item -r "QtQuick\Controls.2\Material" }
