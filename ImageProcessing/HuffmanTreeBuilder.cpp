#include "stdafx.h"
#include "HuffmanTreeBuilder.h"
#include "HistogramEQ.h"

HuffmanTreeBuilder::HuffmanTreeBuilder()
{
}

HuffmanTreeBuilder::~HuffmanTreeBuilder()
{
}

bool cmp(const shared_ptr<typeTreeNode> & x, const shared_ptr<typeTreeNode> & y)
{
	return x->getDataRef().Probability < y->getDataRef().Probability;
}

shared_ptr<MyBinaryTree<stNodeData>> HuffmanTreeBuilder::GenerateHuffmanTree(type_statistic_map & statistic_map, unordered_map<stKey, shared_ptr<typeTreeNode>> & leafMap)
{
	list<shared_ptr<typeTreeNode>> Nodes;
	for (type_statistic_map::iterator it = statistic_map.begin(); it != statistic_map.end(); it++)
	{
		stNodeData data;
		data.GrayScale = it->first;
		data.Probability = it->second;
		shared_ptr<typeTreeNode> node(new typeTreeNode(data));
		Nodes.push_back(node);
	}
	Nodes.sort(cmp);

	while (Nodes.size() > 1)
	{
		shared_ptr<typeTreeNode> left = Nodes.front();
		left->getDataRef().Symbol = 0;
		Nodes.pop_front();
		if (left->getFirstChild() == NULL)
		{
			leafMap.insert(std::make_pair(left->getDataRef().GrayScale, left));
		}

		shared_ptr<typeTreeNode> right = Nodes.front();
		right->getDataRef().Symbol = 1;
		Nodes.pop_front();
		if (right->getFirstChild() == NULL)
		{
			leafMap.insert(std::make_pair(right->getDataRef().GrayScale, right));
		}

		stNodeData data;
		data.GrayScale = left->getDataRef().GrayScale + right->getDataRef().GrayScale;
		data.Probability = left->getDataRef().Probability + right->getDataRef().Probability;
		shared_ptr<typeTreeNode> merge(new typeTreeNode(data));

		left->setParent(merge);
		right->setParent(merge);

		left->setNextSlibing(right);
		merge->setFirstChild(left);

		list<shared_ptr<typeTreeNode>>::iterator it = Nodes.begin();
		for (; it != Nodes.end(); it++)
		{
			if (merge->getDataRef().Probability < (*it)->getDataRef().Probability)
			{
				it = Nodes.insert(it, merge);
			}

			break;
		}

		if (it == Nodes.end())
		{
			Nodes.push_back(merge);
		}
	}

	return shared_ptr<MyBinaryTree<stNodeData>>(new MyBinaryTree<stNodeData>(Nodes.front()));
}

shared_ptr<MyBinaryTree<stNodeData>> HuffmanTreeBuilder::BuildTrees(ByteVecotrPtr src, unordered_map<stKey, shared_ptr<typeTreeNode>> & leafMap)
{
	type_statistic_map map;
	statistic(src, map);

	return GenerateHuffmanTree(map, leafMap);
}

shared_ptr<MyBinaryTree<stNodeData>> HuffmanTreeBuilder::BuildTrees(typeImgPtr src, unordered_map<stKey, shared_ptr<typeTreeNode>> & leafMap)
{
	type_statistic_map map;
	statistic(src, map);

	return GenerateHuffmanTree(map,leafMap);
}

int HuffmanTreeBuilder::statistic(ByteVecotrPtr array, type_statistic_map & scale_statistic_map)
{
	int max_num = 0;
	for each (byte r in *array)
	{
		type_statistic_map::iterator it = scale_statistic_map.find(r);
		if (it != scale_statistic_map.end())
		{
			it->second += 1;
			if (it->second > max_num)
			{
				max_num = it->second;
			}
		}
		else
		{
			scale_statistic_map.insert({ r, 1 });
			if (1 > max_num)
			{
				max_num = 1;
			}
		}
	}

	return max_num;
}

int HuffmanTreeBuilder::statistic(typeImgPtr img, type_statistic_map & scale_statistic_map)
{
	scale_statistic_map.clear();

	int srcW = img->GetWidth();
	int srcH = img->GetHeight();
	int srcL = img->GetBPP();
	int srcClrCount = srcL / 8;
	int srcRowBytes = img->GetPitch();
	byte * srcBuf = (byte *)img->GetBits();

	int max_num = 0;
	if (srcClrCount > 0)
	{
		max_num = statistic(img->toByteVector(), scale_statistic_map);
	}
	else
	{
		byte bit_mask = 0;
		for (int i = 0; i < srcL; i++)
		{
			bit_mask |= 1 << i;
		}

		for (int i = 0; i < srcH; i++)
		{
			for (int j = 0; j < srcW; j++)
			{
				byte r = (srcBuf[i * srcRowBytes + (j * srcL) / 8] >> ((j * srcL) % 8)) & bit_mask;
				type_statistic_map::iterator it = scale_statistic_map.find(r);
				if (it != scale_statistic_map.end())
				{
					it->second += 1;
					if (it->second > max_num)
					{
						max_num = it->second;
					}
				}
				else
				{
					scale_statistic_map.insert({ r, 1 });
					if (1 > max_num)
					{
						max_num = 1;
					}
				}
			}
		}
	}

	return max_num;
}