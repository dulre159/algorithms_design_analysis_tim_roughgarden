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

                if (((*(it1+1)) != (*it1)) && compare_cb(*(it1+1), *it1, order))
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


    // Quick sort
    // Choose a pivot element L randomly
    // Divid the input array in two parts P1 and P2
    // P1 contains the elements that are less then L and P2 contains the elements that are greater then L
    // Recurse on P1 and P2
    // Avrage running time of O(nlogn)
    // Not better then merge sort if the input has many repeated elements
    template <typename T>
    void quick_sort(std::vector<T> &input_vector, SORTING_ORDER order, std::function<bool(const T&,const T&, const SORTING_ORDER sort_ord)> compare_cb)
    {

        if (!compare_cb)
        {
            std::cout << "Comparison callback is needed\n";
            return;
        }

        std::mt19937 rndg_alg{std::random_device{}()};

        auto select_pivot = [&rndg_alg](auto it_begin, auto it_end){
            // Pivot selection is random; the hope is to get half of the time a reasonable split
            int d = std::distance(it_begin, it_end);
            std::uniform_int_distribution rnd_idis(0, d-1);
            int rnd_n = rnd_idis(rndg_alg);
            // std::cout << "d: " << d << " rn*d_n: "<< rnd_n << std::endl;
            return it_begin+rnd_n;
        };

        auto partition_around_pivot = [](auto pivot_it, auto it_begin, auto it_end, SORTING_ORDER order, auto& compare_cb){
            
            auto pivot_val = *pivot_it;
            std::iter_swap(it_begin, pivot_it);
            auto split_point = it_begin+1;

            // std::cout << "[ ";
            // for(auto it1 = it_begin; it1 != it_end; it1++) std::cout << *it1 << " ";
            // std::cout << "]" << std::endl;

            for (auto it=it_begin+1; it != it_end; it++)
            {   
                if (compare_cb(*it, pivot_val, order))
                {
                    std::iter_swap(split_point, it);
                    split_point++;

                    // std::cout << "[ ";
                    // for(auto it1 = it_begin; it1 != it_end; it1++) std::cout << *it1 << " ";
                    // std::cout << "]" << std::endl;
                }
            }
            std::iter_swap(split_point-1, it_begin);

            // std::cout << "[ ";
            // for(auto it = it_begin; it != it_end; it++) std::cout << *it << " ";
            // std::cout << "]" << std::endl;

            return split_point-1;
        };

        auto rec_part = [](const auto& self, const auto& part_fun, const auto& sel_pivot_fun, auto it_begin, auto it_end, SORTING_ORDER order, auto& compare_cb) {
            auto in_size = std::distance(it_begin, it_end);
            
            if (in_size <= 1) return;
            
            // std::cout << "[ ";
            // for(auto it = it_begin; it != it_end; it++) std::cout << *it << " ";
            // std::cout << "]" << std::endl;

            auto pivot_it = sel_pivot_fun(it_begin, it_end);

            // std::cout << "Selected pivot " << *pivot_it << std::endl;

            auto split_point = part_fun(pivot_it, it_begin, it_end, order, compare_cb);

            self(self, part_fun, sel_pivot_fun, it_begin, split_point, order, compare_cb);
            self(self, part_fun, sel_pivot_fun, split_point+1, it_end, order, compare_cb);
        };

        rec_part(rec_part, partition_around_pivot, select_pivot, input_vector.begin(), input_vector.end(), order, compare_cb);
    }
}