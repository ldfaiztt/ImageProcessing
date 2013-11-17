#include "stdafx.h"
#include "ByteVecotr.h"


ByteVecotr::ByteVecotr()
{
}

ByteVecotr::ByteVecotr(byte * begin, byte * end)
	:vector<byte>(begin, end)
{
}

ByteVecotr::~ByteVecotr()
{
}
