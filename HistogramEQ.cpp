#include "stdafx.h"
#include "HistogramEQ.h"

using namespace std;

HistogramEQ::HistogramEQ()
{
}

HistogramEQ::HistogramEQ(shared_ptr<stImgPara>)
{

}

HistogramEQ::~HistogramEQ()
{
}

shared_ptr<type_statistic_map> HistogramEQ::Statistic(shared_ptr<CImage> src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	type_statistic_map scale_count_map;

	for (int i = 0; i < srcW; i++)
	{
		for (int j = 0; j < srcH; j++)
		{
			COLORREF pixel = src->GetPixel(i, j);
			int r = GetRValue(pixel);

			type_statistic_map::iterator it = scale_count_map.find(r);
			if (it != scale_count_map.end())
			{
				it->second += 1;
			}
			else
			{
				scale_count_map.insert({ r, 1 });
			}
		}
	}

	int sum = 0;
	shared_ptr<type_statistic_map> scale_sum_map(new type_statistic_map());
	for (type_statistic_map::iterator it = scale_count_map.begin(); it != scale_count_map.end(); ++it)
	{
		sum += it->second;
		scale_sum_map->insert({ it->first, sum });
	}

	return scale_sum_map;
}

shared_ptr<CImage> HistogramEQ::transit(shared_ptr<CImage> src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	shared_ptr<type_statistic_map> statistic_map = Statistic(src);

	shared_ptr<CImage> dst(new CImage());
	dst->Create(srcW, srcH, src->GetBPP());

	for (int i = 0; i < srcW; i++)
	{
		for (int j = 0; j < srcH; j++)
		{
			COLORREF pixel = src->GetPixel(i, j);
			int r = GetRValue(pixel);

			int g = (statistic_map->at(r) * (statistic_map->size() - 1)) / (srcH * srcW);

			dst->SetPixelRGB(i, j, g, g, g);
		}
	}

	return dst;

}
