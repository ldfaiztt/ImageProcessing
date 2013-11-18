#pragma once
#include "BitVector.h"
#include "ByteVecotr.h"

class TransData
{
protected:
	unique_ptr<TransData> preOP;

	virtual BitVectorPtr transitDataOwn(BitVectorPtr src);
	virtual ByteVecotrPtr transitDataOwn(ByteVecotrPtr src);

public:
	static const byte PlaceHolder = 0xff;

public:
	TransData();
	TransData(TransData * pre);
	virtual ~TransData();

	BitVectorPtr transitData(BitVectorPtr src);
	ByteVecotrPtr transitData(ByteVecotrPtr src);
};

