#pragma once
#include "TransData.h"
#include "MyImage.h"
#include <list>

class VLC_HuffmanEncoder :
	public TransData
{
protected:
	int BuildHuffmanTree(list<type_statistic_pair> & lst);
public:
	VLC_HuffmanEncoder();
	VLC_HuffmanEncoder(TransData * pre);
	virtual ~VLC_HuffmanEncoder();

	void SortRawData(typeImgPtr img);
};

