// contigsum.hpp
// James Von Holle
// CS 411
// Oct 13 2017

#ifndef CONTIGSUM_HPP_INCLDUED
#define CONTIGSUM_HPP_INCLDUED

#include <algorithm>
#include <vector>

template<typename RAIter>
std::vector<int> get_contigSum(RAIter first, RAIter last) {
    if(last - first <= 0)
        return {0};
    std::vector<int> Rvec = {0,0,0,0}; // [0] = a
                                       // [1] = b
                                       // [2] = c
                                       // [3] = d
    
    // BASE CASE
    if(last - first <= 2) {
        if(last - first == 1) {
            Rvec[3] = *first;
            if(*first > 0) {
                Rvec[0] = *first; Rvec[1] = *first; Rvec[2] = *first; 
            }
            return Rvec;
        }
        
        Rvec[3] = *first + *(last-1);
        if(*first > Rvec[3]) 
            Rvec[1] = *first;
        if(*(last-1) > Rvec[3]) 
            Rvec[2] = *(last-1);
        Rvec[0] = std::max({Rvec[1], Rvec[2], Rvec[3]});
        
        for(int i = 0; i < 3; ++i)
            if(Rvec[i] < 0)
                Rvec[i] = 0;
        return Rvec;
    } 
    // END BASE CASE
    
    std::vector<int> left  {0,0,0,0};
    std::vector<int> right {0,0,0,0};
    
    auto mid = (last - first) /2;
    left  = get_contigSum(first, last-mid);
    right = get_contigSum(last-mid, last);
    
    Rvec[3] = left[3] + right[3];
    Rvec[1] = std::max({left[1], left[3] + right[1],  Rvec[3]});  // max { left.b, left.d + right.b, Rvec.d }
    Rvec[2] = std::max({right[2], right[3] + left[2], Rvec[3]}); // max { right.c, right.d + left.c, Rvec.d }
    Rvec[0] = std::max({left[0], right[0], left[2] + right[1], Rvec[3], Rvec[1], Rvec[2]});
    
    return Rvec;
}

template<typename RAIter>
int contigSum(RAIter first, RAIter last) {
    auto ret = get_contigSum(first, last);
    return ret[0];
}

#endif