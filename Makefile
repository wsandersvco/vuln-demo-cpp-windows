# Windows ARM64 C++ Project Makefile
# ====================================
# This Makefile is designed specifically for Windows ARM64 builds.
# For native Windows ARM64 builds, use Visual Studio 2022 or MSBuild.
# This Makefile provides convenient make targets that wrap MSBuild commands.

# Solution and project settings
SOLUTION = arm64_sample.sln
PROJECT = arm64_sample.vcxproj
PLATFORM = ARM64
DEFAULT_CONFIG = Release

# Build directories
BUILD_DIR = build
BUILD_OUTPUT_DIR = $(BUILD_DIR)\$(PLATFORM)
VERAOUT_DIR = veraout

# MSBuild settings
MSBUILD = msbuild
MSBUILD_FLAGS = /m /v:minimal /nologo

# Default target
.PHONY: all
all: release

# Help target - display available commands
.PHONY: help
help:
	@echo ========================================
	@echo Windows ARM64 C++ Project Makefile
	@echo ========================================
	@echo.
	@echo This Makefile is designed for Windows ARM64 only.
	@echo It requires Visual Studio 2022 with ARM64 build tools.
	@echo.
	@echo Available targets:
	@echo   all              - Build Release configuration (default)
	@echo   release          - Build Release configuration for ARM64
	@echo   debug            - Build Debug configuration for ARM64
	@echo   rebuild          - Clean and rebuild Release configuration
	@echo   rebuild-debug    - Clean and rebuild Debug configuration
	@echo   clean            - Clean all build artifacts
	@echo   clean-debug      - Clean Debug build artifacts only
	@echo   clean-release    - Clean Release build artifacts only
	@echo   veracode-package - Create Veracode package for scanning
	@echo   run              - Build and run Release configuration
	@echo   run-debug        - Build and run Debug configuration
	@echo   help             - Show this help message
	@echo.
	@echo Build methods:
	@echo   1. Using this Makefile:     make release
	@echo   2. Using build scripts:     build.ps1 or build.cmd
	@echo   3. Using Visual Studio:     Open arm64_sample.sln
	@echo   4. Using MSBuild directly:  msbuild arm64_sample.sln /p:Platform=ARM64
	@echo.
	@echo Requirements:
	@echo   - Windows 11 ARM64 (or Windows 10 ARM64)
	@echo   - Visual Studio 2022 with C++ ARM64 tools
	@echo   - MSBuild (included with Visual Studio)
	@echo.

# Build Release configuration
.PHONY: release
release:
	@echo ========================================
	@echo Building Windows ARM64 - Release
	@echo ========================================
	@$(MSBUILD) "$(SOLUTION)" /t:Build /p:Configuration=Release /p:Platform=$(PLATFORM) $(MSBUILD_FLAGS)
	@echo.
	@echo Build complete: $(BUILD_OUTPUT_DIR)\Release\arm64_sample.exe

# Build Debug configuration
.PHONY: debug
debug:
	@echo ========================================
	@echo Building Windows ARM64 - Debug
	@echo ========================================
	@$(MSBUILD) "$(SOLUTION)" /t:Build /p:Configuration=Debug /p:Platform=$(PLATFORM) $(MSBUILD_FLAGS)
	@echo.
	@echo Build complete: $(BUILD_OUTPUT_DIR)\Debug\arm64_sample.exe

# Rebuild Release configuration
.PHONY: rebuild
rebuild:
	@echo ========================================
	@echo Rebuilding Windows ARM64 - Release
	@echo ========================================
	@$(MSBUILD) "$(SOLUTION)" /t:Rebuild /p:Configuration=Release /p:Platform=$(PLATFORM) $(MSBUILD_FLAGS)
	@echo.
	@echo Rebuild complete: $(BUILD_OUTPUT_DIR)\Release\arm64_sample.exe

# Rebuild Debug configuration
.PHONY: rebuild-debug
rebuild-debug:
	@echo ========================================
	@echo Rebuilding Windows ARM64 - Debug
	@echo ========================================
	@$(MSBUILD) "$(SOLUTION)" /t:Rebuild /p:Configuration=Debug /p:Platform=$(PLATFORM) $(MSBUILD_FLAGS)
	@echo.
	@echo Rebuild complete: $(BUILD_OUTPUT_DIR)\Debug\arm64_sample.exe

