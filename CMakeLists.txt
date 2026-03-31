cmake_minimum_required(VERSION 3.15)

# Project definition
project(ARM64Sample
    VERSION 1.0.0
    DESCRIPTION "ARM64 Sample C++ Application"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Platform-specific settings
if(APPLE)
    # For macOS ARM64 (Apple Silicon)
    set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "Build architectures for macOS" FORCE)
    message(STATUS "Building for macOS ARM64 (Apple Silicon)")
elseif(WIN32)
    # For Windows ARM64
    if(CMAKE_GENERATOR_PLATFORM STREQUAL "ARM64")
        message(STATUS "Building for Windows ARM64")
    endif()
elseif(UNIX)
    # For Linux ARM64
    message(STATUS "Building for Linux ARM64")
endif()

# Display build configuration
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "System: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Processor: ${CMAKE_SYSTEM_PROCESSOR}")

# Source files
set(SOURCES
    ARM64Sample/main.cpp
    ARM64Sample/math_operations.cpp
)

set(HEADERS
    ARM64Sample/math_operations.h
)

# Create executable
add_executable(ARM64Sample ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(ARM64Sample PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ARM64Sample
)

# Compiler flags
if(MSVC)
    # MSVC-specific flags
    target_compile_options(ARM64Sample PRIVATE
        /W3           # Warning level 3
        /permissive-  # Conformance mode
    )
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(ARM64Sample PRIVATE /O2)
    endif()
else()
    # GCC/Clang flags (macOS, Linux)
    target_compile_options(ARM64Sample PRIVATE
        -Wall
        -Wextra
        -pedantic
    )
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(ARM64Sample PRIVATE -O3)
    endif()
endif()

# Platform-specific definitions
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(ARM64Sample PRIVATE _DEBUG)
else()
    target_compile_definitions(ARM64Sample PRIVATE NDEBUG)
endif()

# Installation rules
install(TARGETS ARM64Sample
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Print final configuration
message(STATUS "ARM64Sample configuration complete")
