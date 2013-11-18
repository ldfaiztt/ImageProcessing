#include "stdafx.h"
#include "VLC_HuffmanDecoder.h"


VLC_HuffmanDecoder::VLC_HuffmanDecoder(shared_ptr<MyBinaryTree<stNodeData>> tree)
	:huffmanTree(tree)
{
}


VLC_HuffmanDecoder::~VLC_HuffmanDecoder()
{
}

ByteVecotrPtr VLC_HuffmanDecoder::transitData(BitVectorPtr src)
{
	ByteVecotrPtr ret = ByteVecotrPtr(new ByteVecotr());
	ret->clear();

	huffmanTree->Root();

	for (BitVector::size_type i = 0; i < src->size(); i++ )
	{
		bool bit = (*src)[i];
		if (!bit)
		{
			huffmanTree->FirstChild();
		}
		else
		{
			huffmanTree->FirstChild();
			huffmanTree->NextSibling();
		}

		if (huffmanTree->IsLeaf())
		{
			stKey val = huffmanTree->GetCurrentData().GrayScale;
			ret->push_back(val);
			huffmanTree->Root();
		}
	}

	return ret;
}
