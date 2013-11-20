#include "stdafx.h"
#include "TransData.h"


TransData::TransData()
{
	preOP = NULL;
}

TransData::TransData(TransData * pre)
{
	preOP.reset(pre);
}

TransData::~TransData()
{
}

ByteVecotrPtr TransData::transitData(ByteVecotrPtr src)
{
	if (preOP != NULL)
	{
		return transitDataOwn(preOP->transitData(src));
	}

	return transitDataOwn(src);
}

BitVectorPtr TransData::transitData(BitVectorPtr src)
{
	if (preOP != NULL)
	{
		return transitDataOwn(preOP->transitData(src));
	}

	return transitDataOwn(src);
}

ByteVecotrPtr TransData::transitDataOwn(ByteVecotrPtr src)
{
	return src;
}

BitVectorPtr TransData::transitDataOwn(BitVectorPtr src)
{
	return src;
}