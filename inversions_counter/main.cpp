#include "../commons/vector_utils.h"
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

/* 
    Brute-force inversions counter 
    With 2 indices over the vector we count the number of inversions
*/
void brute_inv_cnt(vector<int> &input_vector, unsigned int &tot_invs)
{
    unsigned int inv_s = input_vector.size();

    for (int i = 0; i < inv_s; i++)
    {
        for (int j = i; j < inv_s; j++)
        {
            if (input_vector[i] > input_vector[j]) {
                tot_invs += 1;
            }
        }
    }
}


/*
    Recursive inversions counter
    "Divide and conquer" approach application
    There are three types of inversions: left, right and split
    Counting split inversions is done using the merge steps of the merge sort algorithm
    The split inversions of the second right half are the right inversions
    In particular during the merge step each time an element 'er' from the right half(second half)
    is to be inserted into the merged vector, the remaining number of elements in the left vector(first half) are the inversions for 'er';
*/
void recursive_inv_cnt(vector<int> &input_vector, unsigned int &tot_invs)
{
    unsigned int in_size = input_vector.size();

    if (in_size == 1) return;

    // Divid vector in two parts
    vector<int> first_half, second_half;
    
    for (int i = 0; i < in_size; i++)
    {
        if (i < in_size/2)
        {
            first_half.push_back(input_vector[i]);
        }
        else
        {
            second_half.push_back(input_vector[i]);
        } 
    }

    recursive_inv_cnt(first_half, tot_invs);
    recursive_inv_cnt(second_half, tot_invs);

    // Merge and inversion count step
    int j = 0, l = 0;
    for (int i=0; i < in_size; i++) {

        if (j < first_half.size() && l < second_half.size())
        {
                // We count split inversions here
                if (first_half[j] <= second_half[l])
                {
                    input_vector[i] = first_half[j];
                    j++;
                } 
                else
                {
                    input_vector[i] = second_half[l];
                    l++;
                    tot_invs += first_half.size() - j;
                }
        }
        else
        {
            if (j < first_half.size()) {
                input_vector[i] = first_half[j];
                j++;
            }

            if (l < second_half.size()) {
                input_vector[i] = second_half[l];
                l++;
            }
        }
        
    }
}

int main(int argc, char**argv)
{
    //vector<int> in_vec = {1, 3, 5, 2, 4, 6};
    //vector<int> in_vec = {6,5,4,3,2,1};
    vector<int> in_vec;
    unsigned int inversions_counter = 0;
    init_vec(in_vec, 10000, 0, 1000);

    cout << "Vector: ";
    print_vec(in_vec);
    cout << "\n";

    cout << "Counting inversions with brute force method..." << "\n";

    auto t1 = high_resolution_clock::now();
    brute_inv_cnt(in_vec, inversions_counter);
    auto t2 = high_resolution_clock::now();
    
    milliseconds ms_int = duration_cast<milliseconds>(t2 - t1);
    cout << "Execution time(ms): " << ms_int.count() << "\n";

    cout << "Total number of inversions found: " << inversions_counter << "\n";

    inversions_counter = 0;

    cout << "Recursively counting inversions..." << "\n";
    t1 = high_resolution_clock::now();
    recursive_inv_cnt(in_vec, inversions_counter);
    t2 = high_resolution_clock::now();

    ms_int = duration_cast<milliseconds>(t2 - t1);
    cout << "Execution time(ms): " << ms_int.count() << "\n";

    cout << "Total number of inversions found: " << inversions_counter << "\n";

    return 0;
}
