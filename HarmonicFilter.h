#pragma once
#include "Median.h"
class HarmonicFilter :
	public MedianFilter
{
private:
	byte Harmonic(shared_ptr<ImageMask> src, int index);

protected:
	virtual byte ProcessingMask(shared_ptr<ImageMask> src, int index);

public:
	HarmonicFilter();
	HarmonicFilter(typeImgParaPtr imgP);
	virtual ~HarmonicFilter();
};

