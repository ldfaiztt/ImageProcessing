#pragma once
#include "MyImage.h"
#include "MyBinaryTree.h"
#include <list>
#include <unordered_map>

struct stNodeData
{
	stKey GrayScale;
	stVal Probability;
	byte Symbol;
};

typedef TreeNode<stNodeData> typeTreeNode;

class BuildHuffmanTree
{
protected:
	shared_ptr<MyBinaryTree<stNodeData>> GenerateHuffmanTree(type_statistic_map & statistic_map, unordered_map<stKey, shared_ptr<typeTreeNode>> & leafMap);
	int statistic(typeImgPtr img, type_statistic_map & scale_statistic_map);
	int statistic(ByteVecotrPtr array, type_statistic_map & scale_statistic_map);
public:
	BuildHuffmanTree();
	virtual ~BuildHuffmanTree();

	shared_ptr<MyBinaryTree<stNodeData>> BuildTrees(typeImgPtr src, unordered_map<stKey, shared_ptr<typeTreeNode>> & leafMap);
	shared_ptr<MyBinaryTree<stNodeData>> BuildTrees(ByteVecotrPtr src, unordered_map<stKey, shared_ptr<typeTreeNode>> & leafMap);
};

