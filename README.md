# Windows ARM64 C++ Security Demo Project
**Version:** 2.0.0

This project demonstrates various security vulnerabilities for testing static analysis tools on **Windows ARM64 architecture** using native Windows SSPI authentication.

## Overview

This is an **ARM64-native** Windows C++ application that demonstrates intentional security vulnerabilities including authentication weaknesses using **Windows SSPI (Security Support Provider Interface)** with Kerberos support. Perfect for testing security scanning tools on the ARM64 platform.

## Requirements

### Windows ARM64 Build (Native)
- **Windows 11 ARM64** (or Windows 10 ARM64)
- **Visual Studio 2022 (v17.0 or later)** with:
  - Desktop development with C++ workload
  - **ARM64 build tools** (required)
  - Windows 11 SDK (10.0.22000.0 or later)
  - C++ ARM64 Spectre-mitigated libraries (optional)
- **MSBuild** (included with Visual Studio)

### Authentication Dependencies
- **Windows SSPI (Secur32.lib)** - Native Windows authentication API
  - Built-in Windows library, no external dependencies required
  - Full ARM64 support (native)
  - Supports Kerberos, NTLM, Negotiate, and other security packages
  - No need for MIT Kerberos for Windows

## Building

### Visual Studio IDE
1. Open `arm64_sample.sln` in Visual Studio 2022
2. Select **ARM64** platform from the dropdown
3. Choose **Debug** or **Release** configuration
4. Press **F7** or select **Build > Build Solution**

### Command Line (Build Scripts)
For convenience, use the provided build scripts:

**PowerShell:**
```powershell
# Build Release configuration
.\build.ps1

# Build Debug configuration
.\build.ps1 -Configuration Debug

# Clean build artifacts
.\build.ps1 -Clean

# Clean and rebuild
.\build.ps1 -Rebuild

# Show help
.\build.ps1 -Help
```

**Batch/CMD:**
```cmd
# Build Release configuration
build.cmd Release

# Build Debug configuration
build.cmd Debug

# Clean build artifacts
build.cmd Release Clean

# Rebuild
build.cmd Release Rebuild
```

### Command Line (MSBuild)
Or use MSBuild directly from **Developer Command Prompt for VS 2022**:

```powershell
# Build Debug configuration for ARM64
msbuild arm64_sample.sln /p:Configuration=Debug /p:Platform=ARM64 /m

# Build Release configuration for ARM64
msbuild arm64_sample.sln /p:Configuration=Release /p:Platform=ARM64 /m

# Clean and rebuild
msbuild arm64_sample.sln /t:Clean,Build /p:Configuration=Release /p:Platform=ARM64 /m
```

## Running

After building, run the executable from the build directory:

```powershell
# Debug build
.\build\ARM64\Debug\arm64_sample.exe

# Release build
.\build\ARM64\Release\arm64_sample.exe
```

## Project Structure

```
vuln-demo-cpp-windows/
├── arm64_sample.sln          # Visual Studio solution
├── arm64_sample.vcxproj      # Visual Studio project (ARM64)
├── build.ps1                 # PowerShell build script
├── build.cmd                 # Batch build script
├── Makefile                  # Cross-platform Makefile
├── main.cpp                  # Main entry point
├── verademo_vulns.cpp        # Vulnerability implementations
├── verademo_vulns.h          # Vulnerability declarations
├── utils.cpp                 # Utility functions
├── utils.h                   # Utility headers
├── veracode.yml              # Veracode configuration
└── build/                    # Build output directory
    └── ARM64/
        ├── Debug/
        └── Release/
```

## Vulnerabilities Demonstrated

This project contains intentional security vulnerabilities for testing purposes, including:

### Authentication & Credentials
- CWE-259: Hard-coded Passwords (Windows SSPI/Kerberos)
- CWE-798: Hard-coded Credentials
- CWE-522: Insufficiently Protected Credentials (SSPI)

### Injection Vulnerabilities
- CWE-89: SQL Injection
- CWE-78: OS Command Injection
- CWE-611: XML External Entity (XXE)

### Memory Safety
- CWE-120/121/122: Buffer Overflows (Stack and Heap)
- CWE-416: Use After Free
- CWE-415: Double Free
- CWE-401: Memory Leak
- CWE-476: NULL Pointer Dereference

### Cryptography
- CWE-327: Weak Cryptography (MD5)
- CWE-330: Weak Random Number Generation

### And many more including:
- CWE-73: Path Traversal
- CWE-190/191: Integer Overflow/Underflow
- CWE-134: Format String Vulnerabilities
- CWE-362/367: Race Conditions
- CWE-457: Uninitialized Variables
- CWE-561: Dead Code
- CWE-606: Logic Errors

**⚠️ WARNING: This code is intentionally vulnerable. Do not use in production!**

## Windows SSPI Features

This project demonstrates Windows Security Support Provider Interface (SSPI) usage with intentional vulnerabilities:
- Native Kerberos authentication via SSPI
- Credential handle management
- Security context initialization
- Security package enumeration
- Token generation and validation
- **All running natively on ARM64 Windows**

## Cleaning Build Artifacts

```powershell
# Using MSBuild
msbuild arm64_sample.sln /t:Clean /p:Configuration=Debug /p:Platform=ARM64
msbuild arm64_sample.sln /t:Clean /p:Configuration=Release /p:Platform=ARM64

# Manual cleanup
Remove-Item -Recurse -Force build\
```

## Notes for Windows ARM64

- This project is **ARM64-native only** - specifically designed for Windows on ARM64 devices
- Optimized for ARM64 hardware (e.g., Surface Pro X, Windows Dev Kit 2023, Snapdragon X Elite devices)
- Uses **native Windows SSPI** authentication APIs with full ARM64 support
- No external dependencies required - all authentication via built-in Windows libraries
- To build for x64/x86, you would need to create a separate project configuration
