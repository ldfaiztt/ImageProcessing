#pragma once
#include "MyImage.h"
#include "BitVector.h"

class BitPlaneBuilder
{
public:
	BitPlaneBuilder();
	virtual ~BitPlaneBuilder();

	int build(typeImgPtr src, vector<BitVectorPtr> & result);
	int build(ByteVecotrPtr src, vector<BitVectorPtr> & result);
};

