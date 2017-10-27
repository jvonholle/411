// build.cpp
// James R Von Holle
// source for bridge algorithm
// 29 Sept 2017

#include "build.h"
#include <algorithm>

#include <iostream>
// Improved Greedy method
// see header for parameter detail
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

bridge_tree::bridge_tree(const std::vector<Bridge> & bridges, const Bridge & first, const std::vector<Bridge> & set) { 
    if(bridges.size() <= 0)
        return;
        
    auto shrink_set = bridges;
    for(size_t i = 0; i < shrink_set.size()/2; ++i)
        std::swap(shrink_set[i], shrink_set[shrink_set.size()-(i+1)]);
        
    here = first;
    so_far = set;
    toll = here[2];
    
    for(auto k : so_far) 
        if( ((here[0] <= k[0] && here[1] >= k[1]) || (here[0] >= k[0] && here[1] <= k[1])) && (here != k))
            return;
    so_far.push_back(here);
    
    bool cross = false;
    for(size_t i = 0; i < bridges.size(); ++i) {
        if(bridges[i] == here)
            continue;
        
        for(auto k : so_far) {
            cross = false;
            if( ((bridges[i][0] <= k[0] && bridges[i][1] >= k[1]) || (bridges[i][0] >= k[0] && bridges[i][1] <= k[1])) && (bridges[i] != k))
                cross = true;
        }
               
        if(!cross) {
            shrink_set.pop_back();
            valid_next.push_back( bridge_tree(shrink_set, bridges[i], so_far));
        }
               
    }
    
}

void bridge_tree::print_tree() {
    int temp = 0;
    for(auto i : so_far) {
        std::cout << i[0] << " -> " << i[1] << " | ";
        temp+= i[2];
    }
    std::cout << "toll: " << temp << std::endl;
    
    // for(auto i : valid_next)
        // i.print_tree();
        
    std::cout << "------------------------------------------------" << std::endl;
}

int bridge_tree::get_best() {
    if(valid_next.size() <= 0) {
        int temp = 0;
        for(auto i : so_far)
            temp += i[2];
        return temp;
    }
    for(auto i : valid_next) {
        int temp = i.get_best();
        if(temp > toll)
            toll = temp;
    }
        
    std::sort(valid_next.begin(), valid_next.end(), [&](bridge_tree a, bridge_tree b){return a.toll < b.toll;});
    
    for(size_t i = 0; i < valid_next.size(); ++i) {
        std::cout << i << " : ";
        valid_next[i].print_tree();
    }
        std::cout << "++++++++++++++++++++" << std::endl;
    return toll;
    
    // for(auto i : valid_next)
    //     std::cout << i.toll << " ";
    // std::cout << std::endl;
    // std::cout << toll+valid_next[0].toll; 
    
    return 0;
}

// New exhaustive search version
// see header for parmeter detail
int build(int w, int e, const std::vector<Bridge> & bridges) {
    std::vector<int> tolls;
    
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
    for(auto i : bridges) {
        auto cur = bridge_tree(bridges, i, {});
        tolls.push_back(cur.get_best());
    }
    
    return *std::max_element(tolls.begin(), tolls.end());
}