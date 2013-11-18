#include "stdafx.h"
#include "RLC_GrayScaleDecoder.h"


RLC_GrayScaleDecoder::RLC_GrayScaleDecoder(int Num)
	: TransData()
{
	NumPerLine = Num;
}

RLC_GrayScaleDecoder::RLC_GrayScaleDecoder(int Num, TransData * preOP)
	: TransData(preOP)
{
	NumPerLine = Num;
}

RLC_GrayScaleDecoder::~RLC_GrayScaleDecoder()
{
}

ByteVecotrPtr RLC_GrayScaleDecoder::transitDataOwn(ByteVecotrPtr src)
{
	ByteVecotrPtr ret = ByteVecotrPtr(new ByteVecotr());
	ret->clear();

	if (src->size() <= 0)
	{
		return ret;
	}

	for (ByteVecotr::iterator it = src->begin(); it != src->end();)
	{
		if (NumPerLine <= 0)
		{
			byte elem = *it++;
			byte count = *it++;

			for (int i = 0; i < count; i++ )
			{
				ret->push_back(elem);
			}
		} 
		else
		{
			if (it == src->begin())
			{
				while (*it != PlaceHolder)
				{
					it++;
				}
			}

			int countLine = 0;
			while (countLine < NumPerLine)
			{
				byte elem = *it++;
				if (*it == PlaceHolder)
				{
					it++;
					break;
				}

				byte count = *it++;
				if (*it == PlaceHolder)
				{
					it++;
					break;
				}

				for (int i = 0; i < count; i++)
				{
					if (countLine >= NumPerLine)
					{
						break;
					}

					ret->push_back(elem);
					countLine++;
				}
			}

			if (countLine < NumPerLine)
			{
				for (int i = 0; i < NumPerLine - countLine; i++)
				{
					ret->push_back(*(it - 1));
				}
			}
			else
			{
				while (*it != PlaceHolder)
				{
					it++;
				}
			}
		}
	}
}