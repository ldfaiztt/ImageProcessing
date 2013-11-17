#pragma once
#include "TransImage.h"

class ImageMask;

class MedianFilter :
	public TransImage
{
private:
	byte MedianListSort(shared_ptr<ImageMask> src, int index);
	byte MedianVectorSort(shared_ptr<ImageMask> src, int index);
	byte MedianList(shared_ptr<ImageMask> src, int index);
	byte MedianVector(shared_ptr<ImageMask> src, int index);

protected:
	int mask_size;
	virtual byte ProcessingMask(shared_ptr<ImageMask> src, int index);

public:
	MedianFilter();
	MedianFilter(typeImgParaPtr imgP);
	virtual ~MedianFilter();

	virtual typeImgPtr transit(typeImgPtr src);
};