# Clean all build artifacts
.PHONY: clean
clean:
	@echo ========================================
	@echo Cleaning Windows ARM64 build artifacts
	@echo ========================================
	@$(MSBUILD) "$(SOLUTION)" /t:Clean /p:Configuration=Debug /p:Platform=$(PLATFORM) $(MSBUILD_FLAGS)
	@$(MSBUILD) "$(SOLUTION)" /t:Clean /p:Configuration=Release /p:Platform=$(PLATFORM) $(MSBUILD_FLAGS)
	@if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)" 2>nul
	@if exist "$(VERAOUT_DIR)" rmdir /s /q "$(VERAOUT_DIR)" 2>nul
	@if exist "arm64_sample.zip" del /q "arm64_sample.zip" 2>nul
	@echo.
	@echo Clean complete

# Clean Debug artifacts only
.PHONY: clean-debug
clean-debug:
	@echo Cleaning Debug artifacts...
	@$(MSBUILD) "$(SOLUTION)" /t:Clean /p:Configuration=Debug /p:Platform=$(PLATFORM) $(MSBUILD_FLAGS)
	@if exist "$(BUILD_OUTPUT_DIR)\Debug" rmdir /s /q "$(BUILD_OUTPUT_DIR)\Debug" 2>nul

# Clean Release artifacts only
.PHONY: clean-release
clean-release:
	@echo Cleaning Release artifacts...
	@$(MSBUILD) "$(SOLUTION)" /t:Clean /p:Configuration=Release /p:Platform=$(PLATFORM) $(MSBUILD_FLAGS)
	@if exist "$(BUILD_OUTPUT_DIR)\Release" rmdir /s /q "$(BUILD_OUTPUT_DIR)\Release" 2>nul

# Build and run Release configuration
.PHONY: run
run: release
	@echo.
	@echo ========================================
	@echo Running Release build
	@echo ========================================
	@"$(BUILD_OUTPUT_DIR)\Release\arm64_sample.exe"

# Build and run Debug configuration
.PHONY: run-debug
run-debug: debug
	@echo.
	@echo ========================================
	@echo Running Debug build
	@echo ========================================
	@"$(BUILD_OUTPUT_DIR)\Debug\arm64_sample.exe"

# Create Veracode package
.PHONY: veracode-package
veracode-package:
	@echo ========================================
	@echo Creating Veracode package
	@echo ========================================
	@if not exist "$(VERAOUT_DIR)" mkdir "$(VERAOUT_DIR)"
	@veracode package -s . -a -t directory -o "$(VERAOUT_DIR)"
	@echo.
	@echo Veracode package created in $(VERAOUT_DIR)

# Check if solution file exists
.PHONY: check
check:
	@if not exist "$(SOLUTION)" (echo ERROR: Solution file not found: $(SOLUTION) && exit /b 1)
	@if not exist "$(PROJECT)" (echo ERROR: Project file not found: $(PROJECT) && exit /b 1)
	@where $(MSBUILD) >nul 2>&1 || (echo ERROR: MSBuild not found. Run from Developer Command Prompt for VS 2022 && exit /b 1)
	@echo Environment check passed
	@echo   Solution: $(SOLUTION)
	@echo   Project:  $(PROJECT)
	@echo   Platform: $(PLATFORM)
	@echo   MSBuild:  Available

# Show build information
.PHONY: info
info:
	@echo ========================================
	@echo Windows ARM64 Project Information
	@echo ========================================
	@echo Solution:         $(SOLUTION)
	@echo Project:          $(PROJECT)
	@echo Platform:         $(PLATFORM)
	@echo Default Config:   $(DEFAULT_CONFIG)
	@echo Build Directory:  $(BUILD_DIR)
	@echo Output Directory: $(BUILD_OUTPUT_DIR)
	@echo.
	@echo Debug output:     $(BUILD_OUTPUT_DIR)\Debug\arm64_sample.exe
	@echo Release output:   $(BUILD_OUTPUT_DIR)\Release\arm64_sample.exe
