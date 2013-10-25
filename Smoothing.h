#pragma once
#include <vector>
#include "TransImage.h"

class ImageMask;

class Smoothing :
	public TransImage
{
public:
	Smoothing();
	Smoothing(typeImgParaPtr imgP);
	virtual ~Smoothing();

protected:
	int mask_size;
	vector<vector<int>> weight_mask;
	byte Average(shared_ptr<ImageMask> src, int index);
	void DefaultInit();
public:
	virtual typeImgPtr transit(typeImgPtr src);
};

