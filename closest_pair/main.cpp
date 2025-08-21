#include "../commons/vector_utils.h"
#include "../sorting/sorting.h"
#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>
#include <random>
#include <cmath>

struct POINT_2D {
    POINT_2D() = default;

    POINT_2D(const int& l_x, const int& l_y){
        x = l_x;
        y = l_y;
    }

    friend std::ostream& operator<<(std::ostream& os, const POINT_2D& p2d)
    {
        os << "{" << p2d.x << "," << p2d.y << '}';
        return os;
    }

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

// Computes the euclidean distance between two 2D points
inline constexpr auto dist_points_2D(const POINT_2D &a,const POINT_2D &b)
{
    return sqrt(pow((b.x-a.x),2) + pow((b.y-a.y),2));
}

// Brute force algorithm to find the closest pair of 2D points
// Complexity O(n^2)
auto bf_cp_alg(vector<POINT_2D> &in_P2D_vec)
{
    int cp_idxi=-1,cp_idxj=-1;
    // There might be a better way then initializing the dist this way?
    double cur_min_dist = 9000000;
    // In case no pair is found the pair [0,0] is returned
    auto cp_out = std::pair<POINT_2D,POINT_2D>({POINT_2D{0,0}, POINT_2D{0,0}});

    std::for_each(in_P2D_vec.cbegin(), in_P2D_vec.cend(), [&cp_out, &cur_min_dist, &in_P2D_vec](auto a){
        std::for_each(in_P2D_vec.cbegin(), in_P2D_vec.cend(), [&a, &cp_out, &cur_min_dist](auto b){
            // Skip same points
            if (a.x != b.x && a.y != b.y) {
                auto dist_ab = dist_points_2D(a, b);
                if (dist_ab < cur_min_dist) {
                    cur_min_dist = dist_ab;
                    std::get<0>(cp_out) = a;
                    std::get<1>(cp_out) = b;
                }
            }
        }); 
    });

    return cp_out;
}

int main(int argc, char**argv)
{
    auto num_ele = 10000, min_ele = -10, max_ele = 10;
    auto in_2D_vec = vector<POINT_2D>(num_ele, POINT_2D{0,0});

    std::random_device rndev;
    std::mt19937 rng_alg (rndev());
    std::uniform_int_distribution dist(min_ele, max_ele);

    std::generate(in_2D_vec.begin(), in_2D_vec.end(), [&rng_alg, &dist](){
        return POINT_2D(dist(rng_alg), dist(rng_alg));
    });

    cout << "Generated 2D points : ";
    print_vec(in_2D_vec);
    cout << "\n";

    cout << "Applying bruteforce method..." << std::endl;
    auto t0 = high_resolution_clock::now();
    auto bf_cp = bf_cp_alg(in_2D_vec);
    auto t1 = high_resolution_clock::now();
    auto dt = duration_cast<milliseconds>(t1-t0);
    cout << "Execution took "<< dt.count() << " ms" << std::endl;
    cout << "Closest pair is: [ " << std::get<0>(bf_cp) << " , " << std::get<1>(bf_cp) << " ]" <<std::endl;

    return 0;
}