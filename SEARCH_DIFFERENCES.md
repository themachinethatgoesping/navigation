# Quick Reference: Differences to Search For

Based on the analysis of GitHub Actions workflow run #18689880133, here are the specific differences you should search for to resolve the segfault in the ubuntu:22.04 job.

## Job URLs
- **FAILING**: https://github.com/themachinethatgoesping/navigation/actions/runs/18689880133/job/53292502472
- **PASSING**: https://github.com/themachinethatgoesping/navigation/actions/runs/18689880133/job/53292502321

## Critical Difference: GCC Version

### ubuntu:22.04 (SEGFAULT)
```yaml
gcc_version: "12"  # ← FORCED GCC 12
```
**Effect**: Installs and forces GCC 12 via:
```bash
sudo apt-get install -y gcc-12 g++-12
export CC=gcc-12
export CXX=g++-12
```

### ghcr.io/.../ubuntu-dep:latest (SUCCESS)
```yaml
gcc_version: ""  # ← Uses container default (likely GCC 11)
```
**Effect**: No GCC installation, uses pre-configured compiler

## Other Environment Differences

### Python Versions
- **ubuntu:22.04**: Python 3.10.12
- **ubuntu-dep:latest**: Python 3.12.3

### Pytest Versions
- **ubuntu:22.04**: pytest 8.4.2
- **ubuntu-dep:latest**: pytest 8.4.0

### Installation Methods
**ubuntu:22.04**: Fresh installation of everything
```bash
apt-get install build-essential ccache pkg-config cmake python3-pip libboost-all-dev libcurl4-openssl-dev
pip install meson meson-python ninja pytest numpy
```

**ubuntu-dep:latest**: Pre-configured container with dependencies
```yaml
# No installation steps - all pre-configured
```

## Symptom Pattern

```
============================== 29 passed in 0.33s ==============================
Segmentation fault (core dumped)
##[error]Process completed with exit code 139.
```

- All 29 tests pass successfully ✓
- Segfault occurs AFTER test completion during cleanup
- Exit code 139 = 128 + 11 (SIGSEGV signal)

## What to Search For

1. **Compiler ABI compatibility issues**
   - GCC 11 vs GCC 12 ABI changes
   - C++ std::string ABI differences
   - Exception handling ABI changes

2. **Python C extension compatibility**
   - nanobind/pybind11 version compatibility with different GCC versions
   - Python 3.10 vs 3.12 C API differences
   - Module cleanup/destructor issues

3. **System library mismatches**
   - libboost ABI compatibility (compiled with GCC 11, linked with GCC 12)
   - libstdc++ version differences
   - GeographicLib symbol conflicts

4. **Known issues**
   - Search for: "nanobind gcc 12 segfault"
   - Search for: "pybind11 ubuntu 22.04 gcc 12"
   - Search for: "python extension gcc version mismatch"
   - Search for: "boost abi gcc 11 gcc 12"

## Immediate Fix to Test

In `.github/workflows/ci-linux.yml`, change line 75:

```yaml
# BEFORE (causes segfault)
gcc_version: "12",

# AFTER (use system default)
gcc_version: "",
```

This will make ubuntu:22.04 use the default GCC 11, matching the system Python and libraries.

## Alternative Fixes

If GCC 12 is required:

1. **Upgrade to Ubuntu 24.04**:
   ```yaml
   container: "ubuntu:24.04"  # Ships with GCC 13
   ```

2. **Use deadsnakes PPA for newer Python**:
   ```bash
   add-apt-repository ppa:deadsnakes/ppa
   apt-get install python3.12 python3.12-dev
   ```

3. **Build Python from source with GCC 12**:
   ```bash
   # This ensures consistent compiler across all components
   CC=gcc-12 CXX=g++-12 ./configure && make && make install
   ```

## How to Debug Further

If removing forced GCC 12 doesn't fix it:

```bash
# Get detailed stack trace
gdb --args python3 -m pytest -v
# Inside gdb: run, then bt on crash

# Check library dependencies
ldd builddir/src/nanomodule/navigation_nanopy.*.so

# Check GCC ABI version
strings builddir/src/nanomodule/navigation_nanopy.*.so | grep GLIBCXX

# Run with memory checker
valgrind --leak-check=full python3 -m pytest -v

# Check for undefined symbols
nm -D builddir/src/nanomodule/navigation_nanopy.*.so | grep -i undef
```

## Related Information

- **Commit that introduced issue**: Check git history around the time GCC 12 was added to ubuntu:22.04 config
- **Ubuntu 22.04 defaults**: GCC 11.4, Python 3.10.12
- **GCC 11→12 breaking changes**: New C++20 features, libstdc++ ABI changes, optimization behavior
