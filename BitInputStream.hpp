#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

using namespace std;

class BitInputStream {
private:
    istream& in;  // use istream to composite  bit stream
    char buf;     // the buffer of bits
    int buf_index;     // index to access buf
    char bitVal(char b, int i);
public:
  // constructor
  BitInputStream(istream& s) : in(s), buf(0), buf_index(8) { }

  // read next bit
  int readBit();

  // read next byte, used for decoding header
  int readByte();

  // read next int, used for decoding header
  int readInt();
};

#endif
