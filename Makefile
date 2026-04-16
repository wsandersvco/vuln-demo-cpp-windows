# Detect architecture
UNAME_M := $(shell uname -m)

ifeq ($(UNAME_M),x86_64)
    # Linux x86_64 - use cross-compiler for ARM64
    CC = aarch64-linux-gnu-g++
    CXX = aarch64-linux-gnu-g++
    # Use ARM64 library paths for cross-compilation
    ARM64_LIB_PATH = /usr/lib/aarch64-linux-gnu
    LDFLAGS = -lm -lstdc++ -L$(ARM64_LIB_PATH) -lkrb5 -lgssapi_krb5 -lk5crypto -lkrb5support -lcom_err
else ifeq ($(UNAME_M),aarch64)
    # Native ARM64 Linux
    CC = g++
    CXX = g++
    LDFLAGS = -lm -lstdc++ -lkrb5 -lgssapi_krb5 -lk5crypto -lkrb5support -lcom_err -lkeyutils
else
    # Default to native compiler
    CC = g++
    CXX = g++
    LDFLAGS = -lm -lstdc++
endif

# Compiler flags
CFLAGS = -Wall -Wextra -march=armv8-a -save-temps=obj
CXXFLAGS = -Wall -Wextra -march=armv8-a -std=c++17 -save-temps=obj

# Directories
BUILD_DIR = build
VERAOUT_DIR = veraout
PROJECT_DIR = .

# Target executable
TARGET = $(BUILD_DIR)/arm64_sample

# Source files
SOURCES = main.cpp utils.cpp verademo_vulns.cpp
OBJECTS = $(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))

# Preprocessed files that will be generated
PREPROCESSED = $(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.ii))

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile C++ source files to object files
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) arm64_sample.zip ${VERAOUT_DIR}

# Display preprocessed files
show-preprocessed:
	@echo "Preprocessed files (.ii):"
	@ls -lh $(BUILD_DIR)/*.ii 2>/dev/null || echo "No preprocessed files found. Run 'make' first."

# Veracode package
veracode-package:
	veracode package -s $(PROJECT_DIR) -a -t directory -o veraout

# Phony targets
.PHONY: all clean show-preprocessed veracode-package
