#include "stdafx.h"
#include <memory>
#include "TransImage.h"
#include "Subsampling.h"
#include "Graying.h"
#include "Replication.h"
#include "bilinear_interpolation.h"
#include "nearest_neighbor.h"
#include "GrayLevel.h"
#include "PowerScale.h"
#include "LogScale.h"
#include "HistogramEQ.h"
#include "HistogramMatch.h"
#include "HistogramLocal.h"

using namespace std;

TransImage::TransImage()
{
}

TransImage::TransImage(typeImgParaPtr imgP)
{
}


TransImage::~TransImage()
{
}

int TransImage::ResetDstColorTable(typeImgPtr src, typeImgPtr dst)
{
	if (src->IsIndexed())
	{
		int srcColorTableEntries = src->GetMaxColorTableEntries();
		RGBQUAD	* srcColorTabs = new RGBQUAD[srcColorTableEntries];
		src->GetColorTable(0, srcColorTableEntries, srcColorTabs);

		int dstColorTableEntries = dst->GetMaxColorTableEntries();
		RGBQUAD	* dstColorTabs = new RGBQUAD[dstColorTableEntries];

		int ratio = ceil(srcColorTableEntries / dstColorTableEntries);
		for (int i = 0; i < dstColorTableEntries; i++)
		{
			//dstColorTabs[i].rgbBlue = dstColorTabs[i].rgbGreen = dstColorTabs[i].rgbRed = i;
			dstColorTabs[i] = srcColorTabs[i* ratio];
		}
		dst->SetColorTable(0, dstColorTableEntries, dstColorTabs);
		
		delete[] srcColorTabs;
		delete[] dstColorTabs;
	}
	
	return 0;
}

byte * TransImage::getImgBuff(typeImgPtr src)
{
	byte *pData = NULL;

	if (src->GetPitch() < 0)
	{
		pData = (BYTE*)src->GetBits() + (src->GetPitch()*(src->GetHeight() - 1));
	}
	else
	{
		pData = (BYTE*)src->GetBits();
	}

	return pData;
}

TransImage * TransImage::CreateTransition(Transitions tsType, typeImgParaPtr imgP)
{
	switch (tsType)
	{
	case Transitions::graying:
		return new Graying(imgP);
		break;

	case Transitions::subsampling:
		return new Subsampling(imgP);
		break;

	case Transitions::replication:
		return new Replication(imgP);
		break;

	case Transitions::nearest_neighbor:
		return new NearestNeighbor(imgP);
		break;

	case Transitions::bilinear_interpolation:
		return new BilinearInterpolation(imgP);
		break;

	case Transitions::gray_level:
		return new GrayLevel(imgP);
		break;

	case Transitions::pow_scale:
		return new PowerScale(imgP);
		break;

	case Transitions::log_scale:
		return new LogScale(imgP);
		break;

	case Transitions::histogram_eq:
		return new HistogramEQ(imgP);
		break;

	case Transitions::histogram_match:
		return new HistogramMatch(imgP);
		break;

	case Transitions::histogram_local:
		return new HistogramLocal(imgP);
		break;

	default:
		return NULL;
		break;
	}
}

typeImgPtr TransImage::transit_img(typeImgPtr src, Transitions tsType, typeImgParaPtr imgP /*= NULL*/)
{
	unique_ptr<TransImage> trs = unique_ptr<TransImage>(CreateTransition(tsType,imgP));
	if (trs == NULL)
	{
		return src;
	}

	return trs->transit(src);
}

int TransImage::Gcd(int a, int b)
{
	if (b == 0)
	{
		return a;
	}

	return Gcd(b, a % b);
}