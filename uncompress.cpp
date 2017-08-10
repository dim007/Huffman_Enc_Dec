#include <fstream>
#include <map>
#include <iostream>
#include <vector>
#include "HCTree.hpp"
#include "BitInputStream.hpp"
using namespace std;
int main(int argc, char* argv[]) {
	vector<int> freqs = vector<int>(256,0);
	ifstream inFile;
	ofstream outFile;
	outFile.open(argv[2],ios::binary);
	inFile.open(argv[1], ios::binary);
	int frequency;
	int total_freq; //counts total number of characters, prevents extra chars
	int huffBit;
	char c;
	int numUniqueChars;
	BitInputStream bitIn = BitInputStream(inFile);
	/**** OLD READ HEADER 1024 bytes
	 for(int i = 0; i < 256; i++){ //read header ints
		frequency = bitIn.readInt();
		freqs[i] = frequency;
		total_freq = total_freq + frequency;
	}****/
	numUniqueChars = bitIn.readInt(); //gets first byte in encoded file
	for(int i = 0; i < numUniqueChars; i++){ //reading header
		unsigned char symbol = bitIn.readByte();
		frequency = bitIn.readInt();
		freqs[symbol] = frequency;
		total_freq = total_freq + frequency;
	}
	HCTree tree; //Note to self:creates on stack instead of calling constructor
	tree.build(freqs); //does not require & in build, & means pass by reference
	while(total_freq != 0) {
		huffBit = tree.decode(bitIn);
		c = (char) huffBit;
		outFile.write((const char*)&c,sizeof(char)); //TA type casted
		total_freq--;
	}
	outFile.flush();
	inFile.close();
	outFile.close();
};
