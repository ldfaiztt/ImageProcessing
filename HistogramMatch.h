#pragma once
#include "HistogramEQ.h"

class HistogramMatch :
	public HistogramEQ
{
private:
	CString filePath;

protected:
	stKey MatchValInMap(shared_ptr<type_statistic_map> map, stVal val);

public:
	HistogramMatch();
	HistogramMatch(typeImgParaPtr imgP);
	virtual ~HistogramMatch();

	virtual typeImgPtr transit(typeImgPtr src);
};

