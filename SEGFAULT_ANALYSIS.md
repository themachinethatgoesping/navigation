# Segfault Analysis: GitHub Actions ubuntu:22.04 Job

## Problem Summary

The GitHub Actions workflow run #18689880133 shows a **segmentation fault in the ubuntu:22.04 job** after all 29 pytest tests pass successfully. The segfault occurs during pytest cleanup/shutdown, **not during test execution**.

- **Failing Job**: https://github.com/themachinethatgoesping/navigation/actions/runs/18689880133/job/53292502472
- **Successful Job**: https://github.com/themachinethatgoesping/navigation/actions/runs/18689880133/job/53292502321

## Key Observations

### Failing Job (ubuntu:22.04)
- Container: `ubuntu:22.04`
- Python: `3.10.12`
- Pytest: `8.4.2`
- GCC: `12` (explicitly set via `gcc_version: "12"`)
- All 29 tests **PASS** successfully
- **Segmentation fault occurs AFTER test completion**:
  ```
  ============================== 29 passed in 0.33s ==============================
  Segmentation fault (core dumped)
  ##[error]Process completed with exit code 139.
  ```

### Successful Job (ghcr.io/themachinethatgoesping/ubuntu-dep:latest)
- Container: `ghcr.io/themachinethatgoesping/ubuntu-dep:latest`
- Python: `3.12.3`
- Pytest: `8.4.0`
- GCC: Not explicitly set (uses default from container)
- All 29 tests **PASS** successfully
- **No segfault** - clean exit

### Successful Job (archlinux)
- Container: `archlinux`
- Python version: Not shown in logs
- GCC: Not explicitly set (uses default from container)
- All tests pass
- **No segfault** - clean exit

## Environment Differences

### Matrix Configuration Comparison

| Aspect | ubuntu:22.04 (FAILING) | ghcr.io/...ubuntu-dep:latest (PASSING) | archlinux (PASSING) |
|--------|----------------------|---------------------------------------|-------------------|
| **Container** | ubuntu:22.04 | ghcr.io/themachinethatgoesping/ubuntu-dep:latest | archlinux |
| **Python Version** | 3.10.12 | 3.12.3 | Unknown |
| **Pytest Version** | 8.4.2 | 8.4.0 | Unknown |
| **GCC Version** | 12 (forced) | default (from container) | default (from container) |
| **ccache** | true | true | false (skipped) |
| **Dependencies** | Installed via apt | Pre-installed in container | Installed via pacman |
| **pip install method** | normal | --break-system-packages | --break-system-packages |

### Dependency Installation Differences

**ubuntu:22.04** (manual installation):
```yaml
pre-dep: "apt update && apt-get install -y sudo git git-lfs"
dep: "sudo DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential ccache pkg-config cmake python3-pip libboost-all-dev libcurl4-openssl-dev"
pip: "pip install meson meson-python ninja pytest numpy"
pip2: "pip install -r requirements.txt"
gcc_version: "12"  # Explicitly forced
```

**ghcr.io/.../ubuntu-dep:latest** (pre-configured):
```yaml
# No pre-dep, dep, or pip commands - dependencies pre-installed
pip2: "pip install -r requirements.txt --break-system-packages"
gcc_version: ""  # Uses default from container
```

**archlinux**:
```yaml
pre-dep: "pacman -Syu --noconfirm; pacman -Syy sudo git git-lfs --noconfirm"
dep: "sudo pacman -Syy --noconfirm base-devel ccache pkg-config cmake python-pip boost curl"
pip: "pip install meson meson-python ninja pytest numpy --break-system-packages"
pip2: "pip install -r requirements.txt --break-system-packages --pre"
gcc_version: ""  # Uses default from container
```

## Root Cause Analysis

The segfault occurs **after pytest completes successfully**, which indicates:

1. **C++ Python Extensions Issue**: The segfault likely occurs during Python interpreter shutdown when cleaning up C++ extension modules (nanobind/pybind11 bindings)
2. **Memory Management**: Double-free or use-after-free in destructor chains during module cleanup
3. **ABI Compatibility**: Potential mismatch between:
   - Python version (3.10.12 vs 3.12.3)
   - GCC version (forced 12 vs container default)
   - Boost library versions
   - Standard library versions

## Most Likely Causes

### 1. GCC 12 on Ubuntu 22.04 + Python 3.10 Combination
The ubuntu:22.04 job **explicitly forces GCC 12**:
```yaml
gcc_version: "12"
```

