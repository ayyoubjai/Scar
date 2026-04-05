# Scar

Scar is a native 2D floor-plan editor built on top of a small rendering engine. The repository is now organized as two explicit build targets instead of an implicit source dump:

- `Scar_Source_Code/`: engine library
- `PFE_Source_Code/`: editor application

## Quick Start

Scar now includes a checked-in `CMake` build and a `vcpkg` dependency manifest.

Prerequisites:

- CMake 3.21+
- a C++17 compiler
- `vcpkg` with `VCPKG_ROOT` set

Configure:

```bash
cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
```

Build:

```bash
cmake --build build --config Debug
```

The main executable target is `scar_editor`.

## Repository Layout

```text
.
├── CMakeLists.txt
├── vcpkg.json
├── Scar_Source_Code/     # engine library target
├── PFE_Source_Code/      # editor executable target
├── docs/                 # architecture and restructuring notes
└── PFE_Executabele_64/   # legacy committed Windows binary output
```

## Dependencies

External dependencies are declared in `vcpkg.json`:

- SDL2
- glad
- GLM
- spdlog

Vendored dependencies already in the repository:

- Dear ImGui
- stb_image

## Developer Docs

- [Architecture](./docs/architecture.md)
- [Restructure Plan](./docs/restructure-plan.md)
- [Contributing](./CONTRIBUTING.md)

## What Improved

This repository is now easier for other developers to work with because it has:

- an explicit executable entry point in `PFE_Source_Code/src/main.cpp`
- checked-in `CMake` targets for the engine and editor
- a `vcpkg` manifest for the external dependency set
- onboarding and contribution documentation
- repo-relative runtime asset and shader resolution

## Remaining Gaps

The biggest remaining cleanup is still `PFE_Source_Code/src/pfe.cpp`, which mixes editor UI, commands, serialization, and asset setup in one file. The build and docs are in place now, so that split can happen cleanly in a follow-up pass.
