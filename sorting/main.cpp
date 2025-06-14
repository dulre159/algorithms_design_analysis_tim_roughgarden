#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

enum SORTING_ORDER {
    ASC,
    DESC,
};

// Unsort the array
void unsort_vector(vector<int> &input_vector)
{
    unsigned int max_runs = input_vector.size();
    int swap_helper;

    srand(time(0));

    while(max_runs-- > 0) {
        // Generate a random number between 0 and input_vector.size()
        int randomNum1 = rand() % (input_vector.size()-1);
        // Generate a random number between 0 and input_vector.size()
        int randomNum2 = rand() % (input_vector.size()-1);

        // Swap number at position randomNum1 with randomNum2
        swap_helper = input_vector[randomNum1];
        input_vector[randomNum1] = input_vector[randomNum2];
        input_vector[randomNum2] = swap_helper;
    }
}

// Selection sort
// For each element A compare it with all the others B
// If the element A is bigger than (or lower than) B then swap them
void sel_sort(vector<int> &input_vector, SORTING_ORDER order)
{
    int swap_helper;
    for (int i = 0; i < input_vector.size(); i++)
    {
        for (int j = 0; j < input_vector.size(); j++)
        {
            if (order == SORTING_ORDER::DESC) {
                if (input_vector[j] < input_vector[i]) {
                    swap_helper = input_vector[i];
                    input_vector[i] = input_vector[j];
                    input_vector[j] = swap_helper;
                }
            } else
            {
                if (input_vector[j] > input_vector[i]) {
                    swap_helper = input_vector[i];
                    input_vector[i] = input_vector[j];
                    input_vector[j] = swap_helper;
                }
            }
        }

    }
}


// Bubble sort
// Compare each element A with the next one B
// Swap A with B if necessary
// Reiterate until no swaps are necessary (vector is sorted)
void bubble_sort(vector<int> &input_vector, SORTING_ORDER order)
{
    bool did_swap = true;
    int swap_helper;
    int v_size = input_vector.size();
    while(did_swap==true) {

        did_swap = false;

        for (int i = 0; i < v_size-1; i++) 
        {
            if (order == SORTING_ORDER::DESC)
            {
                if (input_vector[i] < input_vector[i+1])
                {
                    swap_helper = input_vector[i];
                    input_vector[i] = input_vector[i+1];
                    input_vector[i+1] = swap_helper;
                    did_swap = true;
                }
            }
            else
            {
                if (input_vector[i] > input_vector[i+1])
                {
                    swap_helper = input_vector[i];
                    input_vector[i] = input_vector[i+1];
                    input_vector[i+1] = swap_helper;
                    did_swap = true;
                }
            }
        }
    }
}

// Insertion sort
// Start from element n = 1
// Compare element n to element n-1
// If element n is less then element n-1; move element n-1 to n+1 and place n into n-1
void ins_sort(vector<int> &input_vector, SORTING_ORDER order)
{
    int current_selection;
    for (int i = 1; i < input_vector.size(); i++)
    {
        current_selection = input_vector[i];
        
        for (int j = i-1; j >= 0; j--)
        {
            if (order == SORTING_ORDER::ASC)
            {
                if (current_selection < input_vector[j])
                {
                    input_vector[j+1] = input_vector[j];
                    input_vector[j] = current_selection;
                }
            }
            else
            {
                if (current_selection > input_vector[j])
                {
                    input_vector[j+1] = input_vector[j];
                    input_vector[j] = current_selection;
                }
            }

        }

    }
}

// Merge sort
// Divid the input array in half and recursevly call on both halfs
// Merge the output
// Merging is done using two pointers on each sorted half
// The output array is populated choosing the lower or higher value between the two pointed values
void merge_sort(vector<int> &input_vector, SORTING_ORDER order)
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

    merge_sort(first_half, order);
    merge_sort(second_half, order);

    // Merge step
    int j = 0, l = 0;
    for (int i=0; i < in_size; i++) {

        if (j < first_half.size() && l < second_half.size())
        {
             if (order == SORTING_ORDER::ASC)
            {
                if (first_half[j] < second_half[l])
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
                if (first_half[j] > second_half[l])
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

// Vector printing
void print_arr(vector<int> &input_vector)
{
    cout << "[ ";
    for (int i=0; i < input_vector.size(); i++) {
        cout << input_vector[i] << " ";
    }
    cout << "]";
}

// Init input vector
void init_vec(vector<int> &input_vector, unsigned int num_ele, int max, int min)
{
    srand(time(0));
    for (int i=0; i < num_ele; i++) {
        input_vector.push_back((rand() % max)+min);
    }
}

int main(int argc, char**argv)
{
    vector<int> unsorted_vector;

    init_vec(unsorted_vector, 1000, 1000, -1000);

    cout << "Unsorted vector: ";
    print_arr(unsorted_vector);
    cout << "\n";

    cout << "Applying selection sort..." << "\n";
    sel_sort(unsorted_vector, SORTING_ORDER::ASC);

    cout << "Vector after selection sort: ";
    print_arr(unsorted_vector);
    cout << "\n";

    cout << "Unsorting vector..." << "\n";
    unsort_vector(unsorted_vector);

    cout << "Unsorted vector: ";
    print_arr(unsorted_vector);
    cout << "\n";

    cout << "Applying insertion sort..." << "\n";
    ins_sort(unsorted_vector, SORTING_ORDER::ASC);

    cout << "Vector after insertion sort: ";
    print_arr(unsorted_vector);
    cout << "\n";

    cout << "Unsorting vector..." << "\n";
    unsort_vector(unsorted_vector);

    cout << "Unsorted vector: ";
    print_arr(unsorted_vector);
    cout << "\n";

    cout << "Applying bubble sort..." << "\n";
    bubble_sort(unsorted_vector, SORTING_ORDER::ASC);

    cout << "Vector after bubble sort: ";
    print_arr(unsorted_vector);
    cout << "\n";

    cout << "Unsorting vector..." << "\n";
    unsort_vector(unsorted_vector);

    cout << "Unsorted vector: ";
    print_arr(unsorted_vector);
    cout << "\n";

    cout << "Applying merge sort..." << "\n";
    merge_sort(unsorted_vector, SORTING_ORDER::ASC);

    cout << "Vector after merge sort: ";
    print_arr(unsorted_vector);
    cout << "\n";

    return 0;
}
