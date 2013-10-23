#pragma once
#include "HistogramEQ.h"
#include "ImageMask.h"

class HistogramLocal :
	public HistogramEQ
{
private:
	int mask_size;
	//shared_ptr<type_statistic_map> Statistic(typeImgPtr src);
public:
	HistogramLocal();
	HistogramLocal(shared_ptr<stImgPara> imgP);
	virtual ~HistogramLocal();

	virtual typeImgPtr transit(typeImgPtr src);
};

