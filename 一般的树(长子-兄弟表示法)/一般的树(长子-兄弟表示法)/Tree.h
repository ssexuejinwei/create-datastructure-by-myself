#pragma once
#include<iostream>
#include"Quene.h"
template<typename Type>
struct TreeNode {
	Type data;
	TreeNode<Type>*firstChild, *nextSibling;
	//子女以及兄弟结点
	TreeNode(Type value = 0, TreeNode<Type>* fc = nullptr, TreeNode<Type>* ns = nullptr) :data(value), firstChild(fc), nextSibling(ns) {}
};

template<class T>
class Tree {
	TreeNode<T>* root, *current;
	bool Find(TreeNode<T>* p, T value);
	//在以P为根的树中搜索value
	void RemovesubTree(TreeNode<T>* p);
	//删除P为根的子树
	bool FindParent(TreeNode<T>* t, TreeNode<T>* p);
public:
	Tree() { root = current = nullptr };
	bool Root();
	//寻找根并且使之成为当前结点
	bool IsEmpty() { return root == nullptr };
	bool FirstChild();
	//寻找当前结点的第一个子女，并且使之成为当前结点
	bool NextSibling();
	bool Parent();
	bool Find(T target);
	void PreOrder(std::ostream& out, TreeNode<T>* p) {
		if (p != nullptr) {
			out << p->data;
			for (p = p->firstChild; p != nullptr; p = p->nextSibling)
				PreOrder(out, p);
		}
	}
	void PostOrder(std::ostream& out, TreeNode<T>* p) {
		if (p != nullptr) {
			for (p = p->firstChild; p != nullptr; p = p->nextSibling)
				PostOrder(out, p);
			out << p->data;
		}
	};
	void LevelOrder(std::ostream& out, TreeNode<T>* p) {
		LinkedQueue<TreeNode<T>* >Q;
		if (p != nullptr) {
			Q.Enqueue(p);
			while (!Q.is_empty()) {
				Q.Dequeue(p);
				out << p->data;
				for (p = p->firstChild; p != nullptr; p = p->nextSibling) {
					Q.Enqueue(p);
				}
			}
		}
	}
};

template<class T>
bool Tree<T>::Root() {
	//让树的根节点成为当前结点
	if (root == nullptr) {
		current = nullptr;
		return false;
	}
	else {
		current = root;
		return true;
	}
}

template<class T>
bool Tree<T>::Parent() {
	TreeNode* p = current;
	if (current == nullptr || current == root)
		return false;
	else
	{
		return FindParent(root, p);
		//需要从根来找p的父节点
	}
}

template<class T>
bool Tree<T>::FindParent(TreeNode<T>* subtree, TreeNode<T>* p) {
	//根为subtree，寻找P的父节点,并使之成为当前结点
	TreeNode<T>* q = subtree->firstChild;
	while (q != nullptr&&q != p) {
		if (FindParent(q, p))return true;
		q = q->nextSibling;
	}
	if (q != nullptr&&q == p) {
		current = q;
		//使之成为当前结点
		return true;
	}
	else {
		current = nullptr;
		return false;
		//未找到父节点
	}
}

template<class T>
bool Tree<T>::FirstChild() {
	//在树中寻找当前结点的长子，并成为当前结点
	if (current != nullptr&&current->firstChild != nullptr) {
		current = current->firstChild;
		return true;
	}
	else {
		current = nullptr;
		return false;
	}
}

template<class T>
bool Tree<T>::NextSibling() {
	if (current->nextSibling != nullptr&&current != nullptr) {
		current = current->nextSibling;
		return true;
	}
	else {
		current = nullptr;
		return false;
	}
}

template<class T>
bool Tree<T>::Find(T value) {
	if (IsEmpty())return false;
	return Find(root, T value);
}

template<class T>
bool Tree<T>::Find(TreeNode<T>* p, T value) {
	//找到该节点后，成为该节点
	bool result;
	if (p->data == value) {
		current = p;
		return true;
	}
	else {
		TreeNode<T>*q = p->firstChild;
		while(q!=nullptr&&!(result=Find(q,value))){
			q = q->nextSibling;
		}
	}
	return result;
}

template<class T>
void Tree<T>::RemovesubTree(TreeNode<T>* subTree) {
	TreeNode<T>* p = subTree;
	if (subTree != nullptr) {
		for (subTree = subTree->firstChild; subTree != nullptr; subTree = subTree->nextSibling) {
			RemovesubTree(subTree);
			delete p;
		}
	}

}
