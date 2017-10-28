// build.cpp
// James R Von Holle
// source for bridge algorithm
// 29 Sept 2017

#include "build.h"
#include <algorithm>

#include <iostream>
// Improved Greedy method
// see header for parameter detail
// I left this in here for myself
// int build(int w, int e, const std::vector<Bridge> & bridges) {
//     auto max_tol = 0;  // the maximum toll
//     auto cur_tol = 0;  // the toll for the current set of bridges
    
//     std::vector<Bridge> cur_set; // the current set of bridges
//     auto work_set = bridges;
//     std::sort(work_set.begin(), work_set.end(), [&](Bridge a, Bridge b){return b[2]<a[2];});
//     bool cross = false;
    
//     for(auto i : work_set) {
//         cur_set.clear();       // clear working set of bridges
//         cur_set.push_back(i);  // add current bridge from list to working set
//         cur_tol = i[2];        // set current toll to toll of the new first bridge
//         for(auto j : work_set) {
//             if(i == j)
//                 continue;
                
//             cross = false;
//             for(auto k : cur_set)  // check if new bridge crosses any of the old bridges
//                 if( (j[0] <= k[0] && j[1] >= k[1]) || (j[0] >= k[0] && j[1] <= k[1]) )
//                     cross = true;
                    
//             if(!cross) {
//                 cur_set.push_back(j);  // if it doesn't cross, add it to the list and update the toll
//                 cur_tol += j[2];
//             }
//         }
//         if(max_tol < cur_tol)
//             max_tol = cur_tol;  // update the max toll
            
//     }
    
//     return max_tol; 
// }

// ctor
// description in header
bridge_tree::bridge_tree(const std::vector<Bridge> & bridges, const Bridge & first, const std::vector<Bridge> & set) { 
    if(bridges.size() <= 0)
        return;
        
    std::vector<Bridge> shrink_set;
    for(size_t i = 1; i <= bridges.size(); ++i)
        shrink_set.push_back(bridges[bridges.size()-i]);
        
    so_far = set;
    
    for(auto k : so_far) 
        if((first[0] <= k[0] && first[1] >= k[1]) || (first[0] >= k[0] && first[1] <= k[1])) 
            return;
    
    so_far.push_back(first);
    
    bool cross = false;
    for(size_t i = 0; i < bridges.size(); ++i) {
        if(bridges[i] == first)
            continue;
        
        for(auto k : so_far) {
            cross = false;
            if((bridges[i][0] <= k[0] && bridges[i][1] >= k[1]) || (bridges[i][0] >= k[0] && bridges[i][1] <= k[1]))
                cross = true;
        }
        
        if(cross) {
            shrink_set.pop_back();
            continue;
        } else {
            valid_next.push_back(bridge_tree(shrink_set, bridges[i], so_far));
            shrink_set.pop_back();
        }
               
    }
    
}

// description in header
void bridge_tree::print_tree() {
    int temp = 0;
    for(auto i : so_far) {
        std::cout << i[0] << " -> " << i[1] <<" | ";
        temp+= i[2];
    }
    std::cout << "toll: " << temp << std::endl
                << "kids: ";
    
    for(auto i : valid_next)
        i.print_tree();
    std::cout << "------------------------------------------------" << std::endl;
        
}

// description in header
int bridge_tree::get_best() {
    if(valid_next.size() <= 0) {
        int temp = 0;
        for(auto j : so_far)
            temp += j[2];
            
        return temp;
    }
    
    int toll = 0;
    for(auto i : valid_next) {
        int temp = i.get_best();
        if(temp > toll)
            toll = temp;
    }
    
    return toll;
}

// New exhaustive search version
// see header for parmeter detail
int build(int w, int e, const std::vector<Bridge> & bridges) {
    // anything with two or less bridges is easy enough to figure out without a tree
    if(bridges.size() <= 0) {
        return 0;
    } else if(bridges.size() == 1) {
        return bridges[0][2];
    } else if(bridges.size() == 2) {
        if( !((bridges[0][0] <= bridges[1][0] && bridges[0][1] >= bridges[1][1]) || (bridges[0][0] >= bridges[1][0] && bridges[0][1] <= bridges[1][1])) )
            return bridges[0][2]+bridges[1][2];
        else
            return std::max(bridges[0][2], bridges[1][2]);
    }        

    std::vector<int> tolls;
    // generate all of the best tolls for each bridge, add them to a list
    for(auto i : bridges) {
        auto cur = bridge_tree(bridges, i, {});
        tolls.push_back(cur.get_best());
    }
    
    // return the max toll
    return *std::max_element(tolls.begin(), tolls.end());
}
