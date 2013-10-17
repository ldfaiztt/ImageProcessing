#pragma once
#include <map>
#include "TransImage.h"

typedef int stKey;
typedef int stVal;
typedef map<stKey, stVal> type_statistic_map;

class HistogramEQ :
	public TransImage
{
protected:
	shared_ptr<type_statistic_map> Statistic(shared_ptr<CImage> src);
public:
	HistogramEQ();
	HistogramEQ(shared_ptr<stImgPara>);
	virtual ~HistogramEQ();

	virtual shared_ptr<CImage> transit(shared_ptr<CImage> src);
};

