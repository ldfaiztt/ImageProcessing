#include "stdafx.h"
#include "bilinear_interpolation.h"

BilinearInterpolation::BilinearInterpolation()
{
	dstW = 480;
	dstH = 640;
}

BilinearInterpolation::BilinearInterpolation(shared_ptr<stImgPara> imgP)
{
	if (imgP == NULL)
	{
		dstW = 480;
		dstH = 640;
	}
	else
	{
		dstW = imgP->width;
		dstH = imgP->height;
	}
}


BilinearInterpolation::~BilinearInterpolation()
{
}

shared_ptr<CImage> BilinearInterpolation::transit(shared_ptr<CImage> src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	shared_ptr<CImage> dst(new CImage());
	dst->Create(dstW, dstH, src->GetBPP());

	float ratioX = (float)srcW / dstW;
	float ratioY = (float)srcH / dstH;

	for (int i = 0; i < dstW; i++)
	{
		for (int j = 0; j < dstH; j++)
		{
			float dstI = ratioX * i;
			float dstJ = ratioY * j;
			int i_dec = floor(dstI);
			int j_dec = floor(dstJ);
			float i_diff = dstI - i_dec;
			float j_diff = dstJ - j_dec;

			int i_dec_plus = i_dec + 1;
			if (i_dec_plus >= srcW)
			{
				i_dec_plus = srcW - 1;
			}

			int j_dec_plus = j_dec + 1;
			if (j_dec_plus >= srcH)
			{
				j_dec_plus = srcH - 1;
			}
			
			float c1 = (1 - i_diff)*(1 - j_diff);
			COLORREF q1 = src->GetPixel(i_dec, j_dec);

			float c2 = (1 - i_diff) * j_diff;
			COLORREF q2 = src->GetPixel(i_dec, j_dec_plus);

			float c3 = i_diff * (1 - j_diff);
			COLORREF q3 = src->GetPixel(i_dec_plus, j_dec);

			float c4 = i_diff * j_diff;
			COLORREF q4 = src->GetPixel(i_dec_plus, j_dec_plus);

			int r = c1 * GetRValue(q1) + c2 * GetRValue(q2) + c3 * GetRValue(q3) + c4 * GetRValue(q4);
			int g = c1 * GetGValue(q1) + c2 * GetGValue(q2) + c3 * GetGValue(q3) + c4 * GetGValue(q4);
			int b = c1 * GetBValue(q1) + c2 * GetBValue(q2) + c3 * GetBValue(q3) + c4 * GetBValue(q4);

			dst->SetPixelRGB(i, j, r, g, b);
		}
	}

	return dst;
}