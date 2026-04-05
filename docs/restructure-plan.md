# Restructure Plan

## Summary

The current repository does not need a full rewrite. It needs a staged cleanup that separates concerns and makes the build, runtime, and documentation explicit.

The most important immediate problem was portability, not folder naming. That is why this pass fixed path resolution first and documented the real architecture before attempting larger moves.

## Recommended Stages

### Stage 1: Stabilize The Existing Layout

Status: partly done in this pass.

- keep `Scar_Source_Code` as the engine boundary
- keep `PFE_Source_Code` as the editor boundary
- document what each folder owns
- remove machine-specific runtime assumptions
- add ignore rules for local/tooling noise

### Stage 2: Introduce A Build Contract

Status: done in this pass.

- add a checked-in build system such as CMake
- define `Scar` as a library target
- define the editor as an executable target
- express third-party dependencies explicitly
- stop relying on out-of-repo IDE state

This step is now in place, which makes the remaining cleanup much less risky.

### Stage 3: Split The Editor Source

`PFE_Source_Code/src/pfe.cpp` should be broken into focused files. A practical split is:

- `EditorApp.cpp`: application lifecycle and window properties
- `EditorUI.cpp`: ImGui windows and menus
- `EditorCommands.cpp`: create/delete/save/load actions
- `EditorAssets.cpp`: icon and texture loading

This is the highest-value code-level refactor after the build system is in place.

### Stage 4: Clean The Repository Root

After the build system exists, move toward a clearer top-level layout such as:

```text
.
├── apps/
│   └── scar-editor/
├── engine/
├── external/
├── docs/
└── build/
```

That move is worth doing only once the build targets and include paths are explicit.

## Things I Would Not Do Yet

- I would not move source directories immediately while the worktree is already dirty.
- I would not rewrite the engine API before a build system exists.
- I would not delete the committed executable until you decide whether releases belong in this repo.

## Remaining Risks

The project still has a few issues outside the scope of this pass:

- no automated verification in the repo
- likely Windows-first assumptions in parts of the engine
- vendor code mixed into include space
- large, stateful editor source file that is hard to test

Those are real, but they are better handled incrementally than by a one-shot restructure.
