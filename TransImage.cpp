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

TransImage::TransImage(shared_ptr<stImgPara> imgP)
{
}


TransImage::~TransImage()
{
}

TransImage * TransImage::CreateTransition(Transitions tsType, shared_ptr<stImgPara> imgP)
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

shared_ptr<CImage> TransImage::transit_img(shared_ptr<CImage> src, Transitions tsType, shared_ptr<stImgPara> imgP /*= NULL*/)
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