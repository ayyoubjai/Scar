# Architecture

## High-Level Split

Scar is organized as an engine plus one editor application:

- `Scar_Source_Code` contains the engine runtime, rendering abstractions, events, windowing, and managers.
- `PFE_Source_Code` contains the editor UI, editor assets, design serialization, and the `CreateApplication()` entry implementation.

At runtime the flow is:

1. `PFE_Source_Code/src/pfe.cpp` defines the concrete `Application`.
2. `PFE_Source_Code/src/main.cpp` creates the app and boots the engine.
3. `Scar_Source_Code/src/core/Engine.cpp` initializes SDL, logging, rendering, input, and the window.
4. `Scar_Source_Code/src/window/Window.cpp` owns the SDL window, framebuffer, ImGui integration, and screen presentation.
5. `PFE_Source_Code/src/pfe.cpp` drives editor UI and entity creation through `EntityManager`.

## Engine Areas

The engine code is grouped by concern:

- `core/`: engine lifecycle, entry point, platform macros, logging helpers, path resolution
- `window/`: SDL window creation, OpenGL context, framebuffer presentation, resize handling
- `graphics/`: shaders, textures, vertex arrays, framebuffer objects, render commands, entities
- `events/`: keyboard and mouse state tracking
- `managers/`: render queue, entity store, logging backend
- `imguiWindow/`: Dear ImGui setup and SDL/OpenGL binding glue

This grouping is reasonable. The engine is now formalized as a library target, so the next structural pain points are the oversized editor source file and the mixed vendor/public include layout.

## Editor Areas

`PFE_Source_Code` currently mixes several responsibilities:

- `src/pfe.cpp`: editor startup, UI layout, entity creation, save/load logic, and application configuration
- `assets/`: toolbar icons and background assets
- `designs/`: serialized `.scar` files
- `src/shaders/`: editor-side shaders for primitives and icons

The directory shape is acceptable for a small app, but the source layout is not yet modular. `pfe.cpp` is acting as:

- application bootstrap
- UI controller
- command handler
- serialization layer
- asset registry

That file is the best candidate for the next code split.

## Structural Findings

The main structural weaknesses are:

- Runtime resources are repo-relative now, but they still assume execution from somewhere inside the repository tree.
- Binary output is committed next to source, which blurs source-of-truth boundaries.
- Vendor code is mixed into public include paths.
- The editor implementation is still concentrated in one large source file.

## What Changed In This Pass

This pass intentionally avoided risky file moves in a dirty worktree. The concrete changes were:

- introduced repo-relative path helpers in `Scar_Source_Code/include/Scar/core/Paths.h`
- switched editor assets, engine shaders, editor shaders, and design files to use those helpers
- fixed `Window::GetWindowSize()` to return by value instead of a dangling reference
- fixed the `imguiWindow` header include casing
- moved the executable entry point into `PFE_Source_Code/src/main.cpp`
- added checked-in `CMake` targets for the engine and editor
- added a `vcpkg` dependency manifest and contributor setup docs

That gives you a better base for future restructuring without breaking the current folder layout.
