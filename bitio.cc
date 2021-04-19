#include "bitio.hh"
#include <cassert>
#include <sstream>
#include <iostream>
using namespace std;


BitIO::BitIO(std::ostream* os, std::istream* is) {
	liveDataIndex_ = -1;//index initialized to -1 for pulling bits
	endOfFileReached_ = false;//not at eof


	if (os) {
		ostream_ptr_ = os;//will be nullptr if no stream inp
	}
	else if (is) {
		istream_ptr_ = is;
	}
}

BitIO::~BitIO() {

	if (ostream_ptr_) {
		// flush if any data
		if (liveDataIndex_ >= 0) {
			unsigned long int bit_int = curr_bits.to_ulong();//bitset isnt empty, flush last bits w trailing 0's.
			*ostream_ptr_ << char(bit_int);
		}
		liveDataIndex_ = -1;//iterate to the left
	}
}

bool BitIO::input_bit() {
	// first, instead of curr_bits_count, use live_data_index.
	// live_data_index is -1 when no data
	if (liveDataIndex_ < 0) {
		// load 8 more bits into bitset
		int bit_int = istream_ptr_->get();//if bitset is clear, get a new char.
		if (bit_int < 0) {
			return false;
		}
		curr_bits = std::bitset<8>(bit_int); //makes curr_bits be a 8 bit representation of the char
		liveDataIndex_ = 7;//reset the index to leftmost bit
	}
	bool out_bit = curr_bits.test(liveDataIndex_);//test the current bit
	liveDataIndex_--;
	return out_bit; //return the current bit


}

void BitIO::output_bit(bool bit) {
	// if full then flush
	if (liveDataIndex_ > 6) {
		// flush
		unsigned long int bit_int = curr_bits.to_ulong();//convert bits to char
		*ostream_ptr_ << char(bit_int);//output char to stream

		liveDataIndex_ = -1;
		curr_bits.reset(); //reset the bits to ensure trailing 0's if necessary
	}

	// write new bit to bitset
	liveDataIndex_++;
	curr_bits.set(7-liveDataIndex_, bit); //set the current bit to the input.

	return;

}