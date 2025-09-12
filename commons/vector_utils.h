#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

using std::cout;
using std::vector;

/* Vector pretty printing */
template<class T>
void print_vec(vector<T> &input_vector, unsigned int cut_off=100)
{
    cout << "[ ";

    if (input_vector.size() > cut_off)
    {
        // If the vector has more then 100 elements just print the first 50 and the last 50
        std::for_each(input_vector.cbegin(), input_vector.cbegin()+50, [](T e){ cout << e << " ";});
        cout << "... ";
        std::for_each(input_vector.cend()-50, input_vector.cend(), [](T e){ cout << e << " ";});
    }

    else {
        // Otherwise print all the elements
        std::for_each(input_vector.cbegin(), input_vector.cend(), [](T e){ cout << e << " ";});
    }

    cout << "]";
}