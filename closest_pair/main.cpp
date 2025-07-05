#include "../commons/vector_utils.h"
#include "../sorting/main.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <chrono>

struct POINT_2D {
    double x;
    double y;
};

using std::cout;
using std::vector;
/* Stuff to measure execution time */
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

void print_point_2D(const POINT_2D &p, const char enc_char_start, const char enc_char_end, const char sep_char, const bool do_newline)
{
    cout << enc_char_start << p.x << sep_char << p.y << enc_char_end << (do_newline == true ? "\n" : "");
}

// Computes distance between two 2D points
double dist_points_2D(const POINT_2D &a,const POINT_2D &b)
{
    return sqrt(pow((b.x-a.x),2) + pow((b.y-a.y),2));
}

// Brute force algorithm to find the closest pair of 2D points
// Complexity O(N^2)
std::tuple<POINT_2D, POINT_2D> bf_cp_alg(vector<POINT_2D> &in_P2D_vec)
{
    int cp_idxi=-1,cp_idxj=-1;
    // There might be a better way then initializing the dist this way?
    double cur_min_dist = 9000000;
    std::tuple<POINT_2D, POINT_2D> cp_out;

    std::get<0>(cp_out) = POINT_2D{0,0};
    std::get<1>(cp_out) = POINT_2D{0,0};
    

    for (int i=0; i < in_P2D_vec.size(); i++)
    {
        for (int j=0; j < in_P2D_vec.size(); j++)
        {
            // Skip same points
            if (in_P2D_vec[i].x != in_P2D_vec[j].x && in_P2D_vec[i].y != in_P2D_vec[j].y)
            {  
                double dist = dist_points_2D(in_P2D_vec[i], in_P2D_vec[j]);
                if (dist < cur_min_dist)
                {
                    cur_min_dist = dist;
                    cp_idxi = i;
                    cp_idxj = j;
                }
            }
            
        }
    }

    if (cp_idxi != -1)
    {
        std::get<0>(cp_out) = in_P2D_vec[cp_idxi];
    }
    if (cp_idxj != -1)
    {
        std::get<1>(cp_out) = in_P2D_vec[cp_idxj];
    }

    // In case no pair is found the pair [0,0] is returned
    return cp_out;
}

int main(int argc, char**argv)
{
    vector<POINT_2D> in_2D_vec;
    vector<int> in_x_vec;
    vector<int> in_y_vec;
    init_vec(in_x_vec, 10, -10, 10);
    init_vec(in_y_vec, 10, -10, 10);

    for (int i=0; i < 10; i++)
    {
        POINT_2D tmp_pt2d;
        tmp_pt2d.x = in_x_vec[i];
        tmp_pt2d.y = in_y_vec[i];
        in_2D_vec.push_back(tmp_pt2d);
    }

    std::tuple<POINT_2D, POINT_2D> bf_cp = bf_cp_alg(in_2D_vec);

    cout << "Closest pair is: { ";
    print_point_2D(std::get<0>(bf_cp), '[', ']', ',', false);
    cout << " , ";
    print_point_2D(std::get<1>(bf_cp), '[', ']', ',', false);
    cout << " }\n";

    return 0;
}