// huffcode.hpp  UNFINISHED
// Glenn G. Chappell
// 29 Nov 2015
//
// For CS 411/611 Fall 2015
// Assignment 6, Exercise A
// Header for class HuffCode
//
// Modified 11/22/17
// Chris Hartman
// For CS 411 Fall 2017
//
// Finished for submition Dec 1 2017
// James R Von Holle
// CS 411 HW 6

#ifndef FILE_HUFFCODE_H_INCLUDED
#define FILE_HUFFCODE_H_INCLUDED

#include <string>
#include <unordered_map>
#include <utility>
#include <queue>
#include <vector>

using pci = std::pair<char, int>;


// Class HuffCode
// Encoding & decoding using a Huffman code
class HuffCode {

// ***** HuffCode: ctors, dctor, op= *****
public:

    // Compiler-generated default ctor, copy ctor, copy =, dctor used

// ***** HuffCode: general public functions *****
public:

    void setWeights(const std::unordered_map<char, int> & theweights);

    std::string encode(const std::string & text) const;

    std::string decode(const std::string & codestr) const;
    
    int tree_size() { return treeHelp_.size(); }
    int tree_size() const { return treeHelp_.size(); }

// ***** HuffCode: data members *****
private:
    struct HuffTree {
    public:
        HuffTree(pci vals):here_(vals) {}
        
        HuffTree(const HuffTree & other):here_(other.here_), babies_(other.babies_) {}
        
        HuffTree(int zs, int os, HuffTree zero, HuffTree one):here_(std::make_pair('\?',zs+os)) {
            babies_.push_back(zero);
            babies_.push_back(one);
        }
        
        // return functions to get at guts
        int val() { return here_.second; }
        int val() const { return here_.second; }
        
        char cha() { return here_.first; }
        char cha() const { return here_.first; }
        
        // recursive encode function
        // takes the char to encode
        // returns the code for that character only
        std::string number_babies(const char & key, const std::string & codestr = "") const;
        
        // recursive decode function
        // takes a code as a string
        // returns a character and 
        // the position in the key where_ it was
        pci english_babies(const std::string & key, const size_t & pos) const;
        
        // makes creating the priorty_queue cleaner
        friend bool operator<(const HuffTree & lhs, const HuffTree & rhs) {
            return rhs.val() < lhs.val(); }
            
    private:
        pci here_;
        std::vector<HuffTree> babies_;
    }; // End Struct HuffTree
    
    std::priority_queue<HuffTree> treeHelp_;
};  // End class HuffCode


#endif //#ifndef FILE_HUFFCODE_H_INCLUDED

