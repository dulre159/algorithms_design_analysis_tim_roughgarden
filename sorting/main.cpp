#include "main.h"
#include <unistd.h>
#include <iostream>
#include <string>
#include <chrono>
#include <random>

using std::cout;
using std::vector;
/* Stuff to measure execution time */
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

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

    cout << "Unsorted vector: ";
    print_vec(unsorted_vector);
    cout << "\n";

    cout << "Applying selection sort..." << "\n";
    auto t1 = high_resolution_clock::now();
    my_sorting::sel_sort<int>(unsorted_vector, my_sorting::SORTING_ORDER::ASC, sort_cb_fun);
    auto t2 = high_resolution_clock::now();

    milliseconds ms_int = duration_cast<milliseconds>(t2 - t1);

    cout << "Vector after selection sort[ execution time: "<< ms_int.count() <<" ms ]: ";
    print_vec(unsorted_vector);
    cout << "\n";

    cout << "Unsorting vector..." << "\n";
    std::shuffle(unsorted_vector.begin(), unsorted_vector.end(), rng);

    cout << "Unsorted vector: ";
    print_vec(unsorted_vector);
    cout << "\n";

    cout << "Applying insertion sort..." << "\n";
    t1 = high_resolution_clock::now();
    my_sorting::ins_sort<int>(unsorted_vector, my_sorting::SORTING_ORDER::ASC, sort_cb_fun);
    t2 = high_resolution_clock::now();

    ms_int = duration_cast<milliseconds>(t2 - t1);

    cout << "Vector after insertion sort[ execution time: "<< ms_int.count() <<" ms ]: ";
    print_vec(unsorted_vector);
    cout << "\n";

    cout << "Unsorting vector..." << "\n";
    std::shuffle(unsorted_vector.begin(), unsorted_vector.end(), rng);

    cout << "Unsorted vector: ";
    print_vec(unsorted_vector);
    cout << "\n";

    cout << "Applying bubble sort..." << "\n";
    t1 = high_resolution_clock::now();
    my_sorting::bubble_sort<int>(unsorted_vector, my_sorting::SORTING_ORDER::ASC,sort_cb_fun);
    t2 = high_resolution_clock::now();

    ms_int = duration_cast<milliseconds>(t2 - t1);

    cout << "Vector after bubble sort[ execution time: "<< ms_int.count() <<" ms ]: ";
    print_vec(unsorted_vector);
    cout << "\n";

    cout << "Unsorting vector..." << "\n";
    std::shuffle(unsorted_vector.begin(), unsorted_vector.end(), rng);

    cout << "Unsorted vector: ";
    print_vec(unsorted_vector);
    cout << "\n";

    cout << "Applying merge sort..." << "\n";
    t1 = high_resolution_clock::now();
    my_sorting::merge_sort<int>(unsorted_vector, my_sorting::SORTING_ORDER::ASC, sort_cb_fun);
    t2 = high_resolution_clock::now();

    ms_int = duration_cast<milliseconds>(t2 - t1);

    cout << "Vector after merge sort[ execution time: "<< ms_int.count() <<" ms ]: ";
    print_vec(unsorted_vector);
    cout << "\n";

    cout << "Unsorting vector..." << "\n";
    std::shuffle(unsorted_vector.begin(), unsorted_vector.end(), rng);

    cout << "Unsorted vector: ";
    print_vec(unsorted_vector);
    cout << "\n";

    cout << "Applying quick sort..." << "\n";
    t1 = high_resolution_clock::now();
    my_sorting::quick_sort<int>(unsorted_vector, my_sorting::SORTING_ORDER::ASC, sort_cb_fun);
    t2 = high_resolution_clock::now();

    ms_int = duration_cast<milliseconds>(t2 - t1);

    cout << "Vector after quick sort[ execution time: "<< ms_int.count() <<" ms ]: ";
    print_vec(unsorted_vector);
    cout << "\n";

    return 0;
}
