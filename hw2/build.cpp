// build.cpp
// James R Von Holle
// source for bridge algorithm
// 29 Sept 2017

#include "build.h"

// see header for parameter detail
int build(int w, int e, const std::vector<Bridge> & bridges) {
    auto max_tol = 0;  // the maximum toll
    auto cur_tol = 0;  // the toll for the current set of bridges
    
    auto cur_set = bridges; // the current set of bridges
    bool cross = false;
    
    for(auto i : bridges) {
        cur_set.clear();       // clear working set of bridges
        cur_set.push_back(i);  // add current bridge from list to working set
        cur_tol = i[2];        // set current toll to toll of the new first bridge
        for(auto j : bridges) {
            if(i == j)
                continue;
                
            cross = false;
            for(auto k : cur_set)  // check if new bridge crosses any of the old bridges
                if( (j[0] <= k[0] && j[1] >= k[1]) || (j[0] >= k[0] && j[1] <= k[1]) )
                    cross = true;
                    
            if(!cross) {
                cur_set.push_back(j);  // if it doesn't cross, add it to the list and update the toll
                cur_tol += j[2];
            }
        }
        if(max_tol < cur_tol)
            max_tol = cur_tol;  // update the max tol
    }
    
    return max_tol; 
}