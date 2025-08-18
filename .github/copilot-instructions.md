# Navigation Library
Navigation library is a C++ library with Python bindings for interpolating and transforming navigation data, GPS coordinates, sensor configurations, and NMEA parsing.

Always reference these instructions first and fallback to search or bash commands only when you encounter unexpected information that does not match the info here.

## Working Effectively

### Bootstrap and Build the Repository
- Install system dependencies:
  - `sudo apt-get update && sudo apt-get install -y build-essential python3-pip pkg-config cmake libboost-all-dev libeigen3-dev libgeographiclib-dev`
- Install Python build tools:
  - `pip install meson ninja pytest numpy`
- Configure the build (downloads dependencies, takes ~18 minutes on first run):
  - `meson setup builddir`
  - **NOTE**: First-time setup may have dependency resolution issues. If meson setup fails, try: `rm -rf builddir subprojects/*/` and retry.
- Build the C++ library (takes ~17 minutes. NEVER CANCEL. Set timeout to 30+ minutes):
  - `meson compile -C builddir/ --default-library=static`
- Run C++ tests (takes <1 second):
  - `meson test -C builddir/ --print-errorlogs`

### Python Development (KNOWN LIMITATION)
- **WARNING**: Python module compilation fails due to GeographicLib static library not being compiled with -fPIC
- Python tests cannot run: `pytest -v` will fail with "ModuleNotFoundError: No module named 'themachinethatgoesping'"
- This is a system-level GeographicLib packaging issue, not a code issue
- C++ functionality works completely - use C++ tests for validation

### Timing Expectations
- **CRITICAL**: meson setup takes ~18 minutes on first run (downloads dependencies). NEVER CANCEL. Set timeout to 30+ minutes.
- **CRITICAL**: meson compile takes ~17 minutes. NEVER CANCEL. Set timeout to 30+ minutes minimum.
- meson test: <1 second (28 C++ tests)
- Dependencies download: Requires internet access to GitHub, fmt, indicators, etc.
- **First-time setup issues**: Dependency resolution may fail on first run. Clean and retry if needed.

## Validation
- Always run C++ tests after making changes: `meson test -C builddir/ --print-errorlogs`
- All 28 C++ tests should pass (navigation, sensor configuration, coordinate transformations, NMEA parsing)
- Do NOT try to run Python tests - they will fail due to the known GeographicLib linking issue
- Always test key navigation functions by running the specific test categories:
  - Navigation interpolation: check tests `navigationinterpolatorlatlon` and `navigationinterpolatorlocal`
  - Coordinate transformations: check tests for `geolocation*` and `sensordata*` 
  - Sensor configuration: check `sensorconfiguration` test
  - NMEA parsing: check tests in datastructures directory

## Common Tasks

### Repository Structure
```
src/
├── themachinethatgoesping/navigation/  # Main C++ library source
│   ├── datastructures/                 # Coordinate and sensor data structures  
│   ├── nmea_0183/                      # NMEA sentence parsing
│   ├── sensorconfiguration.hpp/.cpp    # Sensor offset management
│   ├── navtools.hpp                    # Navigation utility functions
│   └── *interpolator*.hpp              # Navigation data interpolation
├── tests/                              # C++ unit tests (Catch2)
└── pymodule/                           # Python bindings (pybind11) - BROKEN
python/tests/                           # Python tests - DO NOT USE
.github/workflows/ci-linux.yml          # Working CI configuration
meson.build                             # Main build configuration  
meson_options.txt                       # Build options
```

### Key Library Components
- **Navigation Interpolators**: Interpolate GPS coordinates, heading, speed over time
- **Sensor Configuration**: Manage sensor offsets, rotations, coordinate transformations
- **Data Structures**: Geolocation (LatLon, Local, UTM), sensor data containers
- **NMEA 0183**: Parse common GPS/navigation sentences (GGA, RMC, VTG, etc.)
- **Navigation Tools**: Distance calculations, coordinate conversions

### Build Configuration
- Uses Meson build system (not CMake)
- Automatically downloads ~17 subproject dependencies (fmt, catch2, eigen, boost, etc.)
- Requires C++20 standard
- Dependencies: Boost, Eigen3, GeographicLib, OpenMP
- Supports both static and shared library builds (use static for reliability)

### Troubleshooting
- **GeographicLib linking errors**: Use `--default-library=static` option
- **Network timeouts during setup**: Meson downloads dependencies from multiple sources
- **Long build times**: 17+ minutes is normal for C++ builds with many template-heavy dependencies
- **Python import errors**: Known issue - Python module doesn't build due to GeographicLib PIC problem
- **Missing dependencies**: Install via apt-get, don't try to build them manually

### Development Workflow
1. Always build and run C++ tests before committing changes
2. Focus on C++ functionality - Python bindings are not operational
3. Use existing C++ test patterns in `src/tests/` for new functionality
4. Test coordinate transformations with the existing sensor configuration tests
5. Validate NMEA parsing using the datastructures tests

## Example Commands Summary
```bash
# Complete setup and build
sudo apt-get install -y build-essential python3-pip pkg-config cmake libboost-all-dev libeigen3-dev libgeographiclib-dev
pip install meson ninja pytest numpy
meson setup builddir
meson compile -C builddir/ --default-library=static  # 17+ minutes, NEVER CANCEL
meson test -C builddir/ --print-errorlogs           # <1 second, should show 28 OK

# Clean rebuild if needed
rm -rf builddir
meson setup builddir
# ... repeat build steps
```