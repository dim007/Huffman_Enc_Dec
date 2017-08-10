#include <fstream>
#include <map>
#include <iostream>
#include <vector>
#include "HCTree.hpp"
#include "BitOutputStream.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	vector<int> freqs = vector<int>(256,0);
	ifstream inFile;
	ofstream outFile;
	char c;
	int asciiVal;
	int numUniqueChars = 0;

	outFile.open(argv[2],ios::binary);
	inFile.open(argv[1], ios::binary);

	//check if files are opened correctly
	if(!outFile.is_open() ) {
		cerr << "Invalid output file." << endl;
		return -1;
	} else if(!inFile.is_open() ) {
		cerr << "Invalid input file." << endl;
		return -1;
	}

	BitOutputStream bitOut = BitOutputStream(outFile); //initialize bitOutStream

	while(true){ //count frequency of chars
		asciiVal = inFile.get();
		if(inFile.eof()){
			break;
		}
		freqs[asciiVal]++;
	}
	HCTree tree; //local tree on stack, 'new' not needed
	tree.build(freqs);
	for(int i = 0; i < 256; i++){ //counting unique chars
		if(freqs[i] != 0){
			numUniqueChars++; //should be less than 256
		}
	}
	bitOut.writeInt(numUniqueChars); //written as char
	for(int i = 0; i < 256; i++){ //THIS writes HEADER
		//bitOut.writeInt(freqs[i]); **** Original Header write method 1024 bytes
		if(freqs[i] == 0){ //Starting compressed Header method
			continue;
		}
		bitOut.writeByte(i); //write char i
		bitOut.writeInt(freqs[i]); //write freq of char i
	}
	inFile.clear();
	inFile.seekg(0, inFile.beg);	//start from top of FILE
	while(true) { // Encodes message
		c = (char) inFile.get();
		if(inFile.eof()){
			break;
		}
		tree.encode(c,bitOut);
	}
	bitOut.flush();
	inFile.close();
	outFile.close();
	return 0;
};
