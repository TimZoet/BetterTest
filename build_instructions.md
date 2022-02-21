# Build Instructions

## Dependencies

The following Conan packages are always required:

1. [pyreq](https://github.com/TimZoet/pyreq)
2. [common](https://github.com/TimZoet/common)
3. [date](https://github.com/HowardHinnant/date)
4. [parsertongue](https://github.com/TimZoet/ParserTongue)

Depending on enabled options, you may also need:

1. [alexandria](https://github.com/TimZoet/Alexandria)
2. [nlohmann_json](https://github.com/nlohmann/json)
3. [pugixml](https://github.com/zeux/pugixml)

## Cloning

This project uses git submodules. Cloning therefore requires an additional flag:

```cmd
git clone git@github.com:TimZoet/BetterTest.git source --recurse-submodules
```

## Exporting to Conan

To export the `bettertest` package to your local Conan cache:

```cmd
cd source
conan export . user/channel
```

## Building and Installing Locally

Generating project files can be done using e.g.:

```cmd
mkdir build && cd build
cmake -G "Visual Studio 16 2019" -A x64 -DCMAKE_INSTALL_PREFIX=..\install ..\source
```

Then build and install using your preferred method.
