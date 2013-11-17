#pragma once
#include "Median.h"
class ArithmeticFilter :
	public MedianFilter
{
private:
	byte Arithmetic(shared_ptr<ImageMask> src, int index);

protected:
	virtual byte ProcessingMask(shared_ptr<ImageMask> src, int index);

public:
	ArithmeticFilter();
	ArithmeticFilter(typeImgParaPtr imgP);
	virtual ~ArithmeticFilter();
};

