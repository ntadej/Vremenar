fastlane documentation
----

# Installation

Make sure you have the latest version of the Xcode command line tools installed:

```sh
xcode-select --install
```

For _fastlane_ installation instructions, see [Installing _fastlane_](https://docs.fastlane.tools/#installing-fastlane)

# Available Actions

## Mac

### mac testbuild

```sh
[bundle exec] fastlane mac testbuild
```

Make a test

### mac developer_id_build

```sh
[bundle exec] fastlane mac developer_id_build
```

Make a developer ID build

### mac app_store_build

```sh
[bundle exec] fastlane mac app_store_build
```

Make a store build

----


## iOS

### ios prepare_qt

```sh
[bundle exec] fastlane ios prepare_qt
```

Prepare Qt

### ios prepare_qt5

```sh
[bundle exec] fastlane ios prepare_qt5
```

Prepare Qt5

### ios prepare_qt6

```sh
[bundle exec] fastlane ios prepare_qt6
```

Prepare Qt6

### ios testbuild

```sh
[bundle exec] fastlane ios testbuild
```

Make a development build (Qt5)

### ios testbuild_qt6

```sh
[bundle exec] fastlane ios testbuild_qt6
```

Make a development build (Qt6)

----

This README.md is auto-generated and will be re-generated every time [_fastlane_](https://fastlane.tools) is run.

More information about _fastlane_ can be found on [fastlane.tools](https://fastlane.tools).

The documentation of _fastlane_ can be found on [docs.fastlane.tools](https://docs.fastlane.tools).
