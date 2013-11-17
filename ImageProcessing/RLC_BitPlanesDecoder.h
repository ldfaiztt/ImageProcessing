#pragma once
#include "TransData.h"
class RLC_BitPlanesDecoder :
	public TransData
{
protected:
	BitVectorPtr transitDataOwn(BitVectorPtr src);

public:
	RLC_BitPlanesDecoder();
	RLC_BitPlanesDecoder(TransData * pre);
	virtual ~RLC_BitPlanesDecoder();
};

