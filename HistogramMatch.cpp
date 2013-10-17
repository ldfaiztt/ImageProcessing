#include "stdafx.h"
#include "HistogramMatch.h"

HistogramMatch::HistogramMatch()
{
	filePath = L"IMG_6706.jpg";
}

HistogramMatch::HistogramMatch(shared_ptr<stImgPara> imgP)
{
	if (imgP == NULL)
	{
		filePath = L"IMG_6706.jpg";
	}
	else
	{
		filePath = imgP->filePath;
	}
}

HistogramMatch::~HistogramMatch()
{
}

stKey HistogramMatch::MatchValInMap(shared_ptr<type_statistic_map> map, stVal val)
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

shared_ptr<CImage> HistogramMatch::transit(shared_ptr<CImage> src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	CImage match_img;
	match_img.Load(filePath);
	shared_ptr<type_statistic_map> match_map = Statistic(make_shared<CImage>(match_img));

	shared_ptr<type_statistic_map> src_map = Statistic(src);

	shared_ptr<CImage> dst(new CImage());
	dst->Create(srcW, srcH, src->GetBPP());
	
	for (int i = 0; i < srcW; i++)
	{
		for (int j = 0; j < srcH; j++)
		{
			COLORREF pixel = src->GetPixel(i, j);
			int r = GetRValue(pixel);
			stKey g = MatchValInMap(match_map, src_map->at(r));
			
			dst->SetPixelRGB(i, j, g, g, g);
		}
	}

	return dst;
}
