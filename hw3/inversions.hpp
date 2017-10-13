// inversions.hpp
// James R Von Holle
// CS 411
// HW3 
// Oct 13, 2017

#ifndef INVERSIONS_HPP_INCLUDED
#define INVERSIONS_HPP_INCLUDED

#include <cstddef>     // for std::size_t
#include <vector>      // for std::vector
#include <algorithm>   // for std::copy
#include <iterator>    // for std::distance
#include <type_traits> // for std::remove_reference

#include <iostream>

// mergEm
// This is mostly just lifted from Dr. Chappell's CS 411 Fall 2015 Repo, so I'll paste his comments below
// Merge two halves of a sequence, each sorted, into a single sorted
// sequence in the same location. Merge is done in a stable manner.
// Requirements on Types:
//     FDIter is a forward iterator type.
//     The value type of FDIter has default ctor, dctor, copy=,
//      operator<.
//     operator< is a total order on the value type of FDIter.
// Pre:
//     [first, middle) and [middle, last) are valid ranges, each sorted
//      by <.
// Post: 
//     [first, last) contains the same items as it did initially, but
//      now sorted by < (in a stable manner). 
//     returns number of items skipped in the first half of the list
template<typename FDIter>
std::size_t mergeEm(FDIter first, FDIter middle, FDIter last) {
    // vector of whatever the iteraters are
    // some good c++isms here
    std::vector< typename std::remove_reference<decltype(*first)>::type > buffer(std::distance(first, last));
    FDIter in1 = first;
    FDIter in2 = middle;
    // our output buffer iterator
    auto out = buffer.begin();
    std::size_t ret = 0;
    
    while(in1 != middle && in2 != last) {
        if(*in2 < *in1) {
            *out++ = *in2++;
            ret += std::distance(in1, middle); // if we move something, add how many things we jumped over
        } else 
            *out++ = *in1++;
    }
    copy(in1, middle, out);
    copy(in2, last, out);
    copy(buffer.begin(), buffer.end(), first);
    return ( ret );
}



// mergeStart
// This is also mostly lifted from Dr. Chappell's CS 411 Fall 2015 Repo
// Sorts a sequence, using iterative variant of Merge Sort. 
// Requirements on Types: 
//     RAIter is a random-access iterator type. 
//     The value type of RAIter has default ctor, dctor, copy=, 
//      operator<. 
//     operator< is a total order on the value type of RAIter. 
// Pre: 
//     [first, last) is a valid range. 
// Post: 
//     [first, last) contains the same items as it did initially, 
//      but now sorted by < (in a stable manner). 
// NOTE. We could make this iterative version of Merge Sort work with 
// forward iterators, but it would be messy. 
template<typename RAIter>
std::size_t mergeStart(RAIter first, RAIter last) {
    std::size_t size = last - first;
    std::size_t ic = 0;
    
    std::size_t partsize = 1; 
    while (partsize < size) {
        RAIter lo = first; 
        while(lo + partsize < last) {
            RAIter hi = lo + partsize * 2;
            if(last < hi)
                hi = last;
                
            ic += mergeEm(lo, lo + partsize, hi); // add up how much stuff got jumped over
            
            lo = hi;
        }
        partsize *= 2;
    }
    return ic;
}

template<typename RAIter>
std::size_t inversions(RAIter first, RAIter last) { return mergeStart(first, last); }

#endif