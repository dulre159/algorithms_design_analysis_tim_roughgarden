#pragma once

namespace my_sorting {

    // Selection sort
    // For each element A compare it with all the others B
    // If the element A is bigger than (or lower than) B then swap them
    template <typename T>
    void sel_sort(std::vector<T> &input_vector, SORTING_ORDER order, std::function<bool(const T&,const T&, const SORTING_ORDER sort_ord)> compare_cb)
    {
        if (!compare_cb)
        {
            std::cout << "Comparison callback is needed\n";
            return;
        }

        T swap_helper;
        for (int i = 0; i < input_vector.size(); i++)
        {
            for (int j = 0; j < input_vector.size(); j++)
            {
                if (compare_cb(input_vector[i], input_vector[j], order))
                {
                    swap_helper = input_vector[i];
                    input_vector[i] = input_vector[j];
                    input_vector[j] = swap_helper;
                    
                } 
            }

        }
    }

    // Bubble sort
    // Compare each element A with the next one B
    // Swap A with B if necessary
    // Reiterate until no swaps are necessary (vector is sorted)
    template <typename T>
    void bubble_sort(std::vector<T> &input_vector, SORTING_ORDER order, std::function<bool(const T&,const T&, const SORTING_ORDER sort_ord)> compare_cb)
    {
        if (!compare_cb)
        {
            std::cout << "Comparison callback is needed\n";
            return;
        }

        bool did_swap = true;
        T swap_helper;
        int v_size = input_vector.size();
        while(did_swap==true) {

            did_swap = false;

            for (int i = 0; i < v_size-1; i++) 
            {
                if (compare_cb(input_vector[i+1], input_vector[i], order))
                {
                    swap_helper = input_vector[i];
                    input_vector[i] = input_vector[i+1];
                    input_vector[i+1] = swap_helper;
                    did_swap = true;
                }
            }
        }
    }

    // Insertion sort
    // Start from element i = 1
    // Compare element i to element j = i-1
    // If element i is less then element j; move element j to j+1 and place i into j
    template <typename T>
    void ins_sort(std::vector<T> &input_vector, SORTING_ORDER order, std::function<bool(const T&,const T&, const SORTING_ORDER sort_ord)> compare_cb)
    {
        if (!compare_cb)
        {
            std::cout << "Comparison callback is needed\n";
            return;
        }

        T current_selection;
        for (int i = 1; i < input_vector.size(); i++)
        {
            current_selection = input_vector[i];
            
            for (int j = i-1; j >= 0; j--)
            {
                if (compare_cb(current_selection, input_vector[j], order))
                {
                    input_vector[j+1] = input_vector[j];
                    input_vector[j] = current_selection;
                }

            }

        }
    }

    // Merge sort
    // Divid the input array in half and recursevly call on both halfs
    // Merge the output
    // Merging is done using two pointers on each sorted half
    // The output array is populated choosing the lower or higher value between the two pointed values
    // Complexity O(nlogn)
    template <typename T>
    void merge_sort(std::vector<T> &input_vector, SORTING_ORDER order, std::function<bool(const T&,const T&, const SORTING_ORDER sort_ord)> compare_cb)
    {

        if (!compare_cb)
        {
            std::cout << "Comparison callback is needed\n";
            return;
        }

        unsigned int in_size = input_vector.size();

        if (in_size <= 1) return;

        // Divid vector in two parts
        std::vector<T> first_half (in_size/2), second_half (in_size - in_size/2);

        std::copy_n(input_vector.cbegin(), in_size/2, first_half.begin());
        std::copy(input_vector.cbegin()+(in_size/2), input_vector.cend(), second_half.begin());

        merge_sort(first_half, order, compare_cb);
        merge_sort(second_half, order, compare_cb);

        // Merge step
        int j = 0, l = 0;
        for (int i=0; i < in_size; i++) {

            if (j < first_half.size() && l < second_half.size())
            {
                if (compare_cb(first_half[j], second_half[l], order))
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
                // Copy remaining elements as they are
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
}