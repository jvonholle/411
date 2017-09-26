// build.cpp
// James R Von Holle
// source for bridge algorithm
// 29 Sept 2017

#include "build.h"
#include <utility> // for std::pair and std::make_pair
#include <cstddef>

int build(int w, int e, const std::vector<Bridge> & bridges) {
    auto max_tol = 0;
    auto cur_tol = 0;
    
    auto cur_set = bridges;
    cur_set.clear();
    bool cross = false;
    
    for(auto i : bridges) {
        cur_set.clear();
        cur_set.push_back(i);
        cur_tol = i[2];
        for(auto j : bridges) {
            if(i == j)
                continue;
                
            cross = false;
            for(auto k : cur_set) 
                if( (j[0] <= k[0] && j[1] >= k[1]) || (j[0] >= k[0] && j[1] <= k[1]) )
                    cross = true;
                    
            if(!cross) {
                cur_set.push_back(j);
                cur_tol += j[2];
            }
        }
        if(max_tol < cur_tol)
            max_tol = cur_tol;
    }
    
    return max_tol; 
}