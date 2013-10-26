#pragma once
#include "Median.h"
class MinFilter :
	public MedianFilter
{
private:
	byte MinVectorSort(shared_ptr<ImageMask> src, int index);

protected:
	virtual byte ProcessingMask(shared_ptr<ImageMask> src, int index);

public:
	MinFilter();
	MinFilter(typeImgParaPtr imgP);
	virtual ~MinFilter();
};

