#pragma once
#include <vector>
#include <memory>

using namespace std;

class ByteVecotr
	:public vector<byte>
{
public:
	ByteVecotr();
	ByteVecotr(byte * begin, byte * end);

	virtual ~ByteVecotr();
};

typedef std::shared_ptr<ByteVecotr> ByteVecotrPtr;
