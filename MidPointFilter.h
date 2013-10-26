#pragma once
#include "Median.h"

class MidPointFilter :
	public MedianFilter
{
private:
	byte MidVectorSort(shared_ptr<ImageMask> src, int index);

protected:
	virtual byte ProcessingMask(shared_ptr<ImageMask> src, int index);

public:
	MidPointFilter();
	MidPointFilter(typeImgParaPtr imgP);
	virtual ~MidPointFilter();
};

