// build.cpp
// James R Von Holle
// source for bridge algorithm
// 29 Sept 2017

#include "build.h"
#include <algorithm>

#include <iostream>

bool crosses(Bridge left, Bridge right) { return ((left[0] <= right[0] && left[1] >= right[1]) || (left[0] >= right[0] && left[1] <= right[1])); }

void printMatrix(std::vector<std::vector<int> > mat) {
    for(size_t i = 0; i < mat.size(); ++ i) {
        for(size_t j = 0; j < mat[i].size(); ++j) {
            if(mat[i][j] < 10)
                std::cout << 0;
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------------------" << std::endl;
}

inline std::vector< std::vector<int> > makeBridgeMatrix(const std::vector<Bridge> & bridges, const int & e) {
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
    int max = 0;
    
    for(int i = 0; i < e; ++i) {
        for(int j = 0; j < e; ++j) {
            if(i > 0 && j > 0)
                bridgeMat[i][j] = std::max({(bridgeMat[i][j]+bridgeMat[i-1][j-1]), bridgeMat[i][j-1], bridgeMat[i-1][j]});
            max = std::max(max, bridgeMat[i][j]);
        }
    }
    
    return max;
}

// Top Down
// details on parameters in header
// int build(int w, int e, const std::vector<Bridge> & bridges) { 
//     if(e <= 2) return handleTiny(bridges);
    
    
    
//     return 0;
// }