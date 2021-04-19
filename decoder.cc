#include <iostream>
#include "bitio.hh"
#include "huffman.hh"
#include <fstream>
#include <string>
#include <vector>
using namespace std;


std::vector<int> file_to_vect(string filename) {//again to ease the process of encoding, avoiding opening multiple files at once and making confusing code
	Huffman huffman;
	vector<int> v;
	ifstream f(filename, ios::binary);//open the file in binary mode
	BitIO bit_io(nullptr, &f);// the bitio is using the reference to the file as its stream pointer
	int c = 0;
	while (!f.eof()) {//break when the position of the iterator of f is at the eof
		int temp_key; //the key/char that will be put in the vector
		do {
			c = bit_io.input_bit();//input a bit from the stream
			temp_key = huffman.decode(c);//decode the bit
		} while (temp_key < 0);//keep decoding until reaching a real char, not a negative key
		v.push_back(temp_key);//add the char to the vector
	}
	f.close();
	return v;
}

void decode_file(string filename){
	ofstream outfile(filename + ".plaintext", ios::binary);
	vector<int> v = file_to_vect(filename);//get the vector of the file, already decoded
	long unsigned int i = 0;
	while (i < v.size()-1) {//makes sure not to output the eof again 
		outfile.put(char(v[i]));//simply outputs the vector of chars to the outfile
		i++;
	}
	outfile.close();
}

int main(int argc, char* argv[]) {//same as encoder

	if (argc < 2) return 0;
	string filename = argv[1];
	decode_file(filename);

	return 0;
}

