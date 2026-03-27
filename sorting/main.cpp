#include "sorting.h"
#include "../commons/vector_utils.h"
#include "../commons/commons.h"
#include <unistd.h>
#include <iostream>
#include <string>
#include <random>

using std::cout;
using std::vector;

void show_help()
{
    cout << "Utility to sort randomly generated integers using various sorting arlgoritms\n";
    cout << "Arguments:\n";
    cout << "p number of integers to generate and sort - default 10000\n";
    cout << "n minimum integer to generate - default 0\n";
    cout << "m maximum integer to generate - default 10\n";
    cout << "Example for sorting 5 integers in range [-10, 10]: program_name -p 5 -n -10 -m 10\n";
}

int main(int argc, char**argv)
{

    // Parse cmd args using getopt
    int c;
    long int num_ele=15000, min=0, max=10;
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

    if (argc < 2) {
        show_help();
        exit(0);
    }

    cout << "Creating vector with " << num_ele << " numbers in range [" << min << "," << max << "]...\n";

    vector<int> unsorted_vector (num_ele);

    std::random_device rn_dev;
    std::mt19937 rng(rn_dev());
    std::uniform_int_distribution uniform_int_dist(min,max);

    std::generate(unsorted_vector.begin(), unsorted_vector.end(), [&rng, &uniform_int_dist](){
        return uniform_int_dist(rng);
    });

    auto sort_cb_fun = [](const int& x,const int& y, const my_sorting::SORTING_ORDER sort_ord) -> bool {
        if (sort_ord == my_sorting::SORTING_ORDER::ASC)
        {
            if (x <= y) return true;
        }
        else
        {
            if (x > y) return true;
        }
        return false;
    };

    print_vec(unsorted_vector, "Input unsorted vector");

    cout << "Applying selection sort..." << "\n";
    {
        ExecutionTimerMs execTimer("Selection Sort Function");
        my_sorting::sel_sort<int>(unsorted_vector, my_sorting::SORTING_ORDER::ASC, sort_cb_fun);
    }
    print_vec(unsorted_vector, "Sorted vector");

    cout << "Unsorting vector..." << "\n";
    std::shuffle(unsorted_vector.begin(), unsorted_vector.end(), rng);
    print_vec(unsorted_vector, "Unsorted vector");

    cout << "Applying insertion sort..." << "\n";
    {
        ExecutionTimerMs execTimer("Selection Sort Function");
        my_sorting::ins_sort<int>(unsorted_vector, my_sorting::SORTING_ORDER::ASC, sort_cb_fun);
    }
    print_vec(unsorted_vector, "Sorted vector");

    cout << "Unsorting vector..." << "\n";
    std::shuffle(unsorted_vector.begin(), unsorted_vector.end(), rng);
    print_vec(unsorted_vector, "Unsorted vector");

    cout << "Applying bubble sort..." << "\n";
    {
        ExecutionTimerMs execTimer("Selection Sort Function");
        my_sorting::bubble_sort<int>(unsorted_vector, my_sorting::SORTING_ORDER::ASC,sort_cb_fun);
    }
    print_vec(unsorted_vector, "Sorted vector");

    cout << "Unsorting vector..." << "\n";
    std::shuffle(unsorted_vector.begin(), unsorted_vector.end(), rng);
    print_vec(unsorted_vector, "Unsorted vector");

    cout << "Applying merge sort..." << "\n";
    {
        ExecutionTimerMs execTimer("Selection Sort Function");
        my_sorting::merge_sort<int>(unsorted_vector, my_sorting::SORTING_ORDER::ASC, sort_cb_fun);
    }
    print_vec(unsorted_vector, "Sorted vector");

    cout << "Unsorting vector..." << "\n";
    std::shuffle(unsorted_vector.begin(), unsorted_vector.end(), rng);
    print_vec(unsorted_vector, "Unsorted vector");

    cout << "Applying quick sort..." << "\n";
    {
        ExecutionTimerMs execTimer("Selection Sort Function");
        my_sorting::quick_sort<int>(unsorted_vector, my_sorting::SORTING_ORDER::ASC, sort_cb_fun);
    }
    print_vec(unsorted_vector, "Sorted vector");

    return 0;
}
