#pragma once
#include <vector>
#include "TransImage.h"

class HistogramEQFilter :
	public TransImage
{
protected:
	int StatisticSum(typeImgPtr src, vector<shared_ptr<type_statistic_map>> & scale_statistic_maps);
public:
	HistogramEQFilter();
	HistogramEQFilter(typeImgParaPtr);
	virtual ~HistogramEQFilter();

	virtual typeImgPtr transit(typeImgPtr src);

public:
	static int statistic(typeImgPtr img, vector<shared_ptr<type_statistic_map>> & scale_statistic_maps);
	static int statistic(typeImgPtr img, type_statistic_map & scale_statistic_map);
};

