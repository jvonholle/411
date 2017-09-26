// build.h
// James R Von Holle
// header for bridge algorithm
// 29 Sept 2017

#ifndef BUILD_H_INCLDUED
#define BUILD_H_INCLUDED

#include <vector>
#include <cstddef>

using Bridge = std::vector<int>;

int build(int w, int e, const std::vector<Bridge> & bridges);

#endif