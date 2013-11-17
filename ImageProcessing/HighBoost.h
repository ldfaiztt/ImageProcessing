#pragma once
#include "Laplacian.h"
class HighBoostFilter :
	public LaplacianFilter
{
public:
	HighBoostFilter();
	HighBoostFilter(typeImgParaPtr imgP);
	virtual ~HighBoostFilter();

protected:
	double A;
	virtual int sharpening(shared_ptr<ImageMask> src, int index);
};

