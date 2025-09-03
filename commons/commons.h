#pragma once

#include <limits>

// Checks if two single precision floating point numbers are equal
bool are_equal_f(float a, float b, float epsilon = std::numeric_limits<float>::epsilon());

// Checks if two double precision floating point numbers are equal
bool are_equal_d(double a, double b, double epsilon = std::numeric_limits<double>::epsilon());

// Checks if a is greater than b for floats
bool is_greater_than_f(float a, float b, float epsilon = std::numeric_limits<float>::epsilon());

// Checks if a is less than b for floats
bool is_less_than_f(float a, float b, float epsilon = std::numeric_limits<float>::epsilon());

// Checks if a is greater than b for doubles
bool is_greater_than_d(double a, double b, double epsilon = std::numeric_limits<double>::epsilon());

// Checks if a is less than b for doubles
bool is_less_than_d(double a, double b, double epsilon = std::numeric_limits<double>::epsilon());