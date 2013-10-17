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
	Replication(shared_ptr<stImgPara> imgP);
	virtual ~Replication();

	virtual shared_ptr<CImage> transit(shared_ptr<CImage> src);
};

