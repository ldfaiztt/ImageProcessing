#pragma once
#include "TransImage.h"

class ImageMask;

const int mask_size = 3;

class LaplacianFilter :
	public TransImage
{
protected:
	int weight_mask[mask_size][mask_size];

	void Init_laplacian_nag4();
	void Init_laplacian_nag8();
	void Init_laplacian_pos4();
	void Init_laplacian_pos8();
	virtual int sharpening(shared_ptr<ImageMask> src, int index);

public:
	LaplacianFilter();
	LaplacianFilter(typeImgParaPtr imgP);
	virtual ~LaplacianFilter();

	virtual typeImgPtr transit(typeImgPtr src);
};

