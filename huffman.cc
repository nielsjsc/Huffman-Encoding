#include "huffman.hh"
#include <iostream>
#include <map>
#include "hforest.hh"
Huffman::Huffman(){}
Huffman::~Huffman(){}
HTree::tree_ptr_t Huffman::huffman_tree() { //creates a huffman tree given the frequency table
	HForest forest;
	for (int i = 0; i < 257; i++) {
		HTree::tree_ptr_t temp_tree = std::make_shared<HTree>(i, freq_table[i]); //creates a new tree given the frequency from the table, then adds it to the forest
		forest.add_tree(temp_tree);
	}
	int count = -1; //the index of the combined trees will be negative to avoid collision with ascii values
	while (forest.size()>1) {//breaks when there is 1 tree
		HTree::tree_ptr_t tree_1 = forest.pop_bottom();//pops the two lowest valued trees
		HTree::tree_ptr_t tree_2 = forest.pop_bottom();
		HTree::tree_ptr_t new_tree = std::make_shared<HTree>(count, tree_1->get_value() + tree_2->get_value(), tree_1, tree_2);//creates new tree with the popped trees as children, and combines their values
		forest.add_tree(new_tree);//adds the new tree to the existing forest
		count--;
	}
	HTree::tree_ptr_t tree_ptr = forest.pop_bottom();//pops the 1 tree from the forest, and returns it
	return tree_ptr;
}
Huffman::bits_t Huffman::encode(int symbol) {
	HTree::tree_ptr_t tree_ptr = huffman_tree();//calls and makes the complete tree
	HTree::possible_path_t path_ptr = tree_ptr->path_to(symbol);//gets the path to the character
	Huffman::bits_t path_bits;//using the bits_t member for storing the path
	for (auto i = path_ptr->begin(); i != path_ptr->end();i++ ) {//converting path to bits_t
		HTree::Direction dir = *i;
		switch (dir) {
		case HTree::Direction::LEFT:
			path_bits.push_back(0);
			break;
		case HTree::Direction::RIGHT:
			path_bits.push_back(1);
			break;
		}
	}
	freq_table[symbol] += 1;//updating the freq table with the new value
	return path_bits;
}
int Huffman::decode(bool bit) {
	if (decode_tree == nullptr)decode_tree=huffman_tree();//make a new tree if there isnt one already
	if (bit == 0)decode_tree = decode_tree->get_child(HTree::Direction::LEFT);//go left down tree if the current bit says so
	if (bit == 1)decode_tree = decode_tree->get_child(HTree::Direction::RIGHT);//same for right
	if (decode_tree->get_child(HTree::Direction::LEFT) == nullptr) {
		int key = decode_tree->get_key();//once we've reached a char, get the key to see which char it is
		decode_tree = nullptr;//reset the tree to null
		freq_table[key] += 1;//add a char count to the freq table
		return key; //return the char
	}
	return decode_tree->get_key();//returns a negative key to the caller so it knows to call decode again
}