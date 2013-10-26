#pragma once
#include "TransImage.h"
#include <vector>

class BitSlicing :
	public TransImage
{
public:
	BitSlicing();
	BitSlicing(typeImgParaPtr imgP);
	virtual ~BitSlicing();
	int CountBitPlane(byte mask);

protected:
	byte bit_mask;
	std::vector<byte> bit_planes;
public:
	virtual typeImgPtr transit(typeImgPtr src);
};

