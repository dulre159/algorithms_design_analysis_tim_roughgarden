#include "../commons/vector_utils.h"
#include "../commons/commons.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <random>
#include <algorithm>

using std::cout;
using std::vector;

/* 
    Brute-force inversions counter 
    With 2 indices over the vector we count the number of inversions
    Complexity O(n^2)
*/
void brute_inv_cnt(vector<int> &input_vector, unsigned int &tot_invs)
{
    for (auto it1 = input_vector.begin(); it1 != input_vector.end(); it1++) {
        for (auto it2 = it1; it2 != input_vector.end(); it2++) {
            if (*it1 > *it2) {
                tot_invs += 1;
            }
        }   
    }
}


/*
    Recursive inversions counter
    "Divide and conquer" approach
    There are three types of inversions: left, right and split
    Counting split inversions is done using the merge step of the merge sort algorithm
    The split inversions of the second/right half are the right inversions
    In particular during the merge step each time an element 'er' from the right half(second half)
    is to be inserted into the merged vector, the remaining number of elements in the left vector(first half) are the inversions for 'er';
    Complexity O(nlogn)
*/
void recursive_inv_cnt(vector<int> &input_vector, unsigned int &tot_invs)
{
    unsigned int in_size = input_vector.size();

    if (in_size == 1) return;

    // Divid vector in two parts
    vector<int> first_half (in_size/2), second_half (in_size - in_size/2);

    std::copy_n(input_vector.cbegin(), in_size/2, first_half.begin());
    std::copy(input_vector.cbegin()+(in_size/2), input_vector.cend(), second_half.begin());

    recursive_inv_cnt(first_half, tot_invs);
    recursive_inv_cnt(second_half, tot_invs);

    // Merge and inversion count step
    size_t j = 0, l = 0;
    std::for_each(input_vector.begin(), input_vector.end(), [&j, &l, &first_half, &second_half, &tot_invs](auto &e){
        if (j < first_half.size() && l < second_half.size())
        {
                // We count split inversions here
                if (first_half[j] <= second_half[l])
                {
                    e = first_half[j];
                    j++;
                } 
                else
                {
                    e = second_half[l];
                    l++;
                    tot_invs += first_half.size() - j;
                }
        }
        else
        {
            if (j < first_half.size()) {
                e = first_half[j];
                j++;
            }

            if (l < second_half.size()) {
                e = second_half[l];
                l++;
            }
        }
    });

}
    
int main(/*int argc, char**argv*/)
{
    unsigned int inversions_counter = 0;
    int min = 0, max = 1000, num_ele = 10000;
    //vector<int> in_vec = {1, 3, 5, 2, 4, 6};
    //vector<int> in_vec = {6,5,4,3,2,1};
    vector<int> in_vec (num_ele);
    
    std::random_device rdev;
    std::mt19937 rng_alg(rdev());
    std::uniform_int_distribution dist(min, max);
    
    std::generate(in_vec.begin(), in_vec.end(), [&rng_alg, &dist](){
        return dist(rng_alg);
    });

    print_vec(in_vec, "Input Vector");

    cout << "Counting inversions with brute force method..." << "\n";
    {
        ExecutionTimerMs timer_("Brute-force Inversions Counter Function");
        brute_inv_cnt(in_vec, inversions_counter);
    }

    cout << "Total number of inversions found: " << inversions_counter << "\n";

    inversions_counter = 0;

    cout << "Recursively counting inversions..." << "\n";
    {
        ExecutionTimerMs timer_("Recursive Inversions Counter Function");
        recursive_inv_cnt(in_vec, inversions_counter);
    }

    cout << "Total number of inversions found: " << inversions_counter << "\n";

    return 0;
}
