#include "main.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <chrono>
#include <unistd.h>

using std::cout;
using std::vector;
/* Stuff to measure execution time */
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

// Selection sort
// For each element A compare it with all the others B
// If the element A is bigger than (or lower than) B then swap them
void sel_sort(vector<int> &input_vector, SORTING_ORDER order)
{
    int swap_helper;
    for (int i = 0; i < input_vector.size(); i++)
    {
        for (int j = 0; j < input_vector.size(); j++)
        {
            if (order == SORTING_ORDER::DESC) {
                if (input_vector[j] < input_vector[i]) {
                    swap_helper = input_vector[i];
                    input_vector[i] = input_vector[j];
                    input_vector[j] = swap_helper;
                }
            } else
            {
                if (input_vector[j] > input_vector[i]) {
                    swap_helper = input_vector[i];
                    input_vector[i] = input_vector[j];
                    input_vector[j] = swap_helper;
                }
            }
        }

    }
}


// Bubble sort
// Compare each element A with the next one B
// Swap A with B if necessary
// Reiterate until no swaps are necessary (vector is sorted)
void bubble_sort(vector<int> &input_vector, SORTING_ORDER order)
{
    bool did_swap = true;
    int swap_helper;
    int v_size = input_vector.size();
    while(did_swap==true) {

        did_swap = false;

        for (int i = 0; i < v_size-1; i++) 
        {
            if (order == SORTING_ORDER::DESC)
            {
                if (input_vector[i] < input_vector[i+1])
                {
                    swap_helper = input_vector[i];
                    input_vector[i] = input_vector[i+1];
                    input_vector[i+1] = swap_helper;
                    did_swap = true;
                }
            }
            else
            {
                if (input_vector[i] > input_vector[i+1])
                {
                    swap_helper = input_vector[i];
                    input_vector[i] = input_vector[i+1];
                    input_vector[i+1] = swap_helper;
                    did_swap = true;
                }
            }
        }
    }
}

// Insertion sort
// Start from element n = 1
// Compare element n to element n-1
// If element n is less then element n-1; move element n-1 to n+1 and place n into n-1
void ins_sort(vector<int> &input_vector, SORTING_ORDER order)
{
    int current_selection;
    for (int i = 1; i < input_vector.size(); i++)
    {
        current_selection = input_vector[i];
        
        for (int j = i-1; j >= 0; j--)
        {
            if (order == SORTING_ORDER::ASC)
            {
                if (current_selection < input_vector[j])
                {
                    input_vector[j+1] = input_vector[j];
                    input_vector[j] = current_selection;
                }
            }
            else
            {
                if (current_selection > input_vector[j])
                {
                    input_vector[j+1] = input_vector[j];
                    input_vector[j] = current_selection;
                }
            }

        }

    }
}

void show_help()
{
    cout << "Utility to sort randomly generated integers using various sorting arlgoritms\n";
    cout << "Arguments:\n";
    cout << "p number of integers to generate and sort - default 10\n";
    cout << "n minimum integer to generate - default 0\n";
    cout << "m maximum integer to generate - default 10\n";
    cout << "Example for sorting 5 integers in range [-10, 10]: program_name -p 5 -n -10 -m 10\n";
}

int main(int argc, char**argv)
{

    // Parse cmd args using getopt
    int c;
    long int num_ele=10, min=0, max=10;
    while((c = getopt(argc, argv, ":p:m:n:h")) != -1)
    {
        switch (c)
        {
        case 'p':
            num_ele = strtol(optarg, NULL, 10);
            break;
        case 'm':
            max = strtol(optarg, NULL, 10);
            break;
        case 'n':
            min = strtol(optarg, NULL, 10);
            break;
        case 'h':
            show_help();
            exit(0);
            break;
        default:
            break;
        }
    }

    if (num_ele == 0) {
        cout << "Invalid number of elements to sort...\n";
        exit(-1);
    }

    cout << "Creating vector with " << num_ele << " numbers in range [" << min << "," << max << "]...\n";

    vector<int> unsorted_vector;

    init_vec(unsorted_vector, num_ele, min, max);

    cout << "Unsorted vector: ";
    print_vec(unsorted_vector);
    cout << "\n";

    cout << "Applying selection sort..." << "\n";
    auto t1 = high_resolution_clock::now();
    sel_sort(unsorted_vector, SORTING_ORDER::ASC);
    auto t2 = high_resolution_clock::now();

    milliseconds ms_int = duration_cast<milliseconds>(t2 - t1);

    cout << "Vector after selection sort[ execution time: "<< ms_int.count() <<" ms ]: ";
    print_vec(unsorted_vector);
    cout << "\n";

    cout << "Unsorting vector..." << "\n";
    unsort_vector(unsorted_vector);

    cout << "Unsorted vector: ";
    print_vec(unsorted_vector);
    cout << "\n";

    cout << "Applying insertion sort..." << "\n";
    t1 = high_resolution_clock::now();
    ins_sort(unsorted_vector, SORTING_ORDER::ASC);
    t2 = high_resolution_clock::now();

    ms_int = duration_cast<milliseconds>(t2 - t1);

    cout << "Vector after insertion sort[ execution time: "<< ms_int.count() <<" ms ]: ";
    print_vec(unsorted_vector);
    cout << "\n";

    cout << "Unsorting vector..." << "\n";
    unsort_vector(unsorted_vector);

    cout << "Unsorted vector: ";
    print_vec(unsorted_vector);
    cout << "\n";

    cout << "Applying bubble sort..." << "\n";
    t1 = high_resolution_clock::now();
    bubble_sort(unsorted_vector, SORTING_ORDER::ASC);
    t2 = high_resolution_clock::now();

    ms_int = duration_cast<milliseconds>(t2 - t1);

    cout << "Vector after bubble sort[ execution time: "<< ms_int.count() <<" ms ]: ";
    print_vec(unsorted_vector);
    cout << "\n";

    cout << "Unsorting vector..." << "\n";
    unsort_vector(unsorted_vector);

    cout << "Unsorted vector: ";
    print_vec(unsorted_vector);
    cout << "\n";

    cout << "Applying merge sort..." << "\n";
    t1 = high_resolution_clock::now();
    merge_sort<int>(unsorted_vector, SORTING_ORDER::ASC, [](const int& x,const int& y, const SORTING_ORDER sort_ord) -> bool {
        if (sort_ord == SORTING_ORDER::ASC)
        {
            if (x < y) return true;
            else return false;
        }
        else
        {
            if (x > y) return true;
            else return false;
        }
    });
    t2 = high_resolution_clock::now();

    ms_int = duration_cast<milliseconds>(t2 - t1);

    cout << "Vector after merge sort[ execution time: "<< ms_int.count() <<" ms ]: ";
    print_vec(unsorted_vector);
    cout << "\n";

    return 0;
}
