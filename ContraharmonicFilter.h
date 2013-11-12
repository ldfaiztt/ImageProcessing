#pragma once
#include "Median.h"
class ContraharmonicFilter :
	public MedianFilter
{
private:
	int Q;
	byte Contraharmonic(shared_ptr<ImageMask> src, int index);

protected:
	virtual byte ProcessingMask(shared_ptr<ImageMask> src, int index);

public:
	ContraharmonicFilter();
	ContraharmonicFilter(typeImgParaPtr imgP);
	virtual ~ContraharmonicFilter();
};

