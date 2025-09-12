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
        
       for (auto it1 = input_vector.begin(); it1 != input_vector.end(); it1++) {
            for (auto it2 = input_vector.begin(); it2 != input_vector.end(); it2++) {
                if (compare_cb(*it1, *it2, order)) {
                    swap_helper = *it1;
                    *it1 = *it2;
                    *it2 = swap_helper;
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
        while(did_swap==true) {

            did_swap = false;

            for (auto it1 = input_vector.begin(); it1 != input_vector.end()-1; it1++) {

                if (compare_cb(*(it1+1), *it1, order))
                {
                    swap_helper = *it1;
                    *it1 = *(it1+1);
                    *(it1+1) = swap_helper;
                    did_swap = true;
                }
            }
        }
    }

    // Insertion sort
    // Start from element with index i = 1
    // Compare element with index i to element with index j = i-1
    // If element with index i is less then element with index j; move element with index j to index j+1 and place elment at index i into element with index j
    template <typename T>
    void ins_sort(std::vector<T> &input_vector, SORTING_ORDER order, std::function<bool(const T&,const T&, const SORTING_ORDER sort_ord)> compare_cb)
    {
        if (!compare_cb)
        {
            std::cout << "Comparison callback is needed\n";
            return;
        }

        T current_selection;
        for (auto it1 = input_vector.begin()+1; it1 != input_vector.end(); it1++)
        {
            current_selection = *it1;
            for (auto it2 = std::make_reverse_iterator(it1-1)-1; it2 != input_vector.rend(); it2++)
            {
                if (compare_cb(current_selection, *it2, order))
                {
                    *(it2-1) = *it2;
                    *it2 = current_selection;
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
        size_t j = 0, l = 0;
        std::for_each(input_vector.begin(), input_vector.end(), [&j, &l, &first_half, &second_half, &compare_cb, order](T& e) {

            if (j < first_half.size() && l < second_half.size())
            {
                if (compare_cb(first_half[j], second_half[l], order))
                {
                    e = first_half[j];
                    j++;
                } 
                else
                {
                    e = second_half[l];
                    l++;
                }   
            }
            else
            {
                // Copy remaining elements as they are
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
}