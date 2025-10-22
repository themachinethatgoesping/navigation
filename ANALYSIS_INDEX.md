# Segfault Analysis - Document Index

## 🎯 Quick Navigation

**Need to fix it NOW?** → [FIX_INSTRUCTIONS.md](FIX_INSTRUCTIONS.md)

**Want to understand the problem?** → [README_SEGFAULT_ANALYSIS.md](README_SEGFAULT_ANALYSIS.md)

**Need to explain to others?** → [PR_SUMMARY.md](PR_SUMMARY.md)

## 📚 All Documents

### 1. 🚀 [FIX_INSTRUCTIONS.md](FIX_INSTRUCTIONS.md) (4.6KB)
**Purpose:** Step-by-step guide to apply the fix

**Contains:**
- Exact file location and line number
- Before/after code comparison
- Three methods to apply the fix (CLI, web, sed)
- Verification steps
- Expected results

**When to use:** When you're ready to fix the issue

---

### 2. 📄 [README_SEGFAULT_ANALYSIS.md](README_SEGFAULT_ANALYSIS.md) (5.7KB)
**Purpose:** Executive summary and navigation guide

**Contains:**
- Problem in one sentence
- Fix in one line
- Quick links to all documents
- Visual flow diagrams
- FAQ section

**When to use:** First document to read for overview

---

### 3. 🎨 [VISUAL_COMPARISON.md](VISUAL_COMPARISON.md) (7.4KB)
**Purpose:** Visual understanding of the problem

**Contains:**
- Side-by-side workflow configurations
- Terminal output comparisons
- ASCII diagram of ABI mismatch
- Environment variable comparison
- Library version table

**When to use:** When you need to see the differences clearly

---

### 4. 🔍 [SEARCH_DIFFERENCES.md](SEARCH_DIFFERENCES.md) (4.1KB)
**Purpose:** Quick reference for debugging

**Contains:**
- Critical differences list
- What to search for online
- Debugging commands
- Symptom patterns
- Known issue references

**When to use:** When debugging or researching the issue

---

### 5. 📚 [SEGFAULT_ANALYSIS.md](SEGFAULT_ANALYSIS.md) (8.2KB)
**Purpose:** Complete technical deep dive

**Contains:**
- Detailed root cause analysis
- Full environment comparison tables
- Investigation methodology
- Immediate and long-term recommendations
- Technical details about ABI compatibility

**When to use:** When you need complete technical understanding

---

### 6. 📋 [PR_SUMMARY.md](PR_SUMMARY.md) (4.2KB)
**Purpose:** Concise summary for sharing

**Contains:**
- Issue summary
- Evidence table
- Solution recommendation
- Impact assessment
- Confidence level

**When to use:** When posting to PRs, issues, or sharing with team

---

## 🎯 The Problem (30 Second Version)

```
ubuntu:22.04 job forces GCC 12
    ↓
System libraries use GCC 11
    ↓
ABI incompatibility
    ↓
All tests pass ✅
    ↓
Segfault during cleanup ❌
```

## 🔧 The Fix (10 Second Version)

Change line 75 in `.github/workflows/ci-linux.yml`:
```yaml
gcc_version: "",  # was "12"
```

## 📊 Quick Stats

| Metric | Value |
|--------|-------|
| **Documents** | 6 |
| **Total Size** | 34KB |
| **Lines of Analysis** | ~950 |
| **Problem Confidence** | HIGH |
| **Solution Risk** | LOW |
| **Time to Fix** | 30 seconds |

## 🔗 Related Links

- **Failing Job**: https://github.com/themachinethatgoesping/navigation/actions/runs/18689880133/job/53292502472
- **Passing Job**: https://github.com/themachinethatgoesping/navigation/actions/runs/18689880133/job/53292502321
- **Workflow File**: `.github/workflows/ci-linux.yml`

## 📋 Checklist for Understanding

- [ ] Read README_SEGFAULT_ANALYSIS.md for overview
- [ ] Review VISUAL_COMPARISON.md to see the differences
- [ ] Understand why the fix works
- [ ] Apply the fix using FIX_INSTRUCTIONS.md
- [ ] Verify the fix in the next CI run
- [ ] Share PR_SUMMARY.md with team if needed

## 🎓 Key Learnings

1. **GCC versions must match** between system libraries and compiled code
2. **ABI compatibility matters** even when code compiles successfully
3. **Segfaults during cleanup** are a classic ABI mismatch symptom
4. **Pre-built containers** provide consistent environments
5. **System defaults exist for a reason** - Ubuntu 22.04 is designed for GCC 11

## 🚀 Next Steps

1. **Immediate**: Apply the one-line fix
2. **Short-term**: Verify all CI jobs pass
3. **Long-term**: Consider using pre-built containers for consistency

## 🤝 Contributing

If you find issues with this analysis or have improvements:

1. The documents are in the repository root
2. They're all markdown files
3. Feel free to update and commit improvements

## 📝 Document Map

```
ANALYSIS_INDEX.md (you are here)
├── FIX_INSTRUCTIONS.md ................. How to fix (step-by-step)
├── README_SEGFAULT_ANALYSIS.md ......... Executive summary
├── VISUAL_COMPARISON.md ................ Side-by-side comparisons
├── SEARCH_DIFFERENCES.md ............... Quick reference
├── SEGFAULT_ANALYSIS.md ................ Technical deep dive
└── PR_SUMMARY.md ....................... Concise summary
```

## 🎯 Success Criteria

After applying the fix, you should see:

- ✅ All 29 tests pass
- ✅ No "Segmentation fault" message
- ✅ Exit code 0 (success)
- ✅ "Post job cleanup" in logs
- ✅ Green checkmark on ubuntu:22.04 job

## 💡 Pro Tips

1. **Bookmark this index** - it's your navigation hub
2. **Share PR_SUMMARY.md** - it's perfect for issue comments
3. **Use FIX_INSTRUCTIONS.md** - it has copy-paste commands
4. **Reference VISUAL_COMPARISON.md** - for explaining to others
5. **Keep SEGFAULT_ANALYSIS.md** - for future debugging

---

**Analysis Date**: 2025-10-22  
**Workflow Run**: #18689880133  
**Confidence**: HIGH  
**Documents**: 6 (34KB)

**Ready to fix?** Go to [FIX_INSTRUCTIONS.md](FIX_INSTRUCTIONS.md) 🚀
