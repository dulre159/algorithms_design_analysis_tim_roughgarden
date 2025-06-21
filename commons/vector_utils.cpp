#include "vector_utils.h"
#include <iostream>

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
    int swap_helper;

    srand(time(0));

    while(max_runs-- > 0) {
        // Generate a random number between 0 and input_vector.size()
        int randomNum1 = rand() % (input_vector.size()-1);
        // Generate a random number between 0 and input_vector.size()
        int randomNum2 = rand() % (input_vector.size()-1);

        // Swap number at position randomNum1 with randomNum2
        swap_helper = input_vector[randomNum1];
        input_vector[randomNum1] = input_vector[randomNum2];
        input_vector[randomNum2] = swap_helper;
    }
}