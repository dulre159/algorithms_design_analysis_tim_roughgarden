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
using std::min;

// Multiplication without recursion
unsigned int basic_integer_mul(unsigned int x, unsigned int y)
{
    /*TODO*/
    return x*y;
}

// Counts number of digits in a number
int count_num_digit(int n)
{
    int ret = 0;
    
    if (n==0) return 1;
    
    while(n > 0) {
        n=n/10; 
        ret++;
    };
    
    return ret;
}

// Splits number according to m
tuple<unsigned int, unsigned int> split_num(unsigned int x, unsigned int m)
{
    // Convert number in string
    string x_string = to_string(x/pow(10, m));
    unsigned int num_d_c = count_num_digit(x)+1;
    string x_buff;
    unsigned int a = 0, b = 0;
    for (unsigned int i = 0; i < num_d_c; i++)
    {
        if (x_string[i]=='.') {
            a = stoi(x_buff);
            x_buff.clear();
            continue;
        }
        x_buff.push_back(x_string[i]);
    }

    b = stoi(x_buff);

    return tuple<unsigned int,unsigned int>{a,b};
}


// Recursive multiplication
// Input numbers x and y assumed integers and having n digits
// 'a' and 'b' are the half of x
// 'c' and 'd' are the half of y
// select m that is lower then n
// B is the base; assume B=10
// x = (B^m)*a + b ; y = (B^m)*c + d
// x*y = B^2m * ac + B^m * (ad+bc) + bd
unsigned int recursive_integer_mul(unsigned int x, unsigned int y)
{
    unsigned int xdc = count_num_digit(x);
    unsigned int ydc = count_num_digit(y);

    unsigned int m = (int)min(xdc, ydc)-1;
    unsigned int a = x, b = 0, c = y, d = 0;

    if (m==0)
    {
        return x*y;
    }

    tuple<unsigned int, unsigned int> x_halfs = split_num(x, m);
    a = get<0>(x_halfs);
    b = get<1>(x_halfs);

    tuple<unsigned int, unsigned int> y_halfs = split_num(y, m);
    c = get<0>(y_halfs);
    d = get<1>(y_halfs);

    unsigned int ac = recursive_integer_mul(a, c);
    unsigned int ad = recursive_integer_mul(a, d);
    unsigned int bc = recursive_integer_mul(b, c);
    unsigned int bd = recursive_integer_mul(b, d);

    return (pow(10, 2*m)*ac) + (pow(10, m)*(ad + bc)) + bd;
}

// Karatsuba multiplication
// Input numbers x and y assumed integers
// 'a' and 'b' are the half of x
// 'c' and 'd' are the half of y
// x = (10^(n/2))*a + b ; y = (10^(n/2))*c + d
// x*y = 10^n * ac + 10^n/2 * (ad+bc) + bd
// (ad+bc) = (a+b)(c+d) - ac - bd
unsigned int karatsuba_integer_mul(unsigned int x, unsigned int y)
{
    unsigned int xdc = count_num_digit(x);
    unsigned int ydc = count_num_digit(y);

    unsigned int m = (int)min(xdc, ydc)-1;
    unsigned int a = x, b = 0, c = y, d = 0;

    if (m==0)
    {
        return x*y;
    }

    tuple<unsigned int, unsigned int> x_halfs = split_num(x, m);
    a = get<0>(x_halfs);
    b = get<1>(x_halfs);

    tuple<unsigned int, unsigned int> y_halfs = split_num(y, m);
    c = get<0>(y_halfs);
    d = get<1>(y_halfs);
    
    unsigned int ac = recursive_integer_mul(a, c);
    unsigned int bd = recursive_integer_mul(b, d);
    // (a+b)(c+d)
    unsigned int apbtcpd = recursive_integer_mul(a+b, c+d);
    // (ad + bc)
    unsigned int atdpdtc = apbtcpd - ac - bd;

    return (pow(10, 2*m)*ac) + (pow(10, m)*atdpdtc) + bd;
}

int main(int /*argc*/, char** /*argv*/)
{   
    unsigned int a = 123459999, b = 7896349;

    unsigned int b_mul_res = 0, rec_mul_res = 0, kartsuba_mul_res = 0;
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