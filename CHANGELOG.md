# Changelog

All notable changes to the Windows ARM64 Security Demo project.

## [2.0.0] - 2026-04-16

### 🎯 Major Rewrite: ARM64-Native Windows with SSPI Authentication

This is a major rewrite focused on Windows ARM64 native execution with Windows SSPI authentication APIs.

### Added
- **Windows SSPI (Security Support Provider Interface)** authentication implementation
  - Native Kerberos support via SSPI
  - `AcquireCredentialsHandleA()` for credential management
  - `InitializeSecurityContextA()` for security context creation
  - `QuerySecurityPackageInfoA()` for package enumeration
  - `EnumerateSecurityPackagesA()` for listing available packages
- **Secur32.lib** linking in project configuration
- **SECURITY_WIN32** preprocessor definition for SSPI
- Native Windows authentication headers (`security.h`, `sspi.h`, `ntsecapi.h`)
- ARM64_MIGRATION.md - comprehensive migration guide
- CHANGELOG.md - version history tracking

### Changed
- **Migrated from MIT Kerberos to Windows SSPI** for authentication
  - Replaced `krb5_*` functions with Windows SSPI equivalents
  - Replaced `gss_*` functions with SSPI context management
  - Updated all Kerberos vulnerability demonstrations to use SSPI
- **Converted to ARM64-only build**
  - Removed x64 and x86 platform configurations
  - Optimized for ARM64 native execution
  - Updated all build scripts to target ARM64 platform
- **Updated README.md** with Windows SSPI information
  - Added SSPI features section
  - Updated requirements to reflect ARM64-only focus
  - Clarified no external dependencies needed
  - Enhanced vulnerability categorization
- **Updated project files**
  - arm64_sample.vcxproj: Added Secur32.lib dependency
  - Both Debug and Release configurations updated
  - Added SECURITY_WIN32 to preprocessor definitions
- **Updated source code**
  - main.cpp: Updated headers and startup messages
  - verademo_vulns.cpp: Complete SSPI implementation
  - verademo_vulns.h: Updated function declarations

### Removed
- MIT Kerberos for Windows dependency
- Cross-platform build configurations (x64, x86)
- External authentication library requirements
- GSS-API references and implementations

### Vulnerabilities Preserved
All vulnerability demonstrations retained with Windows SSPI implementation:
- CWE-259: Hard-coded Kerberos Password
- CWE-798: Hard-coded Credentials  
- CWE-522: Insufficiently Protected Credentials
- Plus 40+ other vulnerability types (SQL Injection, Buffer Overflows, etc.)

### Technical Details

#### Authentication Implementation
```cpp
// New SSPI Authentication Flow
CredHandle credHandle;
SEC_WINNT_AUTH_IDENTITY authIdentity;
TimeStamp lifetime;

AcquireCredentialsHandleA(
    username, "Kerberos",
    SECPKG_CRED_OUTBOUND,
    nullptr, &authIdentity,
    nullptr, nullptr,
    &credHandle, &lifetime
);

InitializeSecurityContextA(
    &credHandle, nullptr, target,
    ISC_REQ_MUTUAL_AUTH | ISC_REQ_DELEGATE,
    0, SECURITY_NATIVE_DREP,
    nullptr, 0,
    &contextHandle, &outBufferDesc,
    &contextAttr, &contextLifetime
);
```

#### Build Configuration
```xml
<PreprocessorDefinitions>
  SECURITY_WIN32;_CONSOLE;_CRT_SECURE_NO_WARNINGS
</PreprocessorDefinitions>
<AdditionalDependencies>
  Secur32.lib;%(AdditionalDependencies)
</AdditionalDependencies>
```

### Platform Support
- **Supported**: Windows 11 ARM64, Windows 10 ARM64
- **Architecture**: ARM64 native only
- **Minimum SDK**: Windows 11 SDK (10.0.22000.0)

### Benefits
1. **Native ARM64 Performance** - No emulation overhead
2. **Zero External Dependencies** - Uses built-in Windows libraries
3. **Simplified Deployment** - Single executable, no additional DLLs
4. **Better Integration** - Native Windows security integration
5. **Enhanced Compatibility** - Supports all Windows security packages

### Migration Notes
See ARM64_MIGRATION.md for detailed migration information including:
- API mapping guide (Kerberos → SSPI)
- Code examples and comparisons
- Build instructions
- Performance considerations

### Breaking Changes
⚠️ **This is a breaking change from v1.x:**
- No longer supports x64/x86 platforms (ARM64 only)
- Requires Windows ARM64 operating system
- Requires Visual Studio 2022 with ARM64 tools
- MIT Kerberos for Windows no longer used

### Version Numbering
- v2.0.0: Major version bump due to breaking changes
- Focus on single platform (ARM64) with native authentication

---

## [1.0.3] - Previous Version

### Features
- Cross-platform Windows support (x64, x86, ARM64)
- MIT Kerberos for Windows integration
- Security vulnerability demonstrations
- Multi-platform build configurations

### Dependencies
- MIT Kerberos for Windows
- GSS-API libraries
- Complex external dependency management

---

## Upgrade Guide

### From v1.x to v2.0.0

**Prerequisites:**
1. Windows 11 ARM64 or Windows 10 ARM64
2. Visual Studio 2022 with ARM64 build tools
3. Windows 11 SDK

**Steps:**
1. Remove MIT Kerberos for Windows installation (no longer needed)
2. Open arm64_sample.sln in Visual Studio 2022
3. Select ARM64 platform
4. Build solution - Secur32.lib will link automatically

**No code changes required** if you're just building and running the demo.

---

## Support

For questions or issues:
- Review ARM64_MIGRATION.md for technical details
- Check README.md for build instructions
- Refer to Windows SSPI documentation for API details
