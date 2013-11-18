#include "stdafx.h"
#include "VLC_HuffmanEncoder.h"

VLC_HuffmanEncoder::VLC_HuffmanEncoder(shared_ptr<MyBinaryTree<stNodeData>> tree, shared_ptr<unordered_map<stKey, shared_ptr<typeTreeNode>>> map)
	:huffmanTree(tree),
	leafMap(map)
{

}

VLC_HuffmanEncoder::~VLC_HuffmanEncoder()
{
}

BitVectorPtr VLC_HuffmanEncoder::transitData(ByteVecotrPtr src)
{
	BitVectorPtr ret = BitVectorPtr(new BitVector());

	for (ByteVecotr::iterator it = src->begin(); it != src->end(); it++)
	{
		unordered_map<stKey, shared_ptr<typeTreeNode>>::iterator got = leafMap->find(*it);
		if (got == leafMap->end())
		{
			return NULL;
		}
		else
		{
			shared_ptr<typeTreeNode> leaf = got->second;
			huffmanTree->setCurrentPos(leaf);

			BitVector bits;
			while (!huffmanTree->IsRoot())
			{
				bits.push_back(huffmanTree->GetCurrentData().Symbol);

				huffmanTree->Parent();
			}

			for (BitVector::size_type i = 0; i < bits.size(); i++)
			{
				ret->push_back(bits[bits.size() - 1 - i]);
			}
		}
	}

	return ret;
}
