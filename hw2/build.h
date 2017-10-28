// build.h
// James R Von Holle
// header for bridge algorithm
// 29 Sept 2017

#ifndef BUILD_H_INCLUDED
#define BUILD_H_INCLUDED

#include <vector>
#include <cstddef>

using Bridge = std::vector<int>;

class bridge_tree {
    public:
        bridge_tree(const std::vector<Bridge> & bridges, const Bridge & first, const std::vector<Bridge> & set);
        
        int get_best();
        void print_tree();
        
    private:
        std::vector<bridge_tree> valid_next;
        std::vector<Bridge> so_far;
};

// build
//  takes two ints, w & e, which denote the number of "cities" on either side
//  takes a vector of Bridge (vector<int>), bridges, with all the possible bridges
//     **PRE-CONDITION:
//                     A bridge must be exactly 3 ints
//                         The first denotes the left city
//                         The second denotes the right city
//                         The third denotes the toll for that bridge
//  returns the maximum possible toll with the given bridges
int build(int w, int e, const std::vector<Bridge> & bridges);

#endif