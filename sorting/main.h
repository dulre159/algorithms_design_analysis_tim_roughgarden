#pragma once

#include "../commons/vector_utils.h"
#include <functional>
#include <iostream>

enum SORTING_ORDER {
    ASC,
    DESC,
};

// Selection sort
// For each element A compare it with all the others B
// If the element A is bigger than (or lower than) B then swap them
void sel_sort(std::vector<int> &input_vector, SORTING_ORDER order);

// Bubble sort
// Compare each element A with the next one B
// Swap A with B if necessary
// Reiterate until no swaps are necessary (vector is sorted)
void bubble_sort(std::vector<int> &input_vector, SORTING_ORDER order);

// Insertion sort
// Start from element n = 1
// Compare element n to element n-1
// If element n is less then element n-1; move element n-1 to n+1 and place n into n-1
void ins_sort(std::vector<int> &input_vector, SORTING_ORDER order);

// Merge sort
// Divid the input array in half and recursevly call on both halfs
// Merge the output
// Merging is done using two pointers on each sorted half
// The output array is populated choosing the lower or higher value between the two pointed values
template <typename T>
void merge_sort(std::vector<T> &input_vector, SORTING_ORDER order, std::function<bool(const T&,const T&, const SORTING_ORDER sort_ord)> merge_compare_callback)
{

    if (!merge_compare_callback)
    {
        std::cout << "Merge comparison callback is needed\n";
        return;
    }

    unsigned int in_size = input_vector.size();

    if (in_size <= 1) return;

    // Divid vector in two parts
    std::vector<T> first_half, second_half;
    
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

    merge_sort(first_half, order, merge_compare_callback);
    merge_sort(second_half, order, merge_compare_callback);

    // Merge step
    int j = 0, l = 0;
    for (int i=0; i < in_size; i++) {

        if (j < first_half.size() && l < second_half.size())
        {
             if (order == SORTING_ORDER::ASC)
            {
                //if (first_half[j] < second_half[l])
                if (merge_compare_callback(first_half[j], second_half[l], order))
                {
                    input_vector[i] = first_half[j];
                    j++;
                } 
                else
                {
                    input_vector[i] = second_half[l];
                    l++;
                }
            }
            else
            {
                //if (first_half[j] > second_half[l])
                if (merge_compare_callback(first_half[j], second_half[l], order))
                {
                    input_vector[i] = first_half[j];
                    j++;
                } 
                else
                {
                    input_vector[i] = second_half[l];
                    l++;
                }
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