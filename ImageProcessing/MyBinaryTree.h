#pragma once
#include <memory>

using namespace std;

template <class Type> class MyBinaryTree;

template <class Type> class TreeNode
{
	friend class MyBinaryTree<Type>;

private:
	Type data;
	shared_ptr<TreeNode<Type>> firstChild;
	shared_ptr<TreeNode<Type>> nextSibling;
	shared_ptr<TreeNode<Type>> parent;

public:
	TreeNode(Type value = NULL, shared_ptr<TreeNode<Type>> fc = NULL, shared_ptr<TreeNode<Type>> ns = NULL, shared_ptr<TreeNode<Type>> pt = NULL)
		:data(value), firstChild(fc), nextSibling(ns), parent(pt)
	{

	}

	void setParent(shared_ptr<TreeNode<Type>> pt)
	{
		parent = pt;
	}

	shared_ptr<TreeNode<Type>> getFirstChild()
	{
		return firstChild;
	}

	void setFirstChild(shared_ptr<TreeNode<Type>> fc)
	{
		firstChild = fc;
	}

	shared_ptr<TreeNode<Type>> getNextSlibing()
	{
		return nextSibling;
	}

	void setNextSlibing(shared_ptr<TreeNode<Type>> ns)
	{
		nextSibling = ns;
	}

	Type & getDataRef()
	{
		return data;
	}
};

template <class Type> class MyBinaryTree
{
public:
	MyBinaryTree()
	{
		root = current = NULL;
	}

	MyBinaryTree(shared_ptr<TreeNode<Type>> node)
	{
		root = current = node;
	}

	bool Root();           																					
	bool FirstChild();     																					
	bool NextSibling();
	bool Parent();
	void BuildRoot(Type rootVal);  									
	void InsertChild(Type value);  														
	bool Find(Type target);        															
	//bool Parent();                 														
	bool IsRoot();                 																	
	void RemovesubTree();          									
	Type GetCurrentData();     
	void setCurrentPos(shared_ptr<TreeNode<Type>> node);
	bool IsEmpty()                  									
	{
		return current == NULL;
	}
	bool IsLeaf()                   																
	{
		return current->firstChild == NULL;
	}

private:
	shared_ptr<TreeNode<Type>> root, current;
	bool Find(shared_ptr<TreeNode<Type>> p, Type target);
	void RemovesubTree(shared_ptr<TreeNode<Type>> p);
	//bool FindParent(shared_ptr<TreeNode<Type>> t, shared_ptr<TreeNode<Type>> p);
};