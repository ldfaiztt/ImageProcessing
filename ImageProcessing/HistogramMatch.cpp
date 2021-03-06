#include "stdafx.h"
#include "HistogramMatch.h"

HistogramMatchFilter::HistogramMatchFilter()
{
	filePath = L"IMG_6706.jpg";
}

HistogramMatchFilter::HistogramMatchFilter(typeImgParaPtr imgP)
{
	if (imgP == NULL)
	{
		filePath = L"IMG_0731.jpg";
	}
	else
	{
		filePath = imgP->filePath;
	}
}

HistogramMatchFilter::~HistogramMatchFilter()
{
}

stKey HistogramMatchFilter::MatchValInMap(shared_ptr<type_statistic_map> map, stVal val)
{
	for (type_statistic_map::iterator it = map->begin(); it != map->end(); it++)
	{
		if (it->second == val)
		{
			return it->first;
		}
		else if (it->second > val)
		{
			if (it == map->begin())
			{
				return it->first;
			}
			else
			{
				type_statistic_map::iterator cur = it;
				type_statistic_map::iterator prev = --it;
				return abs(prev->second - val) <= abs(cur->second - val) ? prev->first : cur->first;
			}
		}
	}

	return (--map->end())->first;
}

typeImgPtr HistogramMatchFilter::transit(typeImgPtr src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();
	int srcRowBytes = src->GetPitch();
	int srcClrCount = src->GetBPP() / 8;

	MyImage match_img;
	match_img.Load(filePath);

	vector<shared_ptr<type_statistic_map>> match_maps;
	StatisticSum(make_shared<MyImage>(match_img), match_maps);

	vector<shared_ptr<type_statistic_map>> src_maps;
	StatisticSum(src,src_maps);

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

		for (int i = 0; i < srcH; i++)
		{
			for (int j = 0; j < srcW; j++)
			{
				byte r = srcBuf[i * srcRowBytes + j * srcClrCount + index];
				stKey g = MatchValInMap(match_maps[index % match_maps.size()], src_maps[index]->at(r));
				
				dstBuf[i * dstRowBytes + j * dstClrCount + index] = g;
			}
		}
	}

	return dst;
}
