// huffcode.cpp  UNFINISHED
// Glenn G. Chappell
// 29 Nov 2015
//
// For CS 411/611 Fall 2015
// Assignment 6, Exercise A
// Source for class HuffCode
//
// Modified 11/22/17
// Chris Hartman
// For CS 411 Fall 2017
//
// Finished for submition Dec 1 2017
// James R Von Holle
// CS 411 HW 6

#include "huffcode.hpp"  // for class HuffCode declaration
#include <vector>

#include <iostream>

// number_babies
// recurisive encode function
// further description in header
std::string HuffCode::HuffTree::number_babies(const char & key, const std::string & codestr) const {
    if(this-> cha() == key)
        return codestr;
    else if(babies_.empty())
        return "";
        
     return babies_[0].number_babies(key, codestr+"0") +
                babies_[1].number_babies(key, codestr+"1");
}

// english_babies
// recurisive decode function
// further description in header
pci HuffCode::HuffTree::english_babies(const std::string & key, const size_t & pos) const {
    if(pos >= key.size())
        return std::make_pair(this->cha(), -1);
    if(babies_.empty())
        return std::make_pair(this->cha(), pos);
        
    if(key[pos] == '0')
        return babies_[0].english_babies(key, pos+1);
    return babies_[1].english_babies(key, pos+1);
}

// setWeights
// makes Huffman code tree based on given weights
// stores as priorty queue member variable
void HuffCode::setWeights(const std::unordered_map<char, int> & theweights) {
    for(auto i : theweights)
        this->treeHelp_.push(HuffTree(i));
        
    while(true) {
        if(tree_size() <= 1)
            break;
        HuffTree temp0(treeHelp_.top());
       this->treeHelp_.pop();
        
        HuffTree temp1(treeHelp_.top());
       this->treeHelp_.pop();
        
       this->treeHelp_.push(HuffTree(temp0.val(), temp1.val(), temp0, temp1));
    }
}

// encode
// calls number_babies the right way
std::string HuffCode::encode(const std::string & text) const {
    if(treeHelp_.empty())
        return "";
        
    std::string ret = "";
    
    for(size_t i = 0; i < text.size(); ++i)
        ret += treeHelp_.top().number_babies(text[i]);
        
    return ret;
}

// decode
// calls english_babies the right way
std::string HuffCode::decode(const std::string & codestr) const {
    if(treeHelp_.empty())
        return "";
        
    std::string ret = "";
    pci rvals = std::make_pair('\?', 0);
    
    while(rvals.second >= 0) {
        rvals = treeHelp_.top().english_babies(codestr, rvals.second);
        if(rvals.first != '\?')
            ret += rvals.first;
    }
        
    return ret;
}

