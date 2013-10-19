#include "stdafx.h"
#include "HistogramEQ.h"

using namespace std;

HistogramEQ::HistogramEQ()
{
}

HistogramEQ::HistogramEQ(typeImgParaPtr)
{

}

HistogramEQ::~HistogramEQ()
{
}

int HistogramEQ::Statistic(typeImgPtr src, vector<shared_ptr<type_statistic_map>> & scale_statistic_maps)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();
	int srcRowBytes = src->GetPitch();
	int srcClrCount = src->GetBPP() / 8;

	for (int index = 0; index < srcClrCount; index++)
	{
		byte * buf = (byte *)src->GetBits();
		
		type_statistic_map scale_count_map;
		for (int i = 0; i < srcH; i++)
		{
			for (int j = 0; j < srcW; j++)
			{
				byte r = buf[i*srcRowBytes + j*srcClrCount + index];
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

		scale_statistic_maps.push_back(scale_sum_map);
	}

	return 0;
}

typeImgPtr HistogramEQ::transit(typeImgPtr src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();
	int srcRowBytes = src->GetPitch();
	int srcClrCount = src->GetBPP() / 8;

	vector<shared_ptr<type_statistic_map>> statistic_maps;
	Statistic(src,statistic_maps);

	typeImgPtr dst(new CImage());
	dst->Create(srcW, srcH, src->GetBPP());

	int dstW = dst->GetWidth();
	int dstH = dst->GetHeight();
	int dstRowBytes = dst->GetPitch();
	int dstClrCount = dst->GetBPP() / 8;

	for (int index = 0; index < dstClrCount; index++)
	{
		byte * srcBuf = (byte *)src->GetBits();
		byte * dstBuf = (byte *)dst->GetBits();

		for (int i = 0; i < srcH; i++)
		{
			for (int j = 0; j < srcW; j++)
			{
				byte r = srcBuf[i * srcRowBytes + j * srcClrCount + index];
				int sum = statistic_maps[index]->at(r);
				int L = (--statistic_maps[index]->end())->first;

				int g = (sum * L) / (srcH * srcW);
				dstBuf[i * dstRowBytes + j * dstClrCount + index] = g;
			}
		}
	}

	return dst;

}
