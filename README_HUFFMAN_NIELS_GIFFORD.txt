NIELS/GIFFORD HUFFMAN ENCODING

hforest:
updated ###pop_tree### to ###pop_bottom### so it removes the lowest valued
tree from the forest.

bitio:
this class is used for inputting and outputting bits from a stream.
It uses #bitset# to take chars from files and converts them to their binary values
bitset also takes in bits and can encode multiple paths of bits in one character.

bitio takes one pointer as input, as it can't read and write at the same time
the other pointer is then set to nullptr to avoid memory errors


huffman:
the huffman.cc file includes multiple methods that create huffman trees for
encoding and decoding. The class also has a frequency table that is used to 
build the tree, putting the most frequent bits nearest to the top to ensure a 
short path/encoding. If the path is less than 8, it will be compressed. 
The frequency table is an array, due to it being a fixed size of 257, one for 
each ascii character, and the eof char.

encoder: 
encoder takes a txt file from the command line as input, then encodes the file 
using the methods from huffman. We decided to convert the file to a vector of 
ints first, for easier and cleaner code.
decoder outputs a newly made .comp binary file, which is compressed.

decoder:
the decoder takes a compressed file as input and uses the methods from 
huffman to decode it, building a frequency table along the way. It losslessly
decodes and outputs the same text as what was in the original .txt file.



BUILDING:

there is a makefile included. If all files are stored in the same directory,
use the command "make" on either #decoder# or #encoder# to compile them.
then on the command line, enter:
"
./encoder "example_text.txt"
"
and it will create a "example_text.txt.comp" compressed and encoded file in the
same directory. to decode, enter:
"
./decoder "example_text.txt.comp" 
"
and it will create "example_text.txt.comp.plaintext" in the same dir. It will be
identical to the og .txt file.

COMPRESSION TESTS:

 FILENAME       FILE SIZE  COMPRESSED SIZE  DECODED FILE MATCHES
------------------------------------------------------------
macklemore.txt  |3.6kb      | 2.4kb     |       yes        |          
------------------------------------------------------------
dolphin.txt     |2.7kb      |.69kb      |       yes        | 
------------------------------------------------------------
marsupial.txt   |.92kb      |.37kb      |       yes        | 
------------------------------------------------------------
encoder_text.txt|1.2kb      |1.1kb      |       yes        | 
------------------------------------------------------------
smurf.txt       |2.7kb      |1.1kb      |       yes        | 
------------------------------------------------------------



The compression worked much better on the ascii art, as it works better when
there are a few chars that are frequently used. the encoder_text file was 
surprisingly compressed by a very small amount, likely due to there being 
less characters altogether and a low frequency across all characters.

All decoded files exactly matched the original .txt files.
