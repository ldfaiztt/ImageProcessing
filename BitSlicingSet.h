#pragma once
#include "TransImage.h"
class BitSlicingSet :
	public TransImage
{
protected:
	byte bit_mask;

public:
	BitSlicingSet();
	BitSlicingSet(typeImgParaPtr imgP);
	virtual ~BitSlicingSet();
	virtual typeImgPtr transit(typeImgPtr src);
};

