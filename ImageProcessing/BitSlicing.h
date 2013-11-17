#pragma once
#include "BitSlicingSet.h"
#include <vector>

class BitSlicingReConstruct :
	public BitSlicingSet
{
public:
	BitSlicingReConstruct();
	BitSlicingReConstruct(typeImgParaPtr imgP);
	virtual ~BitSlicingReConstruct();
	virtual typeImgPtr transit(typeImgPtr src);

private:
	int CountBitPlane(byte mask);

protected:
	std::vector<byte> bit_planes;
};

