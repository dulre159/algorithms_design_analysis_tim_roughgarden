#pragma once

#include "../commons/vector_utils.h"

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
void merge_sort(std::vector<int> &input_vector, SORTING_ORDER order);