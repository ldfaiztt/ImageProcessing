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

typeImgPtr Graying::transit(typeImgPtr src)
{
	if (src->IsNull())
	{
		return src;
	}

	typeImgPtr dst(new CImage());
	dst->Create(src->GetWidth(), src->GetHeight(), src->GetBPP(), 0);

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
				byte avg = (int)((r * 0.3) + (g * 0.59) + (b * 0.11));
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
			int avg = (lpColorTable[i].rgbRed * 0.3) + (lpColorTable[i].rgbGreen * 0.59) + (lpColorTable[i].rgbBlue * 0.11);
			lpColorTable[i].rgbRed = avg;
			lpColorTable[i].rgbGreen = avg;
			lpColorTable[i].rgbBlue = avg;
		}
		dst->SetColorTable(0, maxColors, lpColorTable);
		delete(lpColorTable);
	}

	return dst;
}