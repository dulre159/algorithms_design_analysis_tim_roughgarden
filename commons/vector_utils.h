#pragma once

#include <vector>
#include <iostream>

using std::cout;
using std::vector;

/* Vector pretty printing */
template<class T>
void print_vec(vector<T> &input_vector)
{
    cout << "[ ";

    if (input_vector.size() > 100)
    {
        // If the vector has more then 100 elements just print the first 50 and the last 50
        for (unsigned int i=0; i < 50; i++) {
            cout << input_vector[i] << " ";
        }

        cout << "... ";

        for (unsigned int i=input_vector.size()-51; i < input_vector.size(); i++) {
            cout << input_vector[i] << " ";
        }
    }

    else {
        for (unsigned int i=0; i < input_vector.size(); i++) {
            cout << input_vector[i] << " ";
        }
    }

    cout << "]";
}