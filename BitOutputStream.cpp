#include "BitOutputStream.hpp"

void BitOutputStream::writeBit(int bit) {
	if(buf_index == 8) {
		this->flush();
	}
	buf = setBit(buf, bit, buf_index+1);
	buf_index++;
}

void BitOutputStream::writeByte(int i) {
	out.write((const char *)&i,sizeof(char));
}

void BitOutputStream::writeInt(int i) {
	out.write((const char*)&i,sizeof(int));
}

void BitOutputStream::flush() {
	out.put(buf);
	buf_index = 0;
	buf = 0;
}

char BitOutputStream::setBit(char b, int bit, int n) {
	char c;
	if(bit==1) {
		c = b | (bit <<n-1);
	}
	else {
		c= b & ~ (1<<n-1);
	}
	return c;
}
