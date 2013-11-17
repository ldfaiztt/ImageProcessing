#pragma once

template <class Type> class Tree;

template <class Type> class TreeNode
{
	friend class Tree<Type>;

private:
	Type data;
	TreeNode<Type> * firstChild;
	TreeNode<Type> * nextSibling;
	TreeNode<Type> * parent;

	TreeNode(Type value = NULL, TreeNode<Type> *fc = NULL, TreeNode<Type> *ns = NULL, TreeNode<Type> *pt = NULL)
		:data(value), firstChild(fc), nextSibling(ns), parent(pt)
	{

	}
};

template <class Type> class Tree
{
public:
	Tree()
	{
		root = current = NULL;
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
	bool IsEmpty()                  									
	{
		return current == NULL;
	}
	bool IsLeaf()                   																
	{
		return current->firstChild == NULL;
	}

private:
	TreeNode<Type> *root, *current;
	bool Find(TreeNode<Type> *p, Type target);
	void RemovesubTree(TreeNode<Type> *p);
	//bool FindParent(TreeNode<Type> *t, TreeNode<Type> *p);
};