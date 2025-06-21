#include "../commons/vector_utils.h"
#include "../sorting/main.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <chrono>

using std::cout;
using std::vector;
/* Stuff to measure execution time */
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

int main(int argc, char**argv)
{
    vector<int> in_vec;
    unsigned int inversions_counter = 0;
    init_vec(in_vec, 10000, 0, 1000);

    cout << "Vector: ";
    print_vec(in_vec);
    cout << "\n";

    return 0;
}