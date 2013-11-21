#pragma once
#ifndef _AFXDLL
	#define  _AFXDLL
#endif

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

#include "stdafx.h"
#include "MyBinaryTree.h"

template <class Type> void MyBinaryTree<Type>::BuildRoot(Type rootVal)
{
	root = current = shared_ptr(new TreeNode<Type>(rootVal));
}

template <class Type> bool MyBinaryTree<Type>::IsRoot()
{
	if (root == NULL)
	{
		return false;
	}
	else
	{
		return current == root;
	}
}

template <class Type> bool MyBinaryTree<Type>::Root()
{
	if (root == NULL)
	{
		current = NULL;
		return false;
	}
	else
	{
		current = root;
		return true;
	}
}

template <class Type>	Type MyBinaryTree<Type>::GetCurrentData()
{
	if (!IsEmpty())
	{
		return current->data;
	}
}

template <class Type> bool MyBinaryTree<Type>::FirstChild()
{
	if (current != NULL && current->firstChild != NULL)
	{
		current = current->firstChild;
		return true;
	}

	current = NULL;
	return false;
}

template <class Type> bool MyBinaryTree<Type>::NextSibling()
{
	if (current != NULL && current->nextSibling != NULL)
	{
		current = current->nextSibling;
		return true;
	}

	current = NULL;
	return false;
}

template <class Type> bool MyBinaryTree<Type>::Parent()
{
	if (current != NULL && current->parent != NULL)
	{
		current = current->parent;
		return true;
	}

	current = NULL;
	return false;
}

template <class Type> void MyBinaryTree<Type>::InsertChild(Type value)
{
	shared_ptr<TreeNode<Type>> newNode = shared_ptr(new TreeNode<Type>(value));
	newNode->data = value;

	if (current->firstChild == NULL)
	{
		current->firstChild = newNode;
	}
	else
	{
		TreeNode<Type> *p = current->firstChild;
		while (p->nextSibling != NULL)
		{
			p = p->nextSibling;
		}
		p->nextSibling = newNode;
	}

}

template <class Type>	bool MyBinaryTree<Type>::Find(shared_ptr<TreeNode<Type>> p, Type target)
{
	bool result = false;
	if (p->data == target)
	{
		result = true;
		current = p;
	}
	else
	{
		TreeNode<Type> *q = p->firstChild;
		while (q != NULL && !(result = Find(q, target)))
		{
			q = q->nextSibling;
		}
	}
	return result;
}

template <class Type> bool MyBinaryTree<Type>::Find(Type target)
{
	if (root == NULL)
	{
		return false;
	}
	return Find(root, target);
}

//template <class Type> bool Tree<Type>::FindParent(TreeNode<Type> *t, TreeNode<Type> *p)
//{
//	TreeNode<Type> *q = t->firstChild;
//	while (q != NULL && q != p)
//	{
//		bool ret = FindParent(q, p);
//		if (ret)
//		{
//			return ret;
//		}
//		q = q->nextSibling;
//	}
//	if (q != NULL && q == p)
//	{
//		current = t;
//		return true;
//	}
//	else
//		return false;
//}
//
//template <class Type> bool Tree<Type>::Parent()
//{
//	TreeNode<Type> * p = current, *t;
//	if (current == NULL || current == root)
//	{
//		current = NULL;
//		return false;
//	}
//	t = root;
//
//	bool ret = FindParent(t, p);
//
//	return ret;
//}

template <class Type> void MyBinaryTree<Type>::RemovesubTree(shared_ptr<TreeNode<Type>> p)
{
	TreeNode<Type> * q = p->firstChild, *next;
	while (q != NULL)
	{
		next = q->nextSibling;
		RemovesubTree(q);
		q = next;
	}
	delete p;
}

template <class Type> void MyBinaryTree<Type>::RemovesubTree()
{
	if (current != NULL)
	{
		if (current == root)
		{
			root = NULL;
		}
		RemovesubTree(current);
		current = NULL;
	}
}

template <class Type> void MyBinaryTree<Type>::setCurrentPos(shared_ptr<TreeNode<Type>> node)
{
	current = node;
}