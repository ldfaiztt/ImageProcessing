#pragma once
#include "HistogramEQ.h"

class HistogramMatchFilter :
	public HistogramEQFilter
{
private:
	CString filePath;

protected:
	stKey MatchValInMap(shared_ptr<type_statistic_map> map, stVal val);

public:
	HistogramMatchFilter();
	HistogramMatchFilter(typeImgParaPtr imgP);
	virtual ~HistogramMatchFilter();

	virtual typeImgPtr transit(typeImgPtr src);
};

