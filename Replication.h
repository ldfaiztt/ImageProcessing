#pragma once
#include "TransImage.h"
class Replication :
	public TransImage
{
private:
	int dstW;
	int dstH;

public:
	Replication();
	Replication(typeImgParaPtr imgP);
	virtual ~Replication();

	virtual typeImgPtr transit(typeImgPtr src);
};

