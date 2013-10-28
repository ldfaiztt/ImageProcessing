#include "stdafx.h"
#include "HistogramEQ.h"

using namespace std;

HistogramEQFilter::HistogramEQFilter()
{
}

HistogramEQFilter::HistogramEQFilter(typeImgParaPtr)
{

}

HistogramEQFilter::~HistogramEQFilter()
{
}

int HistogramEQFilter::statistic(typeImgPtr img, vector<shared_ptr<type_statistic_map>> & scale_statistic_maps)
{
	scale_statistic_maps.clear();

	int srcW = img->GetWidth();
	int srcH = img->GetHeight();
	int srcL = img->GetBPP();
	int srcClrCount = srcL / 8;
	int srcRowBytes = img->GetPitch();
	byte * srcBuf = (byte *)img->GetBits();

	int max_num = 0;
	if (srcClrCount > 0)
	{
		for (int index = 0; index < srcClrCount; index++)
		{
			shared_ptr<type_statistic_map> scale_count_map(new type_statistic_map());
			for (int i = 0; i < srcH; i++)
			{
				for (int j = 0; j < srcW; j++)
				{
					byte r = img->getByteVal(j, i, index);
					type_statistic_map::iterator it = scale_count_map->find(r);
					if (it != scale_count_map->end())
					{
						it->second += 1;
						if (it->second > max_num)
						{
							max_num = it->second;
						}
					}
					else
					{
						scale_count_map->insert({ r, 1 });
						if (1 > max_num)
						{
							max_num = 1;
						}
					}
				}
			}

			scale_statistic_maps.push_back(scale_count_map);
		}
	}
	else
	{
		byte bit_mask = 0;
		for (int i = 0; i < srcL; i++)
		{
			bit_mask |= 1 << i;
		}

		shared_ptr<type_statistic_map> scale_count_map(new type_statistic_map());
		for (int i = 0; i < srcH; i++)
		{
			for (int j = 0; j < srcW; j++)
			{
				//byte r = img->getByteVal(j, i, index);
				byte r = (srcBuf[i * srcRowBytes + (j * srcL) / 8] >> ((j * srcL) % 8)) & bit_mask;
				type_statistic_map::iterator it = scale_count_map->find(r);
				if (it != scale_count_map->end())
				{
					it->second += 1;
					if (it->second > max_num)
					{
						max_num = it->second;
					}
				}
				else
				{
					scale_count_map->insert({ r, 1 });
					if (1 > max_num)
					{
						max_num = 1;
					}
				}
			}
		}

		scale_statistic_maps.push_back(scale_count_map);
	}
	

	return max_num;
}

int HistogramEQFilter::StatisticSum(typeImgPtr src, vector<shared_ptr<type_statistic_map>> & scale_statistic_maps)
{
	scale_statistic_maps.clear();

	int srcW = src->GetWidth();
	int srcH = src->GetHeight();
	//int srcRowBytes = src->GetPitch();
	int srcClrCount = src->GetBPP() / 8;

	for (int index = 0; index < srcClrCount; index++)
	{
		//byte * buf = (byte *)src->GetBits();
		type_statistic_map scale_count_map;
		for (int i = 0; i < srcH; i++)
		{
			for (int j = 0; j < srcW; j++)
			{
				//byte r = buf[i*srcRowBytes + j*srcClrCount + index];
				byte r = src->getByteVal(j, i, index);
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

typeImgPtr HistogramEQFilter::transit(typeImgPtr src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();
	int srcRowBytes = src->GetPitch();
	int srcClrCount = src->GetBPP() / 8;

	vector<shared_ptr<type_statistic_map>> statistic_maps;
	StatisticSum(src,statistic_maps);

	typeImgPtr dst(new MyImage());
	dst->Create(srcW, srcH, src->GetBPP());
	ResetDstColorTable(src, dst);

	int dstW = dst->GetWidth();
	int dstH = dst->GetHeight();
	int dstRowBytes = dst->GetPitch();
	int dstClrCount = dst->GetBPP() / 8;

	for (int index = 0; index < dstClrCount; index++)
	{
		byte * srcBuf = (byte *)src->GetBits();
		byte * dstBuf = (byte *)dst->GetBits();

		for (int i = 0; i < dstH; i++)
		{
			for (int j = 0; j < dstW; j++)
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
