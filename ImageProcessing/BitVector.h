#pragma once
#include <boost/dynamic_bitset.hpp>

using namespace boost;

class BitVector
	: public dynamic_bitset<>
{
public:
	BitVector();
	BitVector(BitVector::size_type num_bits, ULONG val);

	virtual ~BitVector();
};

typedef std::shared_ptr<BitVector> BitVectorPtr;

