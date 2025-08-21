#pragma once
#include <functional>
#include <iostream>

namespace my_sorting {

    enum class SORTING_ORDER {
        ASC,
        DESC,
    };

    template <typename T>
    void sel_sort(std::vector<T> &input_vector, SORTING_ORDER order, std::function<bool(const T&,const T&, const SORTING_ORDER sort_ord)> compare_cb);

    template <typename T>
    void bubble_sort(std::vector<T> &input_vector, SORTING_ORDER order, std::function<bool(const T&,const T&, const SORTING_ORDER sort_ord)> compare_cb);

    template <typename T>
    void ins_sort(std::vector<T> &input_vector, SORTING_ORDER order, std::function<bool(const T&,const T&, const SORTING_ORDER sort_ord)> compare_cb);

    template <typename T>
    void merge_sort(std::vector<T> &input_vector, SORTING_ORDER order, std::function<bool(const T&,const T&, const SORTING_ORDER sort_ord)> compare_cb);

}

#include "sorting.tpp"