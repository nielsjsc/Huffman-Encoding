#include <iostream>
#include "bitio.hh"
#include "huffman.hh"
#include <fstream>
#include <string>
#include <vector>
using namespace std;
std::vector<int> file_to_vect(string filename) {//converts the whole text file to a vector for easier access
	vector<int> v;//declare v to be a vector of ints
	ifstream f;
	f.open(filename, ios::binary);//open the file in binary mode to ensure no hiccups with line breaks
	int c = 0;
	do {
		c = f.get();//get the next char from the file
		v.push_back(c);//put it on the vector
	} 
	while (c != -1);//while the get-ed char isnt the eof char, continue pulling from the file
	
	f.close();
	return v;
}
void encode_file(string filename) {
	vector<int> v = file_to_vect(filename);//conver the file to a vector of all the chars

	ofstream outfile(filename + ".comp",ios::binary); //create a new file, with the same name as the input file, but with a .comp at the end
	BitIO bit_io(&outfile, nullptr);//create a bitio with the new file's stream as the stream

	Huffman huffman;
	for (size_t i = 0; i < v.size(); i++) {
		Huffman::bits_t bits = huffman.encode(v[i]);//encodes the current char in the vector to bits, then uses output_bit() to compress and output them to the stream
		for (size_t j = 0; j < bits.size(); j++) {
			bit_io.output_bit(bits[j]);//outputs the bits from the bits_t path in order, breaks when finished
		}
	}
	
	outfile.close();
}

int main(int argc, char* argv[]) {//takes two parameters from command line, an int of the number of inputs, and an array of pointers to the filenames.
	if (argc < 2)return 0;//if there isnt a file as input, just return to ensure no bugs
	string filename = argv[1];
	encode_file(filename);


	return argc;
}

