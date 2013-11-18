#pragma once

#include "MyBinaryTree.h"
#include "BuildHuffmanTree.h"
#include "BitVector.h"

class VLC_HuffmanDecoder
{
private:
	shared_ptr<MyBinaryTree<stNodeData>> huffmanTree;

public:
	VLC_HuffmanDecoder(shared_ptr<MyBinaryTree<stNodeData>> tree);
	virtual ~VLC_HuffmanDecoder();

	ByteVecotrPtr transitData(BitVectorPtr src);
};

