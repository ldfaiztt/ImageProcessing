#include "stdafx.h"
#include "HistogramLocal.h"


HistogramLocal::HistogramLocal()
{
	mask_size = 3;
}

HistogramLocal::HistogramLocal(shared_ptr<stImgPara> imgP)
{
	if (imgP == NULL)
	{
		mask_size = 3;
	}
	else
	{
		mask_size = imgP->mask_size;
	}
}


HistogramLocal::~HistogramLocal()
{
}

//shared_ptr<type_statistic_map> HistogramLocal::Statistic(typeImgPtr src)
//{
//	int srcW = src->GetWidth();
//	int srcH = src->GetHeight();
//
//	type_statistic_map scale_count_map;
//
//	for (int i = 0; i < srcW; i++)
//	{
//		for (int j = 0; j < srcH; j++)
//		{
//			COLORREF pixel = src->GetPixel(i, j);
//			byte r = GetRValue(pixel);
//
//			type_statistic_map::iterator it = scale_count_map.find(r);
//			if (it != scale_count_map.end())
//			{
//				it->second += 1;
//			}
//			else
//			{
//				scale_count_map.insert({ r, 1 });
//			}
//		}
//	}
//
//	int sum = 0;
//	shared_ptr<type_statistic_map> scale_sum_map(new type_statistic_map());
//	for (type_statistic_map::iterator it = scale_count_map.begin(); it != scale_count_map.end(); ++it)
//	{
//		sum += it->second;
//		scale_sum_map->insert({ it->first, sum });
//	}
//
//	return scale_sum_map;
//}

typeImgPtr HistogramLocal::transit(typeImgPtr src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();
	int srcRowBytes = src->GetPitch();
	int srcClrCount = src->GetBPP() / 8;

	typeImgPtr dst(new MyImage());
	dst->Create(srcW, srcH, src->GetBPP());
	ResetDstColorTable(src, dst);

	int dstW = dst->GetWidth();
	int dstH = dst->GetHeight();
	int dstRowBytes = dst->GetPitch();
	int dstClrCount = dst->GetBPP() / 8;

	byte * srcBuf = (byte *)src->GetBits();
	byte * dstBuf = (byte *)dst->GetBits();

	for (int i = 0; i < srcH; i++)
	{
		for (int j = 0; j < srcW; j++)
		{
			shared_ptr<ImageMask> mask(new ImageMask(*src, mask_size, j, i));
			vector<shared_ptr<type_statistic_map>> statistic_maps;
			Statistic(mask, statistic_maps);

			for (int index = 0; index < dstClrCount; index++)
			{
				byte r = srcBuf[i * srcRowBytes + j * srcClrCount + index];
				int sum = statistic_maps[index]->at(r);
				int L = (--statistic_maps[index]->end())->first;

				int g = (sum * L) / (mask_size * mask_size);
				dstBuf[i * dstRowBytes + j * dstClrCount + index] = g;
			}

		}
	}

	return dst;
}