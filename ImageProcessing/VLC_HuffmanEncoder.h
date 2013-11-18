#pragma once
#include "MyBinaryTree.h"
#include "BuildHuffmanTree.h"
#include "BitVector.h"

class VLC_HuffmanEncoder
{
private:
	shared_ptr<MyBinaryTree<stNodeData>> huffmanTree;
	shared_ptr<unordered_map<stKey, shared_ptr<typeTreeNode>>> leafMap;

public:
	VLC_HuffmanEncoder(shared_ptr<MyBinaryTree<stNodeData>> tree, shared_ptr<unordered_map<stKey, shared_ptr<typeTreeNode>>> map);
	virtual ~VLC_HuffmanEncoder();

	BitVectorPtr transitData(ByteVecotrPtr src);
};

