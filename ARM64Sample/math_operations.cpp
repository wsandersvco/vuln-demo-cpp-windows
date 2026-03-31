#include "math_operations.h"
#include <cmath>

// Integer arithmetic operations
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

double divide(int a, int b) {
    if (b == 0) {
        return 0.0; // Handle division by zero
    }
    return static_cast<double>(a) / static_cast<double>(b);
}

// Floating-point arithmetic operations
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (std::abs(b) < 1e-10) {
        return 0.0; // Handle division by zero
    }
    return a / b;
}

// Advanced operations
double power(double base, int exponent) {
    return std::pow(base, exponent);
}
