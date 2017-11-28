// build.cpp
// James R Von Holle
// source for bridge algorithm
// 20 Nov 2017

#include "build.h"
#include <algorithm>

#include <iostream>
#include <chrono>

bool crosses(Bridge left, Bridge right) { return ((left[0] <= right[0] && left[1] >= right[1]) || (left[0] >= right[0] && left[1] <= right[1])); }

static inline std::vector< std::vector<int> > makeBridgeMatrix(const std::vector<Bridge> & bridges, const int & e) {
    std::vector< std::vector<int> > bridgeMat;
    std::vector<int> temp(e, 0);
    
    for(int i = 0; i < e; ++i)
        bridgeMat.push_back(temp);
        
    for(auto i : bridges)
        bridgeMat[i[0]][i[1]] = std::max(i[2],bridgeMat[i[0]][i[1]]);
        
    return bridgeMat;
}

inline int handleTiny(const std::vector<Bridge> & bridges) {
    if(bridges.size() <= 0) { return 0; }
    else if(bridges.size() == 1) { return bridges[0][2]; } 
    else if(bridges.size() == 2) {
        if( !crosses(bridges[0], bridges[1]) ) return bridges[0][2]+bridges[1][2];
        else return std::max(bridges[0][2], bridges[1][2]);
    }        
    return 0;
}

// Bottom Up 
// details on parameters in header
int build(int w, int e, const std::vector<Bridge> & bridges) { 
    if(e <= 2) return handleTiny(bridges);

    auto bridgeMat = makeBridgeMatrix(bridges, e); 

    for(int i = 1; i < e; ++i)
        for(int j = 1; j < e; ++j)
            bridgeMat[i][j] = std::max({(bridgeMat[i][j]+bridgeMat[i-1][j-1]), bridgeMat[i][j-1], bridgeMat[i-1][j]});


    return bridgeMat[w-1][e-1];
}

