#include "stdafx.h"
#include "Graying.h"

Graying::Graying()
{
}


Graying::Graying(shared_ptr<stImgPara> imgP)
{
}


Graying::~Graying()
{
}

shared_ptr<CImage> Graying::transit(shared_ptr<CImage> src)
{
	if (src->IsNull())
	{
		return src;
	}

	shared_ptr<CImage> dst(new CImage());
	dst->Create(src->GetWidth(), src->GetHeight(), src->GetBPP());

	if (!src->IsIndexed())
	{
		int maxY = src->GetHeight();
		int maxX = src->GetWidth();

		for (int i = 0; i < maxX; i++)
		{
			for (int j = 0; j < maxY; j++)
			{
				COLORREF pixel = src->GetPixel(i, j);
				byte r = GetRValue(pixel);
				byte g = GetGValue(pixel);
				byte b = GetBValue(pixel);
				byte avg = (int)(((int)r + g + b) / 3);
				dst->SetPixelRGB(i, j, avg, avg, avg);
			}
		}
	}
	else
	{
		int maxColors = src->GetMaxColorTableEntries();
		RGBQUAD * lpColorTable;
		lpColorTable = new RGBQUAD[maxColors];
		src->GetColorTable(0, maxColors, lpColorTable);
		for (int i = 0; i < maxColors; i++)
		{
			int avg = (lpColorTable[i].rgbRed + lpColorTable[i].rgbGreen + lpColorTable[i].rgbBlue) / 3;
			lpColorTable[i].rgbRed = avg;
			lpColorTable[i].rgbGreen = avg;
			lpColorTable[i].rgbBlue = avg;
		}
		dst->SetColorTable(0, maxColors, lpColorTable);
		delete(lpColorTable);
	}

	return dst;
}