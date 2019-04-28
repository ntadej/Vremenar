# OpenSSL for Android

Set the following environment variables:

- `NDK_PATH` - Android NDK path
- `TOOLCHAINS_PATH` - custom toolchains path


## Prepare toolchains

### x86
```
$NDK_PATH/build/tools/make_standalone_toolchain.py --arch x86 --api 16 --install-dir $TOOLCHAINS_PATH/android-16-x86
```

### armeabi-v7a
```
$NDK_PATH/build/tools/make_standalone_toolchain.py --arch arm --api 16 --install-dir $TOOLCHAINS_PATH/android-16-arm
```

### arm64-v8a
```
$NDK_PATH/build/tools/make_standalone_toolchain.py --arch arm64 --api 21 --install-dir $TOOLCHAINS_PATH/android-21-arm64
```


## Prepare source
```
LC_CTYPE=C sed -i.bak -e 's/-mandroid//' Configure
```


## Build

### x86
```
CROSS_COMPILE=$TOOLCHAINS_PATH/android-16-x86/bin/i686-linux-android- ./Configure android shared
make ANDROID_DEV=$TOOLCHAINS_PATH/android-16-x86/sysroot/usr/ CALC_VERSIONS="SHLIB_COMPAT=; SHLIB_SOVER=" build_libs
```

### armeabi-v7a
```
CROSS_COMPILE=$TOOLCHAINS_PATH/android-16-arm/bin/arm-linux-androideabi- ./Configure android shared
make ANDROID_DEV=$TOOLCHAINS_PATH/android-16-arm/sysroot/usr/ CALC_VERSIONS="SHLIB_COMPAT=; SHLIB_SOVER=" build_libs
```

### arm64-v8a
```
CROSS_COMPILE=$TOOLCHAINS_PATH/android-21-arm64/bin/aarch64-linux-android- ./Configure android shared
make ANDROID_DEV=$TOOLCHAINS_PATH/android-21-arm64/sysroot/usr/ CALC_VERSIONS="SHLIB_COMPAT=; SHLIB_SOVER=" build_libs
```
