#include "../commons/commons.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>

using std::cout;
using std::string;
using std::to_string;
using std::tuple;
using std::get;
using std::max;

// Multiplication without recursion
constexpr unsigned long long basic_integer_mul(unsigned int x, unsigned int y)
{
    /*TODO*/
    return static_cast<unsigned long long>(x)*y;
}

// Counts number of digits in a number
unsigned int count_num_digit(unsigned int n)
{
    unsigned int ret = 0;
    
    if (n==0) return 1;
    
    while(n > 0) {
        n=n/10; 
        ret++;
    }
    
    return ret;
}

// Splits number according to m
tuple<unsigned long long, unsigned long long> split_num(unsigned int x, unsigned int m)
{
    // Convert number in string
    unsigned int power_of_10 = pow(10, m);
    unsigned long long a = x / power_of_10;
    unsigned long long b = x % power_of_10;

    //std::cout << "Input " << x << " m " << m << " a " << a << " b" << b << "\n";

    return tuple<unsigned long long,unsigned long long>{a,b};
}


// Recursive multiplication
// Input numbers x and y assumed integers and having n digits
// 'a' and 'b' are respectively the first and second half of x
// 'c' and 'd' are respectively the first and second half of y
// select m that is lower then n
// B is the base; assume B=10
// x = (B^m)*a + b ; y = (B^m)*c + d
// x*y = B^2m * ac + B^m * (ad+bc) + bd
unsigned long long recursive_integer_mul(unsigned int x, unsigned int y)
{
    if (x < 10 || y < 10)
    {
        return x*y;
    }
    
    unsigned int xdc = count_num_digit(x);
    unsigned int ydc = count_num_digit(y);
    unsigned int m = max(xdc, ydc)/2;

    auto [a, b] = split_num(x, m);
    auto [c, d] = split_num(y, m);

    unsigned long long ac = recursive_integer_mul(a, c);
    unsigned long long ad = recursive_integer_mul(a, d);
    unsigned long long bc = recursive_integer_mul(b, c);
    unsigned long long bd = recursive_integer_mul(b, d);

    return (pow(10, 2*m)*ac) + (pow(10, m)*(ad + bc)) + bd;
}

// Karatsuba multiplication
// Input numbers x and y assumed integers
// 'a' and 'b' are respectively the first and second half of x
// 'c' and 'd' are respectively the first and second half of y
// x = (10^(n/2))*a + b ; y = (10^(n/2))*c + d
// x*y = 10^n * ac + 10^n/2 * (ad+bc) + bd
// (ad+bc) = (a+b)(c+d) - ac - bd
unsigned long long karatsuba_integer_mul(unsigned int x, unsigned int y)
{
    if (x < 10 || y < 10)
    {
        return x*y;
    }

    unsigned int xdc = count_num_digit(x);
    unsigned int ydc = count_num_digit(y);
    unsigned int m = max(xdc, ydc)/2;

    auto [a, b] = split_num(x, m);
    auto [c, d] = split_num(y, m);
    
    unsigned long long ac = karatsuba_integer_mul(a, c);
    unsigned long long bd = karatsuba_integer_mul(b, d);
    // (a+b)(c+d)
    unsigned long long apbtcpd = karatsuba_integer_mul(a+b, c+d);
    // (ad + bc)
    unsigned long long atdpdtc = apbtcpd - ac - bd;

    return (pow(10, 2*m)*ac) + (pow(10, m)*atdpdtc) + bd;
}

int main(int /*argc*/, char** /*argv*/)
{   
    unsigned int a = 123459999, b = 7896349;

    unsigned long long b_mul_res = 0, rec_mul_res = 0, kartsuba_mul_res = 0;
    {
        ExecutionTimerMs execTimer_("Basic multiplication function");
        b_mul_res = basic_integer_mul(a,b);
    }

    {   
        ExecutionTimerMs execTimer_("Recursive multiplication function"); 
        rec_mul_res = recursive_integer_mul(a,b);
    }

    {   
        ExecutionTimerMs execTimer_("Karatsuba multiplication function"); 
        kartsuba_mul_res = karatsuba_integer_mul(a,b);
    }

    cout << "Basic multiplication result: "<< a << "x" << b << " = " << b_mul_res << "\n";
    cout << "Recursive multiplication result: "<< a << "x" << b << " = " << rec_mul_res << "\n";
    cout << "Karatsuba multiplication result: "<< a << "x" << b << " = " << kartsuba_mul_res << "\n";
    
    return 0;
}