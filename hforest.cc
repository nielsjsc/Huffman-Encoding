/*
 * HForest: a class to represent a collection of HTrees, each with an
 * associated value (inverse priority).
 * Implemented using the STL's make_heap.
 */

#include <algorithm>
#include "hforest.hh"

 //////////////////////////////////////////////////////////////////////////////
 // Comparator function for std::*_heap
static bool
compare_trees(HForest::tree_t t1, HForest::tree_t t2)
{
    return t1->get_value() > t2->get_value();//switched the sign, so the heap is now ordered from least to greatest value for faster popping.
}

//////////////////////////////////////////////////////////////////////////////
// Add a single tree to the forest:
void
HForest::add_tree(tree_t tree)
{
    isHeap = false;
    trees_.push_back(tree);
    std::push_heap(trees_.begin(), trees_.end(), compare_trees);
}

//////////////////////////////////////////////////////////////////////////////
// Return the tree with the highest frequency count (and remove it from forest)
HForest::tree_t
HForest::pop_bottom()
{
    if (trees_.empty()) {
        return nullptr;
    }


    std::pop_heap(trees_.begin(), trees_.end(), compare_trees);
    tree_t low_val = trees_.back();
    trees_.pop_back();
    return low_val;
    
}

