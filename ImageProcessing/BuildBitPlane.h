#pragma once
#include "MyImage.h"
#include "BitVector.h"

class BuildBitPlane
{
public:
	BuildBitPlane();
	virtual ~BuildBitPlane();

	int build(typeImgPtr src, vector<BitVectorPtr> & result);
	int build(ByteVecotrPtr src, vector<BitVectorPtr> & result);
};

