# Visual Comparison: Failing vs Passing Jobs

## Side-by-Side Workflow Configuration

### ❌ FAILING Job: ubuntu:22.04

```yaml
- {
    container: "ubuntu:22.04",
    ccache: "true",
    pre-dep: "apt update && apt-get install -y sudo git git-lfs",
    dep: "sudo DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential ccache pkg-config cmake python3-pip libboost-all-dev libcurl4-openssl-dev",
    pip: "pip install meson meson-python ninja pytest numpy",
    pip2: "pip install -r requirements.txt",
    gcc_version: "12",  # ← ⚠️ FORCED GCC 12 - THIS IS THE PROBLEM
  }
```

**What happens:**
1. Ubuntu 22.04 ships with GCC 11 as system default
2. All system packages (Python, Boost, etc.) compiled with GCC 11
3. Workflow forces installation of GCC 12
4. C++ extensions compiled with GCC 12
5. **ABI MISMATCH** → Segfault during Python cleanup

---

### ✅ PASSING Job: ghcr.io/.../ubuntu-dep:latest

```yaml
- {
    container: "ghcr.io/themachinethatgoesping/ubuntu-dep:latest",
    ccache: "true",
    pip2: "pip install -r requirements.txt --break-system-packages",
    gcc_version: "",  # ← ✓ Uses container default (consistent toolchain)
  }
```

**What happens:**
1. Container has pre-configured consistent toolchain
2. All dependencies built with same compiler
3. No forced compiler version changes
4. **NO ABI MISMATCH** → Clean exit

---

### ✅ PASSING Job: archlinux

```yaml
- {
    container: "archlinux",
    pre-dep: "pacman -Syu --noconfirm; pacman -Syy sudo git git-lfs --noconfirm",
    dep: "sudo pacman -Syy --noconfirm base-devel ccache pkg-config cmake python-pip boost curl",
    pip: "pip install meson meson-python ninja pytest numpy --break-system-packages",
    pip2: "pip install -r requirements.txt --break-system-packages --pre",
    gcc_version: "",  # ← ✓ Uses container default
  }
```

**What happens:**
1. Rolling release with latest packages
2. All packages built together with same compiler
3. No forced compiler version changes
4. **NO ABI MISMATCH** → Clean exit

---

## Terminal Output Comparison

### ❌ ubuntu:22.04 (FAILING)

```
============================== 29 passed in 0.33s ==============================
Segmentation fault (core dumped)        ← ⚠️ CRASH AFTER TESTS
##[error]Process completed with exit code 139.
```

### ✅ ghcr.io/.../ubuntu-dep:latest (PASSING)

```
============================== 29 passed in 0.32s ==============================
Post job cleanup.                       ← ✓ CLEAN EXIT
##[group]ccache stats
```

### ✅ archlinux (PASSING)

```
============================== 29 passed in 0.33s ==============================
Post job cleanup.                       ← ✓ CLEAN EXIT
```

---

## Environment Variables During Build

### ❌ ubuntu:22.04

```bash
CC=gcc-12           # ← Forced
CXX=g++-12          # ← Forced
# But system Python/Boost compiled with gcc-11!
```

### ✅ Others

```bash
CC=gcc              # ← System default
CXX=g++             # ← System default
# Everything compiled with same toolchain
```

---

## Library Versions

| Component | ubuntu:22.04 ❌ | ubuntu-dep:latest ✅ | archlinux ✅ |
|-----------|----------------|---------------------|--------------|
| **Python** | 3.10.12 | 3.12.3 | Latest |
| **Pytest** | 8.4.2 | 8.4.0 | Latest |
| **GCC** | **12 (forced)** | default | default |
| **ccache** | 4.5.1 | 4.9.1 | Latest |
| **Result** | SEGFAULT | SUCCESS | SUCCESS |

---

## The Problem Visualized

```
ubuntu:22.04 Setup:
┌─────────────────────────────────────────────┐
│ System Python 3.10.12 (compiled with GCC 11)│
├─────────────────────────────────────────────┤
│ System libboost    (compiled with GCC 11)   │
├─────────────────────────────────────────────┤
│ System libstdc++   (compiled with GCC 11)   │
└─────────────────────────────────────────────┘
                    ↓
        Workflow forces GCC 12
                    ↓
┌─────────────────────────────────────────────┐
│ navigation_nanopy.so (compiled with GCC 12) │ ← ABI MISMATCH!
└─────────────────────────────────────────────┘
                    ↓
            SEGMENTATION FAULT
```

```
ubuntu-dep:latest Setup:
┌─────────────────────────────────────────────┐
│ All components compiled with same GCC       │
│ - Python                                    │
│ - Boost                                     │
│ - libstdc++                                 │
│ - navigation_nanopy.so                      │
└─────────────────────────────────────────────┘
                    ↓
              WORKS FINE
```

---

## The Fix

### Before (Causes Segfault)
```yaml
gcc_version: "12",  # Forces GCC 12 on Ubuntu 22.04
```

### After (Will Fix)
```yaml
gcc_version: "",    # Use Ubuntu 22.04's default GCC 11
```

---

## Why This Happens

1. **C++ ABI Changes Between GCC 11 and 12**:
   - Different name mangling
   - Different std::string layout (small string optimization)
   - Different exception handling mechanisms
   - Different virtual table layouts

2. **Python Extension Modules**:
   - Link against Python's libpython (GCC 11)
   - Use Boost.Python/nanobind features (GCC 11)
   - Compiled with GCC 12
   - → **Binary incompatibility**

3. **Timing**:
   - Everything works during tests (basic functionality)
   - Crashes during cleanup (complex destructor chains)
   - → **Classic ABI mismatch symptom**

---

## How to Verify the Fix

After changing `gcc_version: "12"` to `gcc_version: ""`:

1. Trigger the workflow
2. ubuntu:22.04 job should now use GCC 11
3. All jobs should pass without segfault
4. Check compiler version in logs:
   ```
   gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
   ```

---

## Alternative Solutions (If GCC 12 is Required)

### Option 1: Upgrade to Ubuntu 24.04
```yaml
container: "ubuntu:24.04"  # Ships with GCC 13
gcc_version: ""
```

### Option 2: Build All Dependencies with GCC 12
```yaml
# Install newer Python from deadsnakes
pre-dep: |
  apt update
  add-apt-repository ppa:deadsnakes/ppa
  apt-get install -y python3.12 python3.12-dev
  
# Build Boost from source with GCC 12
dep: |
  export CC=gcc-12 CXX=g++-12
  # Build boost...
  # Build all other deps...
```

### Option 3: Use Pre-built Container
```yaml
# Create custom container with GCC 12 and all deps
container: "ghcr.io/yourusername/ubuntu-gcc12:latest"
gcc_version: ""  # Already in container
```

---

## Summary

**ROOT CAUSE**: Forcing GCC 12 on Ubuntu 22.04 creates binary incompatibility with system libraries compiled with GCC 11.

**SYMPTOM**: Segfault during Python interpreter shutdown after all tests pass.

**FIX**: Remove forced GCC 12, use system default GCC 11.

**FILE**: `.github/workflows/ci-linux.yml`  
**LINE**: 75  
**CHANGE**: `gcc_version: "12"` → `gcc_version: ""`
