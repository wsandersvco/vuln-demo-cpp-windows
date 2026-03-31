# Building ARM64Sample

This project supports multiple build systems and platforms.

## Platform Support

- **macOS ARM64** (Apple Silicon M1/M2/M3)
- **Windows ARM64** (Windows 10/11 ARM64)
- **Linux ARM64** (AArch64)

---

## Building on macOS (Apple Silicon)

### Prerequisites
- Xcode Command Line Tools: `xcode-select --install`
- CMake: `brew install cmake`

### Build Instructions

#### Option 1: Using CMake (Recommended)

```bash
# Create build directory
mkdir build
cd build

# Configure (ARM64 is automatic on Apple Silicon)
cmake ..

# Build
cmake --build .

# Run
./bin/ARM64Sample
```

#### Option 2: Using CMake with Xcode

```bash
# Generate Xcode project
mkdir build-xcode
cd build-xcode
cmake -G Xcode ..

# Open in Xcode
open ARM64Sample.xcodeproj

# Or build from command line
cmake --build . --config Release
./bin/Release/ARM64Sample
```

#### Option 3: Using Make directly

```bash
# Build with the Makefile
make

# Run
./ARM64Sample
```

### Build Types

```bash
# Debug build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .

# Release build (optimized)
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

---

## Building on Windows ARM64

### Prerequisites
- Visual Studio 2022 (or later) with:
  - Desktop development with C++
  - ARM64 build tools
- CMake (included with Visual Studio or install separately)

### Build Instructions

#### Option 1: Using Visual Studio Solution (Native)

```cmd
# Open the solution file directly in Visual Studio
ARM64Sample.sln

# Select ARM64 platform and build
# Build → Build Solution (Ctrl+Shift+B)
```

#### Option 2: Using CMake with Visual Studio

```cmd
# Create build directory
mkdir build
cd build

# Configure for ARM64
cmake -G "Visual Studio 17 2022" -A ARM64 ..

# Build
cmake --build . --config Release

# Run
.\bin\Release\ARM64Sample.exe
```

#### Option 3: Using CMake from Visual Studio Developer Command Prompt

```cmd
# Open "ARM64 Native Tools Command Prompt for VS 2022"
mkdir build
cd build

# Configure
cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release ..

# Build
nmake

# Run
.\bin\ARM64Sample.exe
```

---

## Building on Linux ARM64

### Prerequisites

```bash
# Ubuntu/Debian
sudo apt update
sudo apt install build-essential cmake

# Fedora/RHEL
sudo dnf install gcc-c++ cmake
```

### Build Instructions

```bash
# Create build directory
mkdir build
cd build

# Configure
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build
cmake --build . -j$(nproc)

# Run
./bin/ARM64Sample
```

---

## CMake Build Options

### Specifying Build Type

```bash
# Debug (with debug symbols)
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release (optimized)
cmake -DCMAKE_BUILD_TYPE=Release ..

# RelWithDebInfo (optimized with debug info)
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
```

### Verbose Build Output

```bash
cmake --build . --verbose
# or
make VERBOSE=1
```

### Clean Build

```bash
# From build directory
cmake --build . --target clean

# Or remove and recreate build directory
cd ..
rm -rf build
mkdir build
cd build
cmake ..
```

### Installation

```bash
# Install to default location (/usr/local on Unix, C:/Program Files on Windows)
sudo cmake --install .

# Install to custom location
cmake --install . --prefix /custom/path
```

---

## Verifying ARM64 Build

### macOS
```bash
file ./bin/ARM64Sample
# Should show: Mach-O 64-bit executable arm64

lipo -info ./bin/ARM64Sample
# Should show: Non-fat file: ./bin/ARM64Sample is architecture: arm64
```

### Linux
```bash
file ./bin/ARM64Sample
# Should show: ELF 64-bit LSB executable, ARM aarch64

readelf -h ./bin/ARM64Sample | grep Machine
# Should show: Machine: AArch64
```

### Windows
```cmd
dumpbin /HEADERS .\bin\Release\ARM64Sample.exe | findstr "machine"
# Should show: AA64 machine (ARM64)
```

---

## Troubleshooting

### macOS: "Bad CPU type in executable"
- You're trying to run ARM64 binary on Intel Mac or vice versa
- Use the correct architecture for your Mac

### Windows: "ARM64 platform not found"
- Install ARM64 build tools in Visual Studio Installer
- Ensure you're using Visual Studio 2022 or later

### Linux: Compiler not found
- Install build-essential or development tools
- Ensure you're on an ARM64 system: `uname -m` should show `aarch64`

### CMake: "No CMAKE_CXX_COMPILER could be found"
- Install appropriate compiler toolchain
- macOS: `xcode-select --install`
- Linux: `sudo apt install build-essential`
- Windows: Install Visual Studio with C++ tools
