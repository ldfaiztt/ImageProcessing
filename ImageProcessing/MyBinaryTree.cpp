#include "stdafx.h"
#include "MyBinaryTree.h"

template <class Type> void Tree<Type>::BuildRoot(Type rootVal)
{
	root = current = new TreeNode<Type>(rootVal);
}

template <class Type> bool Tree<Type>::IsRoot()
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

template <class Type> bool Tree<Type>::Root()
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

template <class Type>	Type Tree<Type>::GetCurrentData()
{
	if (!IsEmpty())
	{
		return current->data;
	}
}

template <class Type> bool Tree<Type>::FirstChild()
{
	if (current != NULL && current->firstChild != NULL)
	{
		current = current->firstChild;
		return true;
	}

	current = NULL;
	return false;
}

template <class Type> bool Tree<Type>::NextSibling()
{
	if (current != NULL && current->nextSibling != NULL)
	{
		current = current->nextSibling;
		return true;
	}

	current = NULL;
	return false;
}

template <class Type> bool Tree<Type>::Parent()
{
	if (current != NULL && current->parent != NULL)
	{
		current = current->parent;
		return true;
	}

	current = NULL;
	return false;
}

template <class Type> void Tree<Type>::InsertChild(Type value)
{
	TreeNode<Type> * newNode = new TreeNode<Type>(value);
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

template <class Type>	bool Tree<Type>::Find(TreeNode<Type> *p, Type target)
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

template <class Type> bool Tree<Type>::Find(Type target)
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

template <class Type> void Tree<Type>::RemovesubTree(TreeNode<Type> *p)
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

template <class Type> void Tree<Type>::RemovesubTree()
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
