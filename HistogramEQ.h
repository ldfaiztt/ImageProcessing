#pragma once
#include <map>
#include <vector>
#include "TransImage.h"

typedef int stKey;
typedef int stVal;
typedef map<stKey, stVal> type_statistic_map;

class HistogramEQFilter :
	public TransImage
{
protected:
	int Statistic(typeImgPtr src, vector<shared_ptr<type_statistic_map>> & scale_statistic_maps);
public:
	HistogramEQFilter();
	HistogramEQFilter(typeImgParaPtr);
	virtual ~HistogramEQFilter();

	virtual typeImgPtr transit(typeImgPtr src);
};

