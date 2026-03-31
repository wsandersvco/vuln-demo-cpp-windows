# Simple Makefile for macOS/Linux builds
# For cross-platform builds, use CMake (see BUILD.md)

CXX = arch -arm64 clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -target arm64-apple-darwin
SRCDIR = ARM64Sample
BUILDDIR = $(SRCDIR)/build
TARGET = $(BUILDDIR)/ARM64Sample.out
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/math_operations.cpp
HEADERS = $(SRCDIR)/math_operations.h
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

# Platform detection
UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)

ifeq ($(UNAME_S),Darwin)
    $(info Building for macOS ARM64 (forced))
endif

ifeq ($(UNAME_S),Linux)
    ifeq ($(UNAME_M),aarch64)
        $(info Building for Linux ARM64)
    endif
endif

.PHONY: all clean run

all: $(TARGET)

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(TARGET): $(BUILDDIR) $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)
	@echo "Build complete: $(TARGET)"
	@echo "Run with: ./$(TARGET)"

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)
	@echo "Clean complete"

run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -g -D_DEBUG
debug: clean $(TARGET)

# Show build info
info:
	@echo "System: $(UNAME_S)"
	@echo "Architecture: $(UNAME_M)"
	@echo "Compiler: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"
	@echo "Sources: $(SOURCES)"
