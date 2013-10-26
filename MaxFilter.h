#pragma once
#include "Median.h"
class MaxFilter :
	public MedianFilter
{
private:
	byte MaxVectorSort(shared_ptr<ImageMask> src, int index);

protected:
	virtual byte ProcessingMask(shared_ptr<ImageMask> src, int index);

public:
	MaxFilter();
	MaxFilter(typeImgParaPtr imgP);
	virtual ~MaxFilter();
};

