#include <iostream>
#include "math_operations.h"

void print_architecture_info() {
    std::cout << "=== ARM64 Sample Application ===" << std::endl;
    std::cout << "Architecture: ARM64 (AArch64)" << std::endl;
    
#ifdef _M_ARM64
    std::cout << "Compiled for: ARM64 (_M_ARM64 defined)" << std::endl;
#endif

#ifdef _DEBUG
    std::cout << "Build Configuration: Debug" << std::endl;
#else
    std::cout << "Build Configuration: Release" << std::endl;
#endif

    std::cout << "C++ Standard: " << __cplusplus << std::endl;
    std::cout << "================================" << std::endl << std::endl;
}

int main() {
    print_architecture_info();
    
    // Demonstrate basic math operations
    std::cout << "Math Operations Demo:" << std::endl;
    
    int a = 42;
    int b = 17;
    
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "Addition: " << a << " + " << b << " = " << add(a, b) << std::endl;
    std::cout << "Subtraction: " << a << " - " << b << " = " << subtract(a, b) << std::endl;
    std::cout << "Multiplication: " << a << " * " << b << " = " << multiply(a, b) << std::endl;
    std::cout << "Division: " << a << " / " << b << " = " << divide(a, b) << std::endl;
    std::cout << std::endl;
    
    // Demonstrate floating-point operations
    double x = 3.14159;
    double y = 2.71828;
    
    std::cout << "Floating-point operations:" << std::endl;
    std::cout << "x = " << x << ", y = " << y << std::endl;
    std::cout << "x + y = " << add(x, y) << std::endl;
    std::cout << "x * y = " << multiply(x, y) << std::endl;
    std::cout << std::endl;
    
    // Demonstrate power function
    std::cout << "Power function:" << std::endl;
    std::cout << "2^10 = " << power(2.0, 10) << std::endl;
    std::cout << "5^3 = " << power(5.0, 3) << std::endl;
    
    std::cout << "";
    std::cout << "Press Enter to exit...";
    std::cin.get();
    
    return 0;
}
