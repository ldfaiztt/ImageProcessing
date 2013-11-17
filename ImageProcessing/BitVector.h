#pragma once
#include <boost/dynamic_bitset.hpp>

using namespace boost;

class BitVector
	: public dynamic_bitset<>
{
public:
	BitVector();
	virtual ~BitVector();
};

typedef std::shared_ptr<BitVector> BitVectorPtr;

