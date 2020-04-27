[![Actions Status](https://github.com/Denmey/Terrain/workflows/MacOS/badge.svg)](https://github.com/Denmey/Terrain/actions)
[![Actions Status](https://github.com/Denmey/Terrain/workflows/Windows/badge.svg)](https://github.com/Denmey/Terrain/actions)
[![Actions Status](https://github.com/Denmey/Terrain/workflows/Ubuntu/badge.svg)](https://github.com/Denmey/Terrain/actions)
[![Actions Status](https://github.com/Denmey/Terrain/workflows/Style/badge.svg)](https://github.com/Denmey/Terrain/actions)
[![Actions Status](https://github.com/Denmey/Terrain/workflows/Install/badge.svg)](https://github.com/Denmey/Terrain/actions)
[![codecov](https://codecov.io/gh/Denmey/Terrain/branch/master/graph/badge.svg)](https://codecov.io/gh/Denmey/Terrain)

# Terrain

Description to be written

## Usage

To avoid redundant downloads, it's recommended to set a CPM cache directory, e.g.: `export CPM_SOURCE_CACHE=$HOME/.cache/CPM`.
This will also allow offline configurations if all dependencies are present.
No internet connection is required for building.

### Build and run the standalone target

Use the following command to build and run the executable target.

```bash
cmake -Hstandalone/Terrain -Bbuild/standalone/Terrain
cmake --build build/standalone/Terrain
./build/standalone/Terrain/Terrain
```

### Build and run test suite

Use the following commands from the project's root directory to run the test suite.

```bash
cmake -Htest -Bbuild/test
cmake --build build/test

CTEST_OUTPUT_ON_FAILURE=1 cmake --build build/test --target test
# or simply call the executable: 
./build/test/GreeterTests
```

To collect code coverage information, run CMake with the `-DENABLE_TEST_COVERAGE=1` option.

### Run clang-format

Use the following commands from the project's root directory to run clang-format (must be installed on the host system).

```bash
cmake -Htest -Bbuild/test

# view changes
cmake --build build/test --target format

# apply changes
cmake --build build/test --target fix-format
```

See [Format.cmake](https://github.com/TheLartians/Format.cmake) for more options.
