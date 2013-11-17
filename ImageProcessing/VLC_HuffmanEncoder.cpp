#include "stdafx.h"
#include "VLC_HuffmanEncoder.h"
#include "HistogramEQ.h"

VLC_HuffmanEncoder::VLC_HuffmanEncoder()
	:TransData()
{
}

VLC_HuffmanEncoder::VLC_HuffmanEncoder(TransData * pre)
	: TransData(pre)
{

}

VLC_HuffmanEncoder::~VLC_HuffmanEncoder()
{
}

bool cmp(const type_statistic_pair & x, const type_statistic_pair & y)
{
	return x.second < y.second;
}

int VLC_HuffmanEncoder::BuildHuffmanTree(list<type_statistic_pair> & lst)
{
	while (!lst.empty())
	{
		type_statistic_pair left = lst.front();
		lst.pop_front();
		type_statistic_pair right = lst.front();
		lst.pop_front();

		type_statistic_pair merge = make_pair((left.first + right.first), (left.second + right.second));
	}

	return 0;
}

void VLC_HuffmanEncoder::SortRawData(typeImgPtr img)
{
	vector<std::shared_ptr<type_statistic_map>> maps;
	HistogramEQFilter::statistic(img, maps);

	for each (std::shared_ptr<type_statistic_map> map in maps)
	{
		list<type_statistic_pair> pairVec;
		for (type_statistic_map::iterator it = map->begin(); it != map->end(); it++)
		{
			pairVec.push_back(make_pair(it->first, it->second));
		}
		pairVec.sort(cmp);

		BuildHuffmanTree(pairVec);
	}
}
