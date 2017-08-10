#include "BitInputStream.hpp"

int BitInputStream::readBit() {

	int bit; 
	if(buf_index == 8) {
		buf = in.get();
		buf_index = 0;
	}

	bit = bitVal(buf, buf_index+1);
	buf_index++;
	return bit;
}

int BitInputStream::readByte() {
	return in.get();
}

int BitInputStream::readInt() {
	int buffer;
	in.read((char *)&buffer,sizeof(int));
	return buffer;
}

char BitInputStream::bitVal(char b, int i) {
	char c = (b >> (i-1)) & 1;
	return c;
}
