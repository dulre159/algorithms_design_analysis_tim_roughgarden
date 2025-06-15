#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <chrono>

using std::cout;
using std::string;
using std::to_string;
using std::tuple;
using std::get;
using std::min;
/* Stuff to measure execution time */
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

// Multiplication without recursion
unsigned int basic_integer_mul(unsigned int x, unsigned int y)
{
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

int main(int argc, char**argv)
{   
    /*srand(time(0));
    uint min = 1000, max = 100000;
    for (int i=0; i <1000; i++)
    {

        unsigned int a = (rand()%max)+min, b = (rand()%max)+min;

        unsigned int b_mul_res = basic_integer_mul(a,b);
        unsigned int rec_mul_res = recursive_integer_mul(a,b);
        unsigned int kartsuba_mul_res = karatsuba_integer_mul(a,b);

        cout << "Basic mul: "<< a << "x" << b << " = " << b_mul_res<< "\n";
        cout << "Recursive mul: "<< a << "x" << b << " = " << rec_mul_res << "\n";
        cout << "Karatsuba mul: "<< a << "x" << b << " = " << kartsuba_mul_res << "\n";

        if (b_mul_res != rec_mul_res)
        {
            cout << "Failed recursive mul...";
            break;
        }

    }*/

    unsigned int a = 123459999, b = 7896349;

    auto t1 = high_resolution_clock::now();
    unsigned int b_mul_res = basic_integer_mul(a,b);
    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    unsigned int bmt = ms_int.count();

    t1 = high_resolution_clock::now();
    unsigned int rec_mul_res = recursive_integer_mul(a,b);
    t2 = high_resolution_clock::now();
    ms_int = duration_cast<milliseconds>(t2 - t1);
    unsigned int rmt = ms_int.count();

    t1 = high_resolution_clock::now();
    unsigned int kartsuba_mul_res = karatsuba_integer_mul(a,b);
    t2 = high_resolution_clock::now();
    ms_int = duration_cast<milliseconds>(t2 - t1);
    unsigned int kmt = ms_int.count();

    cout << "Basic mul: "<< a << "x" << b << " = " << b_mul_res << " computed in "<< bmt << "ms" << "\n";
    cout << "Recursive mul: "<< a << "x" << b << " = " << rec_mul_res << " computed in "<< rmt << "ms" << "\n";
    cout << "Karatsuba mul: "<< a << "x" << b << " = " << kartsuba_mul_res << " computed in "<< kmt << "ms" << "\n";
    
    return 0;
}