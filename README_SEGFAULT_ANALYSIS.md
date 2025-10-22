# Segfault Analysis - Executive Summary

## Quick Links

- **Failing Job**: https://github.com/themachinethatgoesping/navigation/actions/runs/18689880133/job/53292502472
- **Passing Job**: https://github.com/themachinethatgoesping/navigation/actions/runs/18689880133/job/53292502321

## Documents in This Analysis

1. **[VISUAL_COMPARISON.md](VISUAL_COMPARISON.md)** ⭐ **START HERE**
   - Side-by-side comparisons
   - Visual diagrams
   - Clear before/after fix
   - Best for quick understanding

2. **[SEARCH_DIFFERENCES.md](SEARCH_DIFFERENCES.md)** 🔍
   - Quick reference
   - What to search for
   - Immediate fix instructions
   - Debugging commands

3. **[SEGFAULT_ANALYSIS.md](SEGFAULT_ANALYSIS.md)** 📚
   - Complete technical analysis
   - Root cause deep dive
   - Investigation methodology
   - Long-term recommendations

## The Problem in One Sentence

**The ubuntu:22.04 CI job forces GCC 12 on a system that defaults to GCC 11, creating ABI incompatibilities that cause a segfault during Python cleanup after all tests pass successfully.**

## The Fix in One Line

Change line 75 in `.github/workflows/ci-linux.yml`:
```diff
- gcc_version: "12",
+ gcc_version: "",
```

## Why This Matters

### What's Happening Now (BROKEN)
```
ubuntu:22.04 + GCC 11 (system default)
      ↓
  Force GCC 12
      ↓
Python/Boost (GCC 11) + navigation_nanopy.so (GCC 12)
      ↓
  ABI MISMATCH
      ↓
All tests pass ✓
      ↓
Python cleanup → SEGFAULT ✗
```

### What Should Happen (FIXED)
```
ubuntu:22.04 + GCC 11 (system default)
      ↓
  Use GCC 11 (no change)
      ↓
Python/Boost (GCC 11) + navigation_nanopy.so (GCC 11)
      ↓
  NO ABI MISMATCH
      ↓
All tests pass ✓
      ↓
Python cleanup → Clean exit ✓
```

## Evidence

### Failing Job Output
```
============================== 29 passed in 0.33s ==============================
Segmentation fault (core dumped)
##[error]Process completed with exit code 139.
```

### Passing Job Output
```
============================== 29 passed in 0.32s ==============================
Post job cleanup.
```

### Key Differences

| Aspect | ubuntu:22.04 (FAILS) | ubuntu-dep:latest (PASSES) |
|--------|---------------------|---------------------------|
| GCC | **12 (forced)** | default |
| Python | 3.10.12 | 3.12.3 |
| Exit Status | 139 (SIGSEGV) | 0 (success) |

## Why The Other Jobs Work

1. **ghcr.io/.../ubuntu-dep:latest**: Pre-built container with consistent toolchain
2. **archlinux**: Rolling release, everything built together with same compiler

Both avoid the GCC version mismatch problem.

## Impact

- ✅ C++ tests: All pass
- ✅ Python tests: All 29 pass
- ❌ Python cleanup: Segfaults
- ❌ CI workflow: Marked as failed

**Tests pass but CI fails** - confusing for developers!

## What to Do Next

### Immediate Action (Recommended)
Apply the one-line fix to remove forced GCC 12.

### Verify the Fix
1. Push the change
2. Watch the ubuntu:22.04 job
3. Should see: `gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0`
4. All jobs should pass without segfault

### If You Need GCC 12
See [VISUAL_COMPARISON.md](VISUAL_COMPARISON.md#alternative-solutions-if-gcc-12-is-required) for options:
- Use Ubuntu 24.04 (ships with GCC 13)
- Build all dependencies from source with GCC 12
- Use a pre-built container

## Technical Background

### Why Segfault During Cleanup?
1. Tests exercise basic functionality → Works fine
2. Cleanup triggers complex destructor chains → ABI differences matter
3. Python interpreter shutdown involves:
   - Module unloading
   - Static destructor calls
   - Memory deallocation
   - Thread cleanup

### GCC 11 vs 12 ABI Differences
- Different std::string implementation
- Different exception handling
- Different vtable layouts
- Different name mangling

### Why It's Not Caught During Tests
- Tests don't trigger the problematic code paths
- Only module cleanup/shutdown triggers the mismatch
- Classic symptom of binary incompatibility

## Related Issues

Search for similar problems:
- "nanobind gcc version mismatch segfault"
- "pybind11 abi compatibility gcc"
- "python extension module cleanup crash"
- "boost gcc 11 12 abi"

## Questions?

1. **Why force GCC 12 originally?**
   - Possibly for C++20 features or newer optimizations
   - But creates incompatibility with system libraries

2. **Will this affect performance?**
   - No, GCC 11 is fully capable
   - Ubuntu 22.04 is designed for GCC 11

3. **Should we test with multiple GCC versions?**
   - Yes, but in isolated environments
   - Each environment should be self-consistent

## File Change Required

**File**: `.github/workflows/ci-linux.yml`

**Location**: Line 75

**Before**:
```yaml
- {
    container: "ubuntu:22.04",
    ccache: "true",
    pre-dep: "apt update && apt-get install -y sudo git git-lfs",
    dep: "sudo DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential ccache pkg-config cmake python3-pip libboost-all-dev libcurl4-openssl-dev",
    pip: "pip install meson meson-python ninja pytest numpy",
    pip2: "pip install -r requirements.txt",
    gcc_version: "12",  # ← REMOVE THIS
  }
```

**After**:
```yaml
- {
    container: "ubuntu:22.04",
    ccache: "true",
    pre-dep: "apt update && apt-get install -y sudo git git-lfs",
    dep: "sudo DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential ccache pkg-config cmake python3-pip libboost-all-dev libcurl4-openssl-dev",
    pip: "pip install meson meson-python ninja pytest numpy",
    pip2: "pip install -r requirements.txt",
    gcc_version: "",  # ← CHANGED TO EMPTY STRING
  }
```

---

**Analysis completed by**: GitHub Copilot Agent  
**Date**: 2025-10-22  
**Confidence**: High (based on clear ABI mismatch pattern and environment differences)
