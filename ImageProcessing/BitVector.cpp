#include "stdafx.h"
#include "BitVector.h"


BitVector::BitVector()
{
}

BitVector::BitVector(BitVector::size_type num_bits, ULONG val)
	:dynamic_bitset<>(num_bits,val)
{

}


BitVector::~BitVector()
{
}
