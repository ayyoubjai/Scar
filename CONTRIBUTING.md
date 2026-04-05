# Contributing To Scar

## Goal

This repository now has a checked-in build contract so new contributors do not need to reverse-engineer the project layout before making changes.

Scar currently consists of:

- `Scar_Source_Code/`: engine library
- `PFE_Source_Code/`: editor executable
- `docs/`: architecture and restructuring notes

## Prerequisites

- CMake 3.21+
- A C++17 compiler
- OpenGL-capable development environment
- `vcpkg` with `VCPKG_ROOT` set

The repo includes a `vcpkg.json` manifest for external dependencies:

- `sdl2`
- `glad`
- `glm`
- `spdlog`

ImGui and `stb_image` are vendored in the repository and are built from source as part of the engine target.

## Configure And Build

Example configure command:

```bash
cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
```

Example build command:

```bash
cmake --build build --config Debug
```

The editor executable is `scar_editor`. Runtime assets and shaders are resolved relative to the repository root, so running from any build directory inside the repo should work.

## Working Agreement

- Prefer small, focused changes.
- Do not reintroduce absolute local paths such as `C:/dev/...`.
- Keep engine changes in `Scar_Source_Code` and editor-specific changes in `PFE_Source_Code`.
- Avoid committing generated build output.
- Update `README.md` or `docs/` when behavior or setup changes.

## Near-Term Refactor Targets

The highest-value next cleanup is splitting `PFE_Source_Code/src/pfe.cpp` into smaller editor modules:

- application bootstrap and window setup
- ImGui layout
- save/load commands
- asset registration

That work is independent from the build setup added in this pass and can now happen incrementally.
