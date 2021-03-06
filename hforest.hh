/*
 * HForest: a class to represent a collection of HTrees, each with an
 * associated priority (lower value is higher priority)
 */

#pragma once

#include <memory>
#include <vector>

#include "htree.hh"

class HForest {
public:
	using tree_t = HTree::tree_ptr_t;

	// Initialize with no trees:
	HForest() : isHeap(false) {};
	~HForest() = default;

	// Return the number of trees in the forest:
	size_t size() const { return trees_.size(); }

	// Add a single tree to the forest:
	void add_tree(tree_t);

	// Return the tree with the highest priority (and remove it from forest)
	tree_t pop_bottom();

private:
	std::vector<tree_t> trees_;
	bool isHeap;
};
