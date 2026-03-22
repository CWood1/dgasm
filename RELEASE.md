# DGAsm Release Process
## Overview
This document defines the formal process for releasing dgasm, including:

* Release candidate workflow
* Testing requirements
* Quality gates
* Final release criteria

The goal is to ensure that every release is:

* Correct
* Stable
* Memory-safe
* Reproducible

## Branching & Versioning Model
### Branches
* main - Ongoing development for future versions
* release-vX.Y - Stabilisation branch for a release

### Tags
* vX.Y-rcN - Release candidate (pre-release)
* vX.Y - Final vX.Y release

## Release Workflow
### 1. Feature Freeze
Create a release branch when:

* All planned features are implemented
* No major functionality is missing

```bash
git checkout -b release-vX.Y main
```

### 2. Cut rc1
```bash
git tag vX.Y-rc1
git push origin vX.Y-rc1
```

This shall be marked as pre-release in GitHub.

### 3. Stabilisation Phase
All fixes go into `release-vX.Y` branch.

Permitted changes:

* Bug fixes
* Crash fixes
* Correctness fixes
* Test improvements
* Documentation

Not permitted:

* Feature work
* Large refactors (unless required to fix a release blocking bug)

### 4. Subsequent Release Candidates
When a release blocking bug is found, a new release candidate shall be cut upon resolution.

If multiple release blockers are discovered during a single testing phase, these shall be aggregated into a single release candidate, to prevent candidate proliferation.

### 5. Final Release
When all release criteria are met (see below):

* Cut the final release, using tag `vX.Y`.
* Merge all fixes from the `release-vX.Y` branch back to main.

## Testing Requirements
### Golden Tests
Purpose: Verify correct assembler output.

Golden tests must be exhaustive over assembler features, but need not be combinatorially exhaustive - eg, each opcode must have every parameter tested independently (range checks for constants, every addressing mode, every accumulator, etc), but need not have every combination of accumulator, addressing mode, and constant.

All golden tests must pass, with no diffs between golden output and test result.

### Fuzz Regression Tests
Purpose: Ensure previously crashing inputs remain fixed.

Every newly found crash must result in a new regression test.

All regression tests must exit cleanly, with no crashes and no hangs. The assembler may, however, exit with an error.

### Valgrind
Purpose: Detect memory leaks, invalid memory usage.

Valgrind must be run on a wide-scope of inputs, ensuring maximal coverage. The output must be clean.

### ASan, UBSan
Purpose: Detect undefined behaviour, memory errors.

The Sanitizers must be run against a wide-scope of inputs, ensuring maximal coverage. Additionally, they must be fuzzed. The output must be clean.

DGAsm shall be built with `-fsanitize=address,undefined`.

### Fuzzing Stability
Purpose: Discover unknown bugs.

AFL must be run on every release. No crashes, or hangs of concern, must be found. The minimum period is 24h.

Additionally, AFL must be run on a build with the Sanitizers enabled for a further 24h.

### Coverage
Purpose: Ensure minimal meaningful test coverage.

Golden and regression tests must cover all major code paths. As a proxy, gcov shall be used, with a target of 80% coverage.

## Release Blocking Bugs
* Crashes (segfaults, aborts)
* Memory corruption
* Undefined behaviour
* Incorrect output
* Hangs

## Release Readiness Criteria
* No known blocking bugs
* All tests pass
* Fuzzing finds no issues, after 24h minimum
* Sanitizers are clean
* Memory checks are clean
* Output is stable
* Documentation is up to date

## Fuzzing Workflow
After fuzzing:

* File any found bugs
* Fix all crashes
* Extract crash inputs into tests/fuzzregression
* Minimise corpus using `afl-cmin`
* Update seed corpus (fuzz/corpus/)

## CI Tests
Golden tests, regression tests, and a smoke fuzz is present in CI. Full fuzzing, including ASan and UBSan, and Valgrind testing, is to be done by hand locally.
