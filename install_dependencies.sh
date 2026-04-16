#!/bin/bash
# Install Kerberos development libraries for building ARM64 C++ application

set -e

echo "Installing Kerberos development libraries..."

# Detect the distribution
if [ -f /etc/os-release ]; then
    . /etc/os-release
    DISTRO=$ID
else
    echo "Cannot detect Linux distribution"
    exit 1
fi

# Detect architecture
ARCH=$(uname -m)
echo "Detected architecture: $ARCH"
echo "Detected distribution: $DISTRO"

case $DISTRO in
    ubuntu|debian)
        echo "Installing packages for Debian/Ubuntu..."
        
        # Update package lists
        apt-get update
        
        # Install Kerberos development libraries
        apt-get install -y \
            libkrb5-dev \
            libgssapi-krb5-2 \
            libk5crypto3 \
            libkrb5support0 \
            libcom-err2 \
            libkeyutils1
        
        # If on x86_64, also install ARM64 cross-compilation tools and libraries
        if [ "$ARCH" = "x86_64" ]; then
            echo "Installing ARM64 cross-compilation toolchain..."
            apt-get install -y \
                gcc-aarch64-linux-gnu \
                g++-aarch64-linux-gnu \
                binutils-aarch64-linux-gnu
            
            # Add ARM64 architecture for cross-compilation libraries
            dpkg --add-architecture arm64
            apt-get update
            
            # Install ARM64 versions of the libraries
            apt-get install -y \
                libkrb5-dev:arm64 \
                libgssapi-krb5-2:arm64 \
                libk5crypto3:arm64 \
                libkrb5support0:arm64 \
                libcom-err2:arm64 \
                libkeyutils1:arm64 || echo "Note: ARM64 library installation may require additional configuration"
        fi
        ;;
        
    fedora|rhel|centos|rocky|almalinux)
        echo "Installing packages for RHEL/Fedora/CentOS..."
        
        # Install Kerberos development libraries
        dnf install -y \
            krb5-devel \
            krb5-libs \
            libcom_err \
            keyutils-libs
        
        # If on x86_64, also install ARM64 cross-compilation tools
        if [ "$ARCH" = "x86_64" ]; then
            echo "Installing ARM64 cross-compilation toolchain..."
            dnf install -y \
                gcc-aarch64-linux-gnu \
                binutils-aarch64-linux-gnu || echo "ARM64 cross-compiler may not be available in default repos"
        fi
        ;;
        
    arch|manjaro)
        echo "Installing packages for Arch Linux..."
        
        # Install Kerberos development libraries
        pacman -Sy --noconfirm \
            krb5 \
            keyutils
        
        # If on x86_64, install cross-compilation tools
        if [ "$ARCH" = "x86_64" ]; then
            echo "Installing ARM64 cross-compilation toolchain..."
            pacman -Sy --noconfirm \
                aarch64-linux-gnu-gcc || echo "ARM64 cross-compiler may require AUR"
        fi
        ;;
        
    *)
        echo "Unsupported distribution: $DISTRO"
        echo "Please manually install the following packages:"
        echo "  - Kerberos 5 development libraries (libkrb5-dev or krb5-devel)"
        echo "  - GSSAPI Kerberos library"
        echo "  - Kerberos crypto library"
        echo "  - com_err library"
        echo "  - keyutils library"
        if [ "$ARCH" = "x86_64" ]; then
            echo "  - ARM64 cross-compilation toolchain (aarch64-linux-gnu-gcc)"
        fi
        exit 1
        ;;
esac

echo ""
echo "✓ Dependencies installed successfully!"
echo ""

# Verify installation
echo "Verifying installation..."
if [ "$ARCH" = "x86_64" ]; then
    if command -v aarch64-linux-gnu-g++ &> /dev/null; then
        echo "✓ ARM64 cross-compiler found: $(aarch64-linux-gnu-g++ --version | head -n1)"
    else
        echo "✗ ARM64 cross-compiler not found"
    fi
else
    if command -v g++ &> /dev/null; then
        echo "✓ Native compiler found: $(g++ --version | head -n1)"
    else
        echo "✗ Native compiler not found"
    fi
fi

# Check for Kerberos headers
if [ -f /usr/include/krb5.h ] || [ -f /usr/include/krb5/krb5.h ]; then
    echo "✓ Kerberos headers found"
else
    echo "✗ Kerberos headers not found"
fi

echo ""
echo "You can now build the project with: make"
