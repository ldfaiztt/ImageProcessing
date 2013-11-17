#pragma once
#include "Median.h"
class GeometricFilter :
	public MedianFilter
{
private:
	byte Geometric(shared_ptr<ImageMask> src, int index);

protected:
	virtual byte ProcessingMask(shared_ptr<ImageMask> src, int index);

public:
	GeometricFilter();
	GeometricFilter(typeImgParaPtr imgP);
	virtual ~GeometricFilter();
};

