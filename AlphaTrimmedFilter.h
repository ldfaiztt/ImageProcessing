#pragma once
#include "Median.h"
class AlphaTrimmedFilter :
	public MedianFilter
{
private:
	byte AlphaTrimmed(shared_ptr<ImageMask> src, int index);

protected:
	virtual byte ProcessingMask(shared_ptr<ImageMask> src, int index);

public:
	AlphaTrimmedFilter();
	AlphaTrimmedFilter(typeImgParaPtr imgP);
	virtual ~AlphaTrimmedFilter();
};

