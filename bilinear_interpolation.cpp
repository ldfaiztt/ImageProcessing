#include "stdafx.h"
#include "bilinear_interpolation.h"

BilinearInterpolation::BilinearInterpolation()
{
	dstW = 480;
	dstH = 640;
}

BilinearInterpolation::BilinearInterpolation(typeImgParaPtr imgP)
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

typeImgPtr BilinearInterpolation::transit(typeImgPtr src)
{
	int srcW = src->GetWidth();
	int srcH = src->GetHeight();

	typeImgPtr dst(new MyImage());
	dst->Create(dstW, dstH, src->GetBPP());
	ResetDstColorTable(src, dst);

	float ratioX = (float)srcW / dstW;
	float ratioY = (float)srcH / dstH;

	int srcRowBytes = src->GetPitch();
	int srcClrCount = src->GetBPP() / 8;
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
				float dstI = ratioX * i;
				float dstJ = ratioY * j;
				int i_dec = floor(dstI);
				int j_dec = floor(dstJ);
				float i_diff = dstI - i_dec;
				float j_diff = dstJ - j_dec;

				int i_dec_plus = i_dec + 1;
				if (i_dec_plus >= srcH)
				{
					i_dec_plus = srcH - 1;
				}

				int j_dec_plus = j_dec + 1;
				if (j_dec_plus >= srcW)
				{
					j_dec_plus = srcW - 1;
				}
			
				float c1 = (1 - i_diff)*(1 - j_diff);
				byte q1 = srcBuf[i_dec * srcRowBytes + j_dec * srcClrCount + index];

				float c2 = (1 - i_diff) * j_diff;
				byte q2 = srcBuf[i_dec * srcRowBytes + j_dec_plus * srcClrCount + index];

				float c3 = i_diff * (1 - j_diff);
				byte q3 = srcBuf[i_dec_plus * srcRowBytes + j_dec * srcClrCount + index];

				float c4 = i_diff * j_diff;
				byte q4 = srcBuf[i_dec_plus * srcRowBytes + j_dec_plus * srcClrCount + index];

				byte g = c1 * GetRValue(q1) + c2 * GetRValue(q2) + c3 * GetRValue(q3) + c4 * GetRValue(q4);

				dstBuf[i * dstRowBytes + j * dstClrCount + index] = g;
			}
		}
	}

	return dst;
}