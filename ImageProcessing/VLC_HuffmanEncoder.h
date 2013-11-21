#pragma once
#include "HuffmanTreeBuilder.h"
#include "BitVector.h"
#include "MyBinaryTree.h"

class VLC_HuffmanEncoder
{
private:
	MyBinaryTree<stNodeData> & huffmanTree;
	unordered_map<stKey, shared_ptr<typeTreeNode>> & leafMap;

public:
	VLC_HuffmanEncoder(MyBinaryTree<stNodeData> & tree, unordered_map<stKey, shared_ptr<typeTreeNode>> & map);
	virtual ~VLC_HuffmanEncoder();

	BitVectorPtr transitData(ByteVecotrPtr src);
};

