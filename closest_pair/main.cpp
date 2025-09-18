#include "../commons/vector_utils.h"
#include "../sorting/sorting.h"
#include "../commons/commons.h"
#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>
#include <random>
#include <cmath>
#include <memory>
#include <map>
#include <unordered_set>
#include <functional>
#include <sstream>
#include <limits>

// The rappresention of a 2D point
struct POINT_2D {
    POINT_2D()
    {
        // Default point is the origin
        x = y = 0;
    }

    POINT_2D(const float& l_x, const float& l_y)
    {
        x = l_x;
        y = l_y;
    }

    POINT_2D(const POINT_2D& p2d)
    {
        x = p2d.x;
        y = p2d.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const POINT_2D& p2d)
    {
        os << "{" << p2d.x << "," << p2d.y << '}';
        return os;
    }

    bool operator==(const POINT_2D& b) const {
        return (x == b.x && y == b.y);
    }

    void operator=(const POINT_2D &b) {
        x = b.x;
        y = b.y;
    }

    int x;
    int y;
};

// Alias for a pair of 2d points
using PO2DPS = std::pair<POINT_2D, POINT_2D>;

// Custom hasher for set of POINT_2D
struct POINT_2D_HASHER {
    size_t operator()(const POINT_2D& p) const{
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};

// Custom hasher for set of pairs of POINT_2D
struct PAIR_OF_POINT_2D_HASHER {
    size_t operator()(const PO2DPS& p) const{

        // Sort the pair manually
        // Example for p1={(1,2), (-3,1)} and p2={(-3,1), (1,2)}
        // for p1 a=p1.second and b = p1.first
        // for p2 a=p1.first and b = p1.second
        
        // Example for p1={(1,2), (1,2)} and p2={(1,2), (1,2)}
        // for p1 a=p1.first and b = p1.second
        // for p2 a=p1.first and b = p1.second

        // Example for p1={(1,2), (2,1)} and p2={(2,1), (1,2)}
        // for p1 a=p1.first and b = p1.second
        // for p2 a=p1.second and b = p1.first

        // Example for p1={(1,2), (2,1)} and p2={(2,1), (1,2)}
        // for p1 a=p1.first and b = p1.second
        // for p2 a=p1.second and b = p1.first

        // Example for p1={(1,2), (-3,-1)} and p2={(-3,-1), (1,2)}
        // for p1 a=p1.second and b = p1.first
        // for p2 a=p1.first and b = p1.second


        const POINT_2D& a = (p.first.x < p.second.x || (p.first.x == p.second.x && p.first.y <= p.second.y)) ? p.first : p.second;
        const POINT_2D& b = (a == p.first) ? p.second : p.first;

        auto h1 = POINT_2D_HASHER{}(a);
        auto h2 = POINT_2D_HASHER{}(b);

        return h1 ^ (h2 << 1);
    }
};

// Compair two pairs of POINT_2D
bool cmpp_nord(const PO2DPS &a, const PO2DPS &b)
{
    if (a.first == b.first && a.second == b.second) return true;

    if (a.first == b.second && a.second == b.first) return true;

    return false;
}

// Equality functor
struct PAIR_OF_POINT_2D_EQUALITY {
    size_t operator()(const PO2DPS& a, const PO2DPS &b) const{
        if ((a.first == b.first && a.second == b.second) || (a.first == b.second && a.second == b.first)) return true;

        return false;
    }
};

using std::cout;
/* Stuff to measure execution time */
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

// Computes the euclidean distance between two 2D points
inline constexpr double euc_dist_p2d(const POINT_2D &a,const POINT_2D &b)
{
    return sqrt(pow((b.x-a.x),2) + pow((b.y-a.y),2));
}
inline double euc_dist_p2d(const PO2DPS &pp)
{
    return sqrt(pow((pp.second.x-pp.first.x),2) + pow((pp.second.y-pp.first.y),2));
}

/*
*   Closest pair algorithm : brute force search
*   Complexity O(n^2)
*/
auto bf_cp_alg(const vector<POINT_2D> &in_P2D_vec)
{
    auto out_closest_pairs = std::vector<PO2DPS>();

    if (in_P2D_vec.size() >= 2) {
    
        // There might be a better way then initializing the dist this way?
        double cur_min_dist = std::numeric_limits<double>::max();
        std::unordered_map<double, std::vector<PO2DPS>> map_dist_list_of_pairs;
        
        for (auto it1 = in_P2D_vec.begin(); it1 != in_P2D_vec.end(); it1++) {
            for (auto it2 = std::next(it1); it2 != in_P2D_vec.end(); it2++) {
                // Skip same points
                if (*it1 == *it2) continue;
                
                auto dist_ab = euc_dist_p2d(*it1, *it2);
                bool dieq = are_equal_d(dist_ab, cur_min_dist);
                bool dilt = is_less_than_d(dist_ab, cur_min_dist);

                if (dieq || dilt) {

                    if (dilt)
                        cur_min_dist = dist_ab;

                    if (map_dist_list_of_pairs.find(cur_min_dist) == map_dist_list_of_pairs.cend()) {
                        map_dist_list_of_pairs[cur_min_dist] = std::vector<PO2DPS>{};
                    }

                    map_dist_list_of_pairs[cur_min_dist].push_back(PO2DPS{*it1, *it2});
                }
            } 
        }

        if (map_dist_list_of_pairs.find(cur_min_dist) != map_dist_list_of_pairs.cend()) {
            out_closest_pairs.clear();
            out_closest_pairs.resize(map_dist_list_of_pairs[cur_min_dist].size());
            std::copy(map_dist_list_of_pairs[cur_min_dist].begin(), map_dist_list_of_pairs[cur_min_dist].end(), out_closest_pairs.begin());
        }
    }

    // Thanks to RVO out_closest_pairs should be build in the caller stack
    return out_closest_pairs;

}

/*  
*   Closest pair algorithm : divide and conquer approach
*   
*   Algorithm is divided in two parts: preprocessing and recursive
*   Preprocessing steps:
*   1) Make 2 copies p_x and p_y of the input vector
*   2) Sort the points in p_x by the x-coordinate
*   3) Sort the points in p_y by the y-coordinate
*   Recursive steps:
*   1) Divide p_x into q_x and q_y
*   2) Divide p_y into r_x and r_y
*   3) Recurse on (q_x,q_y) (left half); will return closest pair in left half (p1,q1)
*   4) Recurse on (r_x, r_y) (right half); will return closest pair in right half (p2,q2)
*   5) The closest pair can be in the left half (lucky case), the right half (lucky case) or splitted in both halfs (split pair; unlucky case)
*   6) Compute minimum distance dm between d(p1,q1) (distance of closest left pair) and d(p2, q2) (distance of closest right pair)
*   7) If the closest pair is a split pair (p3,q3) we invoke special function closest_split_pair(p_x, p_y, dm) to find it
*   8) In the unlucky case the running time of the overall algorithm depends on the running time of closest_split_pair(...)
*/
auto dc_cp_alg(const vector<POINT_2D> &in_P2D_vec)
{
    auto out_closest_pairs = std::vector<PO2DPS>();

    if (in_P2D_vec.size() < 2) return out_closest_pairs;   

    // Preprocessing
    vector<POINT_2D> p_x, p_y;
    for (const auto &p : in_P2D_vec)
    {
        p_x.push_back(POINT_2D(p));
        p_y.push_back(POINT_2D(p));
    }
    
    my_sorting::merge_sort<POINT_2D>(p_x, my_sorting::SORTING_ORDER::ASC, [](const POINT_2D& a, const POINT_2D& b, my_sorting::SORTING_ORDER sort_ord){
        if (sort_ord == my_sorting::SORTING_ORDER::ASC)
        {
            if (a.x < b.x) return true;
        }
        else
        {
            if (a.x > b.x) return true;
        }
        return false;
    });

    my_sorting::merge_sort<POINT_2D>(p_y, my_sorting::SORTING_ORDER::ASC, [](const POINT_2D& a, const POINT_2D& b, my_sorting::SORTING_ORDER sort_ord){
        if (sort_ord == my_sorting::SORTING_ORDER::ASC)
        {
            if (a.y < b.y) return true;
        }
        else
        {
            if (a.y > b.y) return true;
        }
        return false;
    });

    // Recursive part
    auto rec_part = [](const auto &self, const auto& find_split_pair,const auto &p_x,const auto &p_y) {
        // With 3 or 2 points we do brute force search
        if (p_x.size() <= 3)
        {
            return bf_cp_alg(p_x);
        }

        // Create left and right half
        std::vector<POINT_2D> q_x, r_x, q_y, r_y;
        std::unordered_set<POINT_2D, POINT_2D_HASHER> q_x_set;
        std::unordered_set<POINT_2D, POINT_2D_HASHER> r_x_set;
        size_t i=0;
        auto p_x_it = p_x.cbegin();
        
        while(p_x_it != p_x.cend())
        {

            if (i < p_x.size()/2) {
                q_x.push_back(POINT_2D(*p_x_it));
                q_x_set.insert(POINT_2D(*p_x_it));
            }
            else {
                r_x.push_back(POINT_2D(*p_x_it));
                r_x_set.insert(POINT_2D(*p_x_it));
            }

            p_x_it++;
            i++;
        }
        
        // Create q_y and r_y
        for (const auto& pt : p_y)
        {
            // Point *p_y_it is either in q_x or r_x
            if (q_x_set.count(pt)) {
                q_y.push_back(pt);
            } else {
                r_y.push_back(pt);
            }
        }

        // Recurse
        auto left_pairs = self(self, find_split_pair, q_x, q_y);
        auto right_pairs = self(self, find_split_pair, r_x, r_y);

        auto d1 = 0.0;
        auto d2 = 0.0;

        if (left_pairs.size() > 0)
        {
            d1 = euc_dist_p2d(*(left_pairs.begin()));
        }

        if (right_pairs.size() > 0)
        {
            d2 = euc_dist_p2d(*(right_pairs.begin()));
        }

        // If d1 or d2 can not be 0
        if (are_equal_d(d1,0.0)) d1 = d2 + 1.0;
        if (are_equal_d(d2,0.0)) d2 = d1 + 1.0;

        auto dm = std::min(d1, d2);

        // Find split pairs if needed
        auto split_pairs = find_split_pair(p_y, q_x, dm);

        if (split_pairs.size() > 0) {
            auto dsps = euc_dist_p2d(*(split_pairs.begin()));
            if (are_equal_d(dsps,d1)) {
                for (auto pp : left_pairs)
                {
                    split_pairs.push_back(pp);
                }
            }

            if (are_equal_d(dsps,d2)) {
                for (auto pp : right_pairs)
                {
                    split_pairs.push_back(pp);
                }
            }

            return split_pairs;
        }

        if (are_equal_d(d2,d1))
        {
            for (auto pp : left_pairs)
            {
                right_pairs.push_back(PO2DPS({POINT_2D(pp.first), POINT_2D(pp.second)}));
            }
        }

        if (is_less_than_d(d1,d2)) return left_pairs;

        return right_pairs;
    };


    auto find_split_pair = [](const auto &p_y,const auto &q_x, const auto& dm) {
        
        // Point having the biggest x-coordinate in the first half of P
        POINT_2D p_qx = *(--(q_x.end()));
        // s_y is the set of points with x-coordinate in the range [p_qx.x - dm, p_qx.x + dm]
        // s_y is sorted by y coordinates
        auto r_a = p_qx.x - dm;
        auto r_b = p_qx.x + dm;
        std::vector<POINT_2D> s_y;
        for (auto p : p_y) {
            if ((is_greater_than_f(p.x, r_a) || are_equal_f(p.x, r_a)) && (is_less_than_f(p.x, r_b) || are_equal_f(p.x, r_b))) s_y.push_back(POINT_2D(p));
        }

        size_t sy_size = s_y.size();

        auto cur_min_dist = dm;
        std::unordered_map<double, std::vector<PO2DPS>> map_dist_list_of_pairs;
        auto out_split_pairs = std::vector<PO2DPS>();

        for (size_t i=0; i < sy_size; i++) {
            for (size_t j=0; j < std::min((size_t)7, sy_size-i); j++)
            {
                if (s_y[i] == s_y[i+j]) continue;
                auto d_pij = euc_dist_p2d(s_y[i], s_y[i+j]);

                bool dieq = are_equal_d(d_pij, cur_min_dist);
                bool dilt = is_less_than_d(d_pij, cur_min_dist);

                if (dieq || dilt) {

                    if (dilt)
                        cur_min_dist = d_pij;

                    if (map_dist_list_of_pairs.find(cur_min_dist) == map_dist_list_of_pairs.end())
                    {
                        map_dist_list_of_pairs[cur_min_dist] = std::vector<PO2DPS>{};
                    }
                    map_dist_list_of_pairs[cur_min_dist].push_back(std::make_pair<POINT_2D,POINT_2D>(POINT_2D(s_y[i]), POINT_2D(s_y[i+j])));
                }
            }
        }

        if (map_dist_list_of_pairs.find(cur_min_dist) != map_dist_list_of_pairs.cend()) {
            out_split_pairs.clear();
            out_split_pairs.resize(map_dist_list_of_pairs[cur_min_dist].size());
            std::copy(map_dist_list_of_pairs[cur_min_dist].begin(), map_dist_list_of_pairs[cur_min_dist].end(), out_split_pairs.begin());
        }

        return out_split_pairs;
    };

    auto rec_part_res = rec_part(rec_part, find_split_pair, p_x, p_y);
    // The does use the hash of the item and the equality test to check if the item is already in the set 
    std::unordered_set<PO2DPS, PAIR_OF_POINT_2D_HASHER, PAIR_OF_POINT_2D_EQUALITY> cp_set;
    for (auto pp : rec_part_res)
    {
        cp_set.insert(std::make_pair<POINT_2D,POINT_2D>(POINT_2D(pp.first), POINT_2D(pp.second)));
    }

    for (auto pp : cp_set)
    {
        out_closest_pairs.push_back(std::make_pair<POINT_2D,POINT_2D>(POINT_2D(pp.first), POINT_2D(pp.second)));
    }

    return out_closest_pairs;
}

// Helper fuction used to print a vector of point pairs
void print_list_of_points_pairs(const std::vector<PO2DPS>& list_of_closest_pairs)
{
    if (list_of_closest_pairs.size() < 1) cout << "No closest pairs found" << std::endl;
    else {
        cout << "Closest pairs are: [ ";
        for (auto cpl_it = list_of_closest_pairs.begin(); cpl_it != list_of_closest_pairs.end(); cpl_it++)
        {
            cout << "<" << cpl_it->first << "," << cpl_it->second << ">"; 
            if ((cpl_it+1) == list_of_closest_pairs.end()) cout << " "; else cout << " , ";
        }
        cout << " ]" <<std::endl;
    }
}

int main(/*int argc, char**argv*/)
{
    size_t num_ele = 20000;
    int min_ele = -100, max_ele = 100;
    
    std::unordered_set<POINT_2D, POINT_2D_HASHER> in_2D_unoset;
    std::random_device rndev;
    std::mt19937 rng_alg (rndev());
    std::uniform_int_distribution dist(min_ele, max_ele);

    while (in_2D_unoset.size() < num_ele) {
        in_2D_unoset.insert(POINT_2D(dist(rng_alg), dist(rng_alg)));
    }

    auto in_2D_vec = std::vector<POINT_2D>(in_2D_unoset.begin(), in_2D_unoset.end());
    // auto in_2D_vec = std::vector<POINT_2D>({POINT_2D{-4,6}, POINT_2D{-4,-10}, POINT_2D{-3,-8}, 
    //                                         POINT_2D{10,3}, POINT_2D{3,4}, POINT_2D{5,10}, POINT_2D{8,2}, 
    //                                         POINT_2D{-3,6}, POINT_2D{5,-1}, POINT_2D{4,-5} });

    
    //auto in_2D_vec = std::vector<POINT_2D>{POINT_2D{-1,-10},POINT_2D{-3,-5},POINT_2D{-5,-8},POINT_2D{10,-3},POINT_2D{-6,5},POINT_2D{-2,-10},POINT_2D{-10,-4},POINT_2D{8,-10},POINT_2D{-5,5},POINT_2D{8,-9}};

    cout << "Generated 2D points : ";
    print_vec(in_2D_vec);
    cout << "\n";

    cout << "Applying bruteforce method..." << std::endl;
    auto t0 = high_resolution_clock::now();
    auto bf_cps_found = bf_cp_alg(in_2D_vec);
    auto t1 = high_resolution_clock::now();
    auto dt = duration_cast<milliseconds>(t1-t0);
    cout << "Execution took "<< dt.count() << " ms" << std::endl;
    //print_list_of_points_pairs(bf_cps_found);
    
    
    cout << "Applying divide and conquer method..." << std::endl;
    t0 = high_resolution_clock::now();
    auto rec_cps_found = dc_cp_alg(in_2D_vec);
    t1 = high_resolution_clock::now();
    dt = duration_cast<milliseconds>(t1-t0);
    cout << "Execution took "<< dt.count() << " ms" << std::endl;
    //print_list_of_points_pairs(rec_cps_found);

    return 0;
}