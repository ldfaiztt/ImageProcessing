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
	HistogramMatch(shared_ptr<stImgPara> imgP);
	virtual ~HistogramMatch();

	virtual shared_ptr<CImage> transit(shared_ptr<CImage> src);
};

