#include "stdafx.h"
#include "HistogramLocal.h"


HistogramLocal::HistogramLocal()
{
	mask_size = 7;
}

HistogramLocal::HistogramLocal(shared_ptr<stImgPara> imgP)
{
	if (imgP == NULL)
	{
		mask_size = 7;
	}
	else
	{
		mask_size = imgP->width;
	}
}


HistogramLocal::~HistogramLocal()
{
}

shared_ptr<type_statistic_map> HistogramLocal::Statistic(shared_ptr<ImageMask> src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	type_statistic_map scale_count_map;

	for (int i = 0; i < srcW; i++)
	{
		for (int j = 0; j < srcH; j++)
		{
			COLORREF pixel = src->GetPixel(i, j);
			byte r = GetRValue(pixel);

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

shared_ptr<CImage> HistogramLocal::transit(shared_ptr<CImage> src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	shared_ptr<CImage> dst(new CImage());
	dst->Create(srcW, srcH, src->GetBPP());

	for (int i = 0; i < srcW; i++)
	{
		for (int j = 0; j < srcH; j++)
		{
			shared_ptr<ImageMask> mask(new ImageMask(*src, mask_size, i, j));
			shared_ptr<type_statistic_map> statistic_map = Statistic(mask);

			COLORREF pixel = src->GetPixel(i, j);
			int r = GetRValue(pixel);

			int sum = statistic_map->at(r);
			int L = (--statistic_map->end())->first;

			int g = sum * L / (mask_size * mask_size);
			dst->SetPixelRGB(i, j, g, g, g);
		}
	}

	return dst;
}