#pragma once
#include <map>
#include <vector>
#include "TransImage.h"

typedef int stKey;
typedef int stVal;
typedef map<stKey, stVal> type_statistic_map;

class HistogramEQ :
	public TransImage
{
protected:
	int Statistic(typeImgPtr src, vector<shared_ptr<type_statistic_map>> & scale_statistic_maps);
public:
	HistogramEQ();
	HistogramEQ(typeImgParaPtr);
	virtual ~HistogramEQ();

	virtual typeImgPtr transit(typeImgPtr src);
};

