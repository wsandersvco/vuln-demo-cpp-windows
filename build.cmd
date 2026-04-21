@echo off
REM Windows ARM64 Build Script (Batch)
REM Requires: Visual Studio 2022 with ARM64 tools
REM Usage: build.cmd [Debug|Release] [Clean|Rebuild]

setlocal enabledelayedexpansion

set SOLUTION=arm64_sample.sln
set PLATFORM=ARM64
set CONFIG=%1
set ACTION=%2

if "%CONFIG%"=="" set CONFIG=Release
if "%CONFIG%"=="debug" set CONFIG=Debug
if "%CONFIG%"=="DEBUG" set CONFIG=Debug
if "%CONFIG%"=="release" set CONFIG=Release
if "%CONFIG%"=="RELEASE" set CONFIG=Release

if "%ACTION%"=="" set ACTION=Build
if "%ACTION%"=="clean" set ACTION=Clean
if "%ACTION%"=="CLEAN" set ACTION=Clean
if "%ACTION%"=="rebuild" set ACTION=Rebuild
if "%ACTION%"=="REBUILD" set ACTION=Rebuild

echo ========================================
echo Windows ARM64 C++ Build
echo ========================================
echo Solution:      %SOLUTION%
echo Configuration: %CONFIG%
echo Platform:      %PLATFORM%
echo Action:        %ACTION%
echo ========================================
echo.

REM Check if solution exists
if not exist "%SOLUTION%" (
    echo ERROR: Solution file not found: %SOLUTION%
    exit /b 1
)

REM Find MSBuild using vswhere
for /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe -prerelease`) do (
    set MSBUILD_PATH=%%i
    goto :found_msbuild
)

:not_found
echo ERROR: MSBuild not found. Please install Visual Studio 2022 with C++ ARM64 tools.
echo Or run this script from Developer Command Prompt for VS 2022
exit /b 1

:found_msbuild
echo MSBuild:       %MSBUILD_PATH%
echo.

REM Build the project
"%MSBUILD_PATH%" "%SOLUTION%" /t:%ACTION% /p:Configuration=%CONFIG% /p:Platform=%PLATFORM% /m /v:minimal

if %ERRORLEVEL% neq 0 (
    echo.
    echo ========================================
    echo %ACTION% FAILED with exit code: %ERRORLEVEL%
    echo ========================================
    exit /b %ERRORLEVEL%
)

echo.
echo ========================================
echo %ACTION% completed successfully!
echo ========================================

if "%ACTION%"=="Build" (
    set OUTPUT_PATH=build\%PLATFORM%\%CONFIG%\arm64_sample.exe
    if exist "!OUTPUT_PATH!" (
        echo.
        echo Executable: !OUTPUT_PATH!
        echo To run: !OUTPUT_PATH!
    )
)

exit /b 0
