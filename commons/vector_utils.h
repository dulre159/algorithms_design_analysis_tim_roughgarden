#pragma once

#include <vector>

/* Function to unsort the vector */
void unsort_vector(std::vector<int> &input_vector);

/* Vector pretty printing */ 
void print_vec(std::vector<int> &input_vector);

/* Initialize input vector with random num_ele numbers between min and max */
void init_vec(std::vector<int> &input_vector, unsigned int num_ele, int min, int max);