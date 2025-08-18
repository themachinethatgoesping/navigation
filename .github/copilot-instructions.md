# navigation

Navigation library for interpolating and transforming navigation data, built with C++20 and Meson. Provides C++ library with Python bindings for handling GPS, NMEA, and sensor positioning data.

**ALWAYS reference these instructions first and fallback to search or bash commands only when you encounter unexpected information that does not match the info here.**

## Working Effectively

Bootstrap, build, and test the repository in the following order:

### Required Dependencies
```bash
sudo apt update
sudo DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential ccache pkg-config cmake python3-pip libboost-all-dev libcurl4-openssl-dev libeigen3-dev
pip install meson meson-python ninja pytest numpy
sudo pip install meson ninja  # Install system-wide for sudo meson install
```

### Build Process

**CRITICAL NOTE:** The repository currently has compilation issues with subproject dependencies (C++ template/namespace conflicts in the tools subproject). The CI builds successfully on different environments, but local builds may fail.

#### Primary Build Attempt (May Fail Currently)
```bash
# Configure build - NEVER CANCEL: Takes ~20 seconds, pulls dependencies  
meson setup builddir -Dunity=on -Dunity_size=9999999 -Dpython.install_env=auto -Dprefix=/usr/

# Compile project - NEVER CANCEL: Expected 4 minutes 42 seconds, set timeout to 10+ minutes
# NOTE: Currently failing due to subproject compilation issues
meson compile -C builddir/
```

#### Alternative C++-Only Build (If Python Build Fails)
```bash
# Clean setup for C++ only (disables Python bindings)
rm -rf builddir/
meson setup builddir -Dbuild_pythonmodule=disabled -Dprefix=/usr/

# Compile - This may also fail due to tools subproject issues
meson compile -C builddir/

# Run C++ tests if build succeeds
meson test -C builddir/ --print-errorlogs
```

#### If Build Fails - Use Pre-built Installation
If compilation fails, you can still work with the navigation library if it was previously built and installed:
```bash
# Check if library is already available
pkg-config --exists themachinethatgoesping_navigation
echo $?  # Should output 0 if installed

# Test Python bindings (if previously installed)
python3 -c "import themachinethatgoesping.navigation as nav; print('Navigation available')"
```

**CRITICAL TIMING EXPECTATIONS (When Working):**
- **Configuration: ~20 seconds** - Downloads subprojects (geographiclib, fmt, etc.)  
- **Compilation: 4 minutes 42 seconds** - NEVER CANCEL, set timeout to 600+ seconds
- **C++ Tests: 0.4 seconds** - 28 tests should pass
- **Python Tests: 0.6 seconds** - 29 tests should pass

## Validation Scenarios

**ALWAYS test functionality after making changes:**

### Test C++ Library Installation
```bash
# Verify libraries are installed (only works if build succeeded)
pkg-config --exists themachinethatgoesping_navigation
echo $?  # Should output 0 if installed
```

### Test Python Module Functionality (If Available)
```bash
python3 -c "
import themachinethatgoesping.navigation as nav
import themachinethatgoesping.navigation.navtools as navtools
import themachinethatgoesping.navigation.datastructures as ds

# Test geolocation creation
location = ds.GeolocationLatLon(latitude=52.5, longitude=13.4, z=0)
print('Location created:', str(location).split('\n')[0])

# Test distance calculation (Berlin to Munich)  
distance = navtools.compute_latlon_distance_m(52.5, 13.4, 48.1, 11.6)
print(f'Distance: {distance:.1f} meters')

# Test sensor configuration
config = nav.SensorConfiguration()
print('Sensor configuration created successfully')
"
```

Expected output should show location creation, distance ~505913 meters, and successful sensor config.

**Note:** This validation only works if the Python modules were previously built and installed successfully.

### Test Code Formatting
```bash
# Check code formatting (will show violations in current codebase)
clang-format --version  # Should show Ubuntu clang-format version 18+
find src -name "*.cpp" -o -name "*.hpp" | head -3 | xargs clang-format --dry-run
```

## Key Project Structure

```
/
├── meson.build              # Main build configuration
├── meson_options.txt        # Build options (build_pythonmodule, build_tests, etc.)
├── requirements.txt         # Python dependencies (numpy >= 1.26.0)
├── .clang-format           # Code formatting rules
├── src/
│   ├── themachinethatgoesping/navigation/  # C++ library source
│   ├── pymodule/                          # Python binding source
│   └── tests/                             # C++ tests (Catch2)
├── python/tests/                          # Python tests (pytest)
├── subprojects/                           # Meson subprojects (auto-managed)
└── .github/workflows/                     # CI for Linux/Mac/Windows
```

## Common Commands

### Clean Rebuild
```bash
rm -rf builddir/
meson setup builddir -Dunity=on -Dunity_size=9999999 -Dpython.install_env=auto -Dprefix=/usr/
```

### Run Specific Tests
```bash
# Run single C++ test
meson test -C builddir/ --print-errorlogs themachinethatgoesping._navigation.navtools_.test

# Run specific Python test
pytest -v python/tests/test_c_navtools.py
```

### Development Workflow
1. **ALWAYS** run the complete build process after checking out fresh code
2. **ALWAYS** test both C++ and Python functionality after changes
3. Check code formatting with clang-format before committing
4. Run both test suites: `meson test -C builddir/` and `pytest -v`

## Troubleshooting

### Build Issues
- **Current Compilation Failures**: The repository has C++ compilation issues in subprojects (tools dependency) with template/namespace conflicts (xsimd/xtensor)
- **"geographiclib not found"**: Automatically resolved by meson subprojects
- **"eigen3 not found"**: Install with `sudo apt-get install libeigen3-dev`
- **Permission denied during install**: Use `sudo meson install -C builddir/`  
- **Network timeout on subprojects**: Wait longer, dependencies are large
- **Unity build failures**: Try without unity: `meson setup builddir -Dpython.install_env=auto -Dprefix=/usr/`

### Workarounds for Build Failures
If the main build fails:
1. **Use C++ only build**: `meson setup builddir -Dbuild_pythonmodule=disabled`
2. **Check for previous installation**: `pkg-config --list-all | grep themachinethatgoesping`
3. **Use system package manager**: Check if distribution provides packages
4. **Work with CI containers**: The builds work in CI environments (Ubuntu 22.04/24.04, Arch Linux)

### Import Issues
- **"Module not found"**: Ensure `meson install` completed successfully
- **"ImportError"**: Check that numpy is installed: `pip install numpy>=1.26.0`

## Dependencies Overview

**System Dependencies:**
- build-essential, ccache, pkg-config, cmake
- libboost-all-dev, libcurl4-openssl-dev, libeigen3-dev

**Python Dependencies:**
- meson, ninja, pytest, numpy>=1.26.0

**Subprojects (auto-managed):**
- geographiclib (geographic calculations)
- themachinethatgoesping_tools (utility library)  
- fmt, catch2, pybind11, xtensor (various utilities)

**Core Functionality:**
- Navigation data interpolation (lat/lon, local coordinates)
- NMEA 0183 message parsing
- Sensor configuration and positioning
- Geographic calculations and coordinate transformations