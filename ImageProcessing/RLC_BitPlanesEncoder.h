#pragma once
#include "TransData.h"

class RLC_BitPlanesEncoder :
	public TransData
{
protected:
	BitVectorPtr transitDataOwn(BitVectorPtr src);

public:
	RLC_BitPlanesEncoder();
	RLC_BitPlanesEncoder(TransData * pre);
	virtual ~RLC_BitPlanesEncoder();

};

