#pragma once
#include "TransImage.h"

class ImageMask;

class Median :
	public TransImage
{
protected:
	int mask_size;
	byte MedianListSort(shared_ptr<ImageMask> src, int index);
	byte MedianVectorSort(shared_ptr<ImageMask> src, int index);
	byte MedianList(shared_ptr<ImageMask> src, int index);
	byte MedianVector(shared_ptr<ImageMask> src, int index);

public:
	Median();
	Median(typeImgParaPtr imgP);
	virtual ~Median();

	virtual typeImgPtr transit(typeImgPtr src);
};

