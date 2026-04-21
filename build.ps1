# Windows ARM64 Build Script
# Requires: Visual Studio 2022 with ARM64 tools
# Usage: .\build.ps1 [-Configuration Debug|Release] [-Clean] [-Rebuild] [-Help]

param(
    [Parameter()]
    [ValidateSet('Debug', 'Release')]
    [string]$Configuration = 'Release',
    
    [Parameter()]
    [switch]$Clean,
    
    [Parameter()]
    [switch]$Rebuild,
    
    [Parameter()]
    [switch]$Help
)

# Display help
if ($Help) {
    Write-Host "Windows ARM64 Build Script" -ForegroundColor Cyan
    Write-Host "==========================" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Usage: .\build.ps1 [-Configuration Debug|Release] [-Clean] [-Rebuild] [-Help]"
    Write-Host ""
    Write-Host "Parameters:" -ForegroundColor Yellow
    Write-Host "  -Configuration    Build configuration (Debug or Release). Default: Release"
    Write-Host "  -Clean            Clean build artifacts without building"
    Write-Host "  -Rebuild          Clean and rebuild the project"
    Write-Host "  -Help             Display this help message"
    Write-Host ""
    Write-Host "Examples:" -ForegroundColor Yellow
    Write-Host "  .\build.ps1                          # Build Release configuration"
    Write-Host "  .\build.ps1 -Configuration Debug     # Build Debug configuration"
    Write-Host "  .\build.ps1 -Clean                   # Clean build artifacts"
    Write-Host "  .\build.ps1 -Rebuild                 # Clean and rebuild Release"
    Write-Host ""
    exit 0
}

$SolutionFile = "arm64_sample.sln"
$Platform = "ARM64"
$BuildAction = if ($Rebuild) { "Rebuild" } elseif ($Clean) { "Clean" } else { "Build" }

# Check if solution file exists
if (-not (Test-Path $SolutionFile)) {
    Write-Host "ERROR: Solution file not found: $SolutionFile" -ForegroundColor Red
    exit 1
}

# Check if MSBuild is available
$MSBuildPath = & "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" `
    -latest -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe `
    -prerelease 2>$null | Select-Object -First 1

if (-not $MSBuildPath -or -not (Test-Path $MSBuildPath)) {
    Write-Host "ERROR: MSBuild not found. Please install Visual Studio 2022 with C++ ARM64 tools." -ForegroundColor Red
    Write-Host "Or run this script from Developer Command Prompt for VS 2022" -ForegroundColor Yellow
    exit 1
}

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Windows ARM64 C++ Build" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Solution:      $SolutionFile"
Write-Host "Configuration: $Configuration"
Write-Host "Platform:      $Platform"
Write-Host "Action:        $BuildAction"
Write-Host "MSBuild:       $MSBuildPath"
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Build the project
$BuildArgs = @(
    $SolutionFile,
    "/t:$BuildAction",
    "/p:Configuration=$Configuration",
    "/p:Platform=$Platform",
    "/m",
    "/v:minimal"
)

Write-Host "Executing: MSBuild $($BuildArgs -join ' ')" -ForegroundColor Yellow
Write-Host ""

& $MSBuildPath $BuildArgs

$ExitCode = $LASTEXITCODE

Write-Host ""
if ($ExitCode -eq 0) {
    Write-Host "========================================" -ForegroundColor Green
    Write-Host "$BuildAction completed successfully!" -ForegroundColor Green
    Write-Host "========================================" -ForegroundColor Green
    
    if (-not $Clean) {
        $OutputPath = "build\$Platform\$Configuration\arm64_sample.exe"
        if (Test-Path $OutputPath) {
            Write-Host ""
            Write-Host "Executable: $OutputPath" -ForegroundColor Green
            $FileInfo = Get-Item $OutputPath
            Write-Host "Size:       $($FileInfo.Length) bytes"
            Write-Host "Modified:   $($FileInfo.LastWriteTime)"
            Write-Host ""
            Write-Host "To run: .\$OutputPath" -ForegroundColor Yellow
        }
    }
} else {
    Write-Host "========================================" -ForegroundColor Red
    Write-Host "$BuildAction failed with exit code: $ExitCode" -ForegroundColor Red
    Write-Host "========================================" -ForegroundColor Red
    exit $ExitCode
}

exit 0
