#pragma once
#include<iostream>
#include"Quene.h"
template<typename Type>
struct TreeNode {
	Type data;
	TreeNode<Type>*firstChild, *nextSibling;
	//��Ů�Լ��ֵܽ��
	TreeNode(Type value = 0, TreeNode<Type>* fc = nullptr, TreeNode<Type>* ns = nullptr) :data(value), firstChild(fc), nextSibling(ns) {}
};

template<class T>
class Tree {
	TreeNode<T>* root, *current;
	bool Find(TreeNode<T>* p, T value);
	//����PΪ������������value
	void RemovesubTree(TreeNode<T>* p);
	//ɾ��PΪ��������
	bool FindParent(TreeNode<T>* t, TreeNode<T>* p);
public:
	Tree() { root = current = nullptr };
	bool Root();
	//Ѱ�Ҹ�����ʹ֮��Ϊ��ǰ���
	bool IsEmpty() { return root == nullptr };
	bool FirstChild();
	//Ѱ�ҵ�ǰ���ĵ�һ����Ů������ʹ֮��Ϊ��ǰ���
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
	//�����ĸ��ڵ��Ϊ��ǰ���
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
		//��Ҫ�Ӹ�����p�ĸ��ڵ�
	}
}

template<class T>
bool Tree<T>::FindParent(TreeNode<T>* subtree, TreeNode<T>* p) {
	//��Ϊsubtree��Ѱ��P�ĸ��ڵ�,��ʹ֮��Ϊ��ǰ���
	TreeNode<T>* q = subtree->firstChild;
	while (q != nullptr&&q != p) {
		if (FindParent(q, p))return true;
		q = q->nextSibling;
	}
	if (q != nullptr&&q == p) {
		current = q;
		//ʹ֮��Ϊ��ǰ���
		return true;
	}
	else {
		current = nullptr;
		return false;
		//δ�ҵ����ڵ�
	}
}

template<class T>
bool Tree<T>::FirstChild() {
	//������Ѱ�ҵ�ǰ���ĳ��ӣ�����Ϊ��ǰ���
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
	//�ҵ��ýڵ�󣬳�Ϊ�ýڵ�
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
