#include "commons.h"
#include <cmath>

// Checks if two single precision floating point numbers are equal
bool are_equal_f(float a, float b, float epsilon)
{
    return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

// Checks if two double precision floating point numbers are equal
bool are_equal_d(double a, double b, double epsilon)
{
    return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

// Checks if a is greater than b for floats
bool is_greater_than_f(float a, float b, float epsilon)
{
    return (a - b) > ( (std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
}

// Checks if a is less than b for floats
bool is_less_than_f(float a, float b, float epsilon)
{
    return (b - a) > ( (std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
}

// Checks if a is greater than b for doubles
bool is_greater_than_d(double a, double b, double epsilon)
{
    return (a - b) > ( (std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
}

// Checks if a is less than b for doubles
bool is_less_than_d(double a, double b, double epsilon)
{
    return (b - a) > ( (std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
}