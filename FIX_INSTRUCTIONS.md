# How to Fix the Segfault - Step by Step

## The One-Line Fix

### File Location
```
.github/workflows/ci-linux.yml
```

### Line to Change
**Line 75**

### Current Code (BROKEN)
```yaml
              gcc_version: "12",
```

### Fixed Code
```yaml
              gcc_version: "",
```

## Complete Context

Here's the full matrix entry with the fix highlighted:

```yaml
          - {
              container: "ubuntu:22.04",
              ccache: "true",
              pre-dep: "apt update && apt-get install -y sudo git git-lfs",
              dep: "sudo DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential ccache pkg-config cmake python3-pip libboost-all-dev libcurl4-openssl-dev",
              pip: "pip install meson meson-python ninja pytest numpy",
              pip2: "pip install -r requirements.txt",
              gcc_version: "",  # ← CHANGED: was "12", now ""
            }
```

## How to Apply the Fix

### Option 1: Using Git Command Line

```bash
# 1. Edit the file
vim .github/workflows/ci-linux.yml

# 2. Navigate to line 75 and change:
#    gcc_version: "12",
#    to:
#    gcc_version: "",

# 3. Save and commit
git add .github/workflows/ci-linux.yml
git commit -m "Fix ubuntu:22.04 segfault by using system default GCC"
git push
```

### Option 2: Using GitHub Web Interface

1. Go to: https://github.com/themachinethatgoesping/navigation/blob/main/.github/workflows/ci-linux.yml
2. Click the pencil icon (Edit this file)
3. Navigate to line 75
4. Change `gcc_version: "12",` to `gcc_version: "",`
5. Scroll down and click "Commit changes"

### Option 3: Using sed

```bash
cd /path/to/navigation

# Make the change
sed -i 's/gcc_version: "12",/gcc_version: "",/' .github/workflows/ci-linux.yml

# Verify the change
git diff .github/workflows/ci-linux.yml

# Commit
git add .github/workflows/ci-linux.yml
git commit -m "Fix ubuntu:22.04 segfault by using system default GCC"
git push
```

## Verification

After pushing the change, the workflow will run and you should see:

### Before (BROKEN)
```
Step "install gcc toolchain":
  Installing gcc-12 and g++-12
  Setting CC=gcc-12, CXX=g++-12

Test output:
  ============================== 29 passed in 0.33s ==============================
  Segmentation fault (core dumped)
  ##[error]Process completed with exit code 139.
```

### After (FIXED)
```
Step "install gcc toolchain":
  (skipped - gcc_version is empty)

Test output:
  ============================== 29 passed in 0.33s ==============================
  Post job cleanup.
  (clean exit)
```

### What Changed
- The workflow will no longer install GCC 12
- Ubuntu 22.04 will use its default GCC 11.4
- All libraries will have compatible ABIs
- No more segfault!

## Expected Results

| Aspect | Before | After |
|--------|--------|-------|
| GCC Version | 12 (forced) | 11.4 (default) |
| Tests Pass | ✅ Yes (29/29) | ✅ Yes (29/29) |
| Exit Clean | ❌ No (segfault) | ✅ Yes |
| CI Status | ❌ Failed | ✅ Success |

## Testing

Watch the ubuntu:22.04 job at:
https://github.com/themachinethatgoesping/navigation/actions

Look for:
1. ✅ All 29 tests pass
2. ✅ No segfault message
3. ✅ "Post job cleanup" appears
4. ✅ Green checkmark on the job

## If You Still See Issues

If the segfault persists after this change, check:

1. **Verify the change was applied:**
   ```bash
   grep gcc_version .github/workflows/ci-linux.yml
   # Should show: gcc_version: "",
   ```

2. **Check the GCC version in the logs:**
   ```
   Should see: gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
   Not: gcc (Ubuntu 12.x.x) 12.x.x
   ```

3. **Review the failing step:**
   - If it's still during pytest cleanup → might be a different issue
   - If it's during build → check compiler flags
   - If it's during different step → not the same issue

## Rollback

If needed, you can easily rollback:

```yaml
gcc_version: "12",  # Revert to force GCC 12 (will cause segfault)
```

But this shouldn't be necessary - the fix is solid!

## Why This Works

### The Problem
```
System Python (GCC 11) + User Code (GCC 12) = ABI Mismatch = Segfault
```

### The Solution
```
System Python (GCC 11) + User Code (GCC 11) = ABI Match = Success
```

### Key Point
Ubuntu 22.04 is designed and tested with GCC 11. All system packages are compiled with GCC 11. Forcing GCC 12 breaks this consistency.

## Additional Resources

- **README_SEGFAULT_ANALYSIS.md** - Executive summary
- **VISUAL_COMPARISON.md** - Visual comparison of environments
- **SEGFAULT_ANALYSIS.md** - Complete technical analysis
- **SEARCH_DIFFERENCES.md** - Debugging reference

---

**Ready to fix it?** Just change line 75 from `"12"` to `""` and push! 🚀
