/*
 * A simple class to perform stream I/O on individual bits.
 * Before reading any bits, ensure your input stream still has valid inputs.
 */
#include <iostream>
#include <bitset>
class BitIO {
public:
	// Construct with one of either an input stream or output (the other null)
	BitIO(std::ostream* os, std::istream* is);

	// Flushes out any remaining output bits and trailing zeros, if any:
	~BitIO();

	BitIO(const BitIO&) = default;
	BitIO(BitIO&&) = default;
	BitIO& operator=(const BitIO&) = default;
	BitIO& operator=(BitIO&&) = default;

	// Output a single bit (buffered)
	void output_bit(bool bit);

	// Read a single bit (or trailing zero)
	bool input_bit();

private:
	std::ostream* ostream_ptr_;//declare the stream pointers
	std::istream* istream_ptr_;
	std::bitset<8> curr_bits;//bitset is used to pack the bits into chars to output, the true compressing.
	char liveDataIndex_;//used to pull and push bits to the bitstream
	bool endOfFileReached_;//used to check for the eof, destructor uses it to output trailing 0's
};
