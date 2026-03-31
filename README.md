# ARM64 Sample C++ Project

A cross-platform C++ project configured for ARM64 architecture, supporting macOS (Apple Silicon), Windows ARM64, and Linux ARM64.

## Project Structure

```
c-cpp-arm-project/
├── CMakeLists.txt           # CMake build configuration (cross-platform)
├── Makefile                 # Simple Makefile for Unix systems
├── ARM64Sample.sln          # Visual Studio solution file (Windows)
├── ARM64Sample/
│   ├── ARM64Sample.vcxproj  # Visual Studio project file
│   ├── main.cpp              # Main application entry point
│   ├── math_operations.h     # Header file for math functions
│   └── math_operations.cpp   # Implementation of math functions
├── README.md
└── BUILD.md                 # Detailed build instructions
```

## Features

- **Cross-Platform ARM64**: Builds on macOS (Apple Silicon), Windows ARM64, and Linux ARM64
- **Multiple Build Systems**: CMake, Visual Studio, Make
- **C++17 Standard**: Uses modern C++ features
- **Sample Code**: Demonstrates integer/floating-point arithmetic and architecture detection

## Quick Start

### macOS (Apple Silicon)

```bash
# Using CMake
mkdir build && cd build
cmake ..
cmake --build .
./bin/ARM64Sample

# Or using Make
make
./ARM64Sample.out
```

### Windows ARM64

```cmd
# Using Visual Studio
Open ARM64Sample.sln in Visual Studio 2022+

# Or using CMake
mkdir build && cd build
cmake -G "Visual Studio 17 2022" -A ARM64 ..
cmake --build . --config Release
.\bin\Release\ARM64Sample.exe
```

### Linux ARM64

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
./bin/ARM64Sample
```

## Requirements

### macOS
- Xcode Command Line Tools: `xcode-select --install`
- CMake (optional): `brew install cmake`
- Apple Silicon Mac (M1/M2/M3)

### Windows
- Visual Studio 2022+ with C++ development tools
- ARM64 build tools and libraries
- Windows 11 ARM64 or Windows 10 ARM64

### Linux
- GCC or Clang with C++17 support
- CMake: `sudo apt install cmake build-essential`
- ARM64/AArch64 system

## Build Systems

This project supports three build approaches:

1. **CMake** (Recommended) - Cross-platform, generates project files for any IDE
2. **Visual Studio** - Native Windows ARM64 development
3. **Make** - Simple Unix builds for macOS/Linux

See **[BUILD.md](BUILD.md)** for detailed instructions.

## Application Output

The program demonstrates:

1. Architecture detection and build configuration
2. Basic integer arithmetic operations (add, subtract, multiply, divide)
3. Floating-point arithmetic operations
4. Power function calculations

## Platform Verification

Confirm ARM64 build:

```bash
# macOS
file ./bin/ARM64Sample

# Linux
readelf -h ./bin/ARM64Sample | grep Machine

# Windows
dumpbin /HEADERS .\bin\Release\ARM64Sample.exe | findstr "machine"
```

## Notes

- Modern Macs (M1/M2/M3) are native ARM64 and will build automatically
- Windows requires explicit ARM64 platform selection
- Linux ARM64 builds on AArch64 systems (e.g., Raspberry Pi 4, AWS Graviton)
