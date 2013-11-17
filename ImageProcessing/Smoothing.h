#pragma once
#include <vector>
#include "TransImage.h"

class ImageMask;

class SmoothingFilter :
	public TransImage
{
public:
	SmoothingFilter();
	SmoothingFilter(typeImgParaPtr imgP);
	virtual ~SmoothingFilter();

protected:
	int mask_size;
	vector<vector<int>> weight_mask;
	byte Average(shared_ptr<ImageMask> src, int index);
	void DefaultInit();
public:
	virtual typeImgPtr transit(typeImgPtr src);
};