This creates a potential ABI mismatch:
- Ubuntu 22.04 ships with GCC 11 as default
- Python 3.10.12 system packages are compiled with GCC 11
- Forcing GCC 12 may create incompatibility with system Python libraries
- The nanobind/pybind11 extensions are compiled with GCC 12, but link against Python compiled with GCC 11

### 2. Python Version Differences (3.10 vs 3.12)
- **Failing**: Python 3.10.12
- **Passing**: Python 3.12.3

Python 3.12 made significant internal changes:
- Improved GC and memory management
- Different C API behavior
- Changed extension module lifecycle

### 3. Boost Library Version Mismatch
Different package sources may provide different Boost versions:
- ubuntu:22.04 apt: Boost 1.74
- Pre-built container: Possibly newer Boost version
- ABI changes between Boost versions can cause segfaults

### 4. GeographicLib or Other Dependencies
The build uses a vendored GeographicLib 2.5.2. If the system has another version or if there's a symbol collision, this could cause issues during cleanup.

## Recommendations

### Immediate Actions

1. **Remove forced GCC 12** for ubuntu:22.04:
   ```yaml
   - {
       container: "ubuntu:22.04",
       ccache: "true",
       pre-dep: "apt update && apt-get install -y sudo git git-lfs",
       dep: "sudo DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential ccache pkg-config cmake python3-pip libboost-all-dev libcurl4-openssl-dev",
       pip: "pip install meson meson-python ninja pytest numpy",
       pip2: "pip install -r requirements.txt",
       gcc_version: "",  # <-- REMOVE forced GCC 12
     }
   ```

2. **Alternative: Upgrade to Ubuntu 24.04** which ships with GCC 13 as default

3. **Add debugging output** to identify the exact point of failure:
   ```bash
   pytest -v --tb=short -s
   ```

### Investigation Steps

1. **Run with valgrind** to catch memory errors:
   ```bash
   valgrind --leak-check=full --show-leak-kinds=all python -m pytest -v
   ```

2. **Run with GDB** to get stack trace:
   ```bash
   gdb --args python -m pytest -v
   # Then 'run' and 'bt' on segfault
   ```

3. **Test with different Python versions** on ubuntu:22.04:
   - Try Python 3.11 or 3.12 via deadsnakes PPA
   - Compare behavior

4. **Check library versions**:
   ```bash
   ldd builddir/src/nanomodule/navigation_nanopy.*.so
   strings builddir/src/nanomodule/navigation_nanopy.*.so | grep GLIBCXX
   gcc --version
   python3 --version
   dpkg -l | grep libboost
   ```

### Long-term Solutions

1. **Use consistent build environments**: 
   - Either pre-build containers for all platforms
   - Or build from source consistently across all platforms

2. **Pin dependency versions** in container images

3. **Add AddressSanitizer** to catch memory issues during development:
   ```meson
   project(..., default_options: ['b_sanitize=address'])
   ```

4. **Update CI to test multiple compiler versions** to catch ABI issues early

## Technical Details

### Observed Behavior Pattern

The pattern "all tests pass + segfault on exit" is characteristic of:

1. **Static destruction order fiasco**: C++ objects with static storage duration being destroyed in the wrong order
2. **Python module cleanup**: Extension modules with complex destructor chains
3. **Smart pointer cycles**: Shared/weak pointer cleanup during interpreter shutdown
4. **Thread cleanup**: Threads or thread-local storage not properly joined/cleaned

### Why It Works in Other Environments

- **ghcr.io/.../ubuntu-dep:latest**: Pre-built with consistent toolchain
- **archlinux**: Rolling release with latest GCC, newer Python, consistent ABI

## Conclusion

The segfault in ubuntu:22.04 is most likely caused by **forcing GCC 12 on a system designed for GCC 11**, creating ABI incompatibilities between:
- The compiled C++ extension modules (GCC 12)
- The system Python interpreter and libraries (GCC 11)
- The Boost libraries (GCC 11)

**Primary Recommendation**: Remove `gcc_version: "12"` from the ubuntu:22.04 matrix configuration to use the default GCC 11 that ships with Ubuntu 22.04.

If GCC 12 is required, either:
- Build Python and all dependencies from source with GCC 12
- Use Ubuntu 24.04 which defaults to GCC 13
- Use a pre-built container with consistent toolchain like the other successful jobs
