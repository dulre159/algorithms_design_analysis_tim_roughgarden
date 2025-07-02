#include "vector_utils.h"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using std::cout;
using std::vector;

/* Initialize input vector with random num_ele numbers between min and max */
void init_vec(vector<int> &input_vector, unsigned int num_ele, int min, int max)
{
    if (max < min) {
        cout << "init_vec(...) - Error : max cannot be less than min" << "\n";
        return;
    }

    if (num_ele < 1) {
        cout << "init_vec(...) - Error : the vector must have at least 1 element" << "\n";
        return;
    }

    srand(time(0));
    for (int i=0; i < num_ele; i++) {
        input_vector.push_back((rand() % max)+min);
    }
}


/* Vector pretty printing */ 
void print_vec(vector<int> &input_vector)
{
    cout << "[ ";

    if (input_vector.size() > 100)
    {
        // If the vector has more then 100 elements just print the first 50 and the last 50
        for (int i=0; i < 50; i++) {
            cout << input_vector[i] << " ";
        }

        cout << "... ";

        for (int i=input_vector.size()-51; i < input_vector.size(); i++) {
            cout << input_vector[i] << " ";
        }
    }

    else {
        for (int i=0; i < input_vector.size(); i++) {
            cout << input_vector[i] << " ";
        }
    }

    cout << "]";
}

/* Function to unsort the array */
void unsort_vector(vector<int> &input_vector)
{
    unsigned int max_runs = input_vector.size();
    int swap_helper=0;

    const std::chrono::time_point<std::chrono::steady_clock> cur_time = std::chrono::steady_clock::now();

    std::srand(cur_time.time_since_epoch().count());

    while(max_runs-- > 0) {
        // Generate a random number between 0 and input_vector.size() - 1
        int index0 = std::rand() % input_vector.size();
        // Generate a random number between 0 and input_vector.size() - 1 
        int index1 = std::rand() % input_vector.size();

        // Swap number at position randomNum1 with randomNum2
        swap_helper = input_vector[index0];
        input_vector[index0] = input_vector[index1];
        input_vector[index1] = swap_helper;
    }
}