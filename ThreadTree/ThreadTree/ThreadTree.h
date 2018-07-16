#pragma once
template<template T>
struct ThreadNode {
	int ltag, rtag;
	//1表示线索，0表示子节点
	ThreadNode<T>* leftChild,* rightChild;
	T data;
	ThreadNode(const T item):data(item), leftChild(nullptr), rightChild(nullptr),
		ltag(0), rtag(0) {};
};

template<class T>
class ThreadTree {
	ThreadNode<T>* root;
	void createInThread(ThreadNode<T>* current, ThreadNode<T>* &pre);
	//中序遍历建立线索二叉树
	ThreadNode<T>* parent(ThreadNode<T>* t);
	//寻找结点t的父节点
public:
	ThreadNode() :root(nullptr) {};
	void createInThread();
	ThreadNode<T>* First(ThreadNode<T>* current);
	//寻找该结点下，中序下，第一个结点
	ThreadNode<T>* Last(ThreadNode<T>* current);
	ThreadNode<T>* Next(ThreadNode<T>* current);
	ThreadNode<T>* Prior(ThreadNode<T>* current);
	void Inorder(void(*visit)(ThreadNode<T>* p));
};

template<class T>
ThreadNode<T>* ThreadTree<T>::First(ThreadNode<T>* current) {
	ThreadNode<T>* p = current;
	while (p->ltag == 0) {
		p = p->leftChild;
	}
	return p;
}

template<class T>
ThreadNode<T>* ThreadTree<T>::Next(ThreadNode<T>* current) {
	ThreadNode<T>* p = current->rightChild;
	if (current->rtag == 1)return p;
	else {
		return First(p);
	}
}

template<class T>
ThreadNode<T>* ThreadTree<T>::Last(ThreadNode<T>* current) {
	ThreadNode<T>* p = current;
	while (p->rtag == 0)p = p->rightChild;
	return p;
}

template<class T>
ThreadNode<T>* ThreadTree<T>::Prior(ThreadNode<T>* current) {
	ThreadNode<T>* p = current->leftChild;
	if (current->ltag == 1)return p;
	else {
		return Last(p);
	}
}

template<class T>
void ThreadTree<T>::Inorder(void(*visit)(ThreadNode<T>* p)) {
	ThreadNode<T>* p = First(root);
	for (; p != nullptr; p = Next(p)) {
		visit(p);
	}
}

template<class T>
void ThreadTree<T>::createInThread() {
	ThreadNode<T>* pre = nullptr;
	if (root != nullptr) {
		createInThread(root, pre);
		pre->rightChild = nullptr;
		pre->rtag = 1;
		//后处理中序的最后一个结点
	}
}

template<class T>
void ThreadTree<T>::createInThread(ThreadNode<T>* current,ThreadNode<T>*& pre) {
	//通过中序遍历，对二叉树进行线索化
	if (current == nullptr)return;
	createInThread(current->leftChild, pre);
	if (current->leftChild == nullptr) {
		//建立当前节点的前驱线索
		current->leftChild = pre;
		current->ltag = 1;
	}
	if (pre != nullptr&&pre->rightChild == nullptr) {
		//建立前驱节点的后继
		pre->rightChild = current;
		pre->rtag = 1;
	}
	pre = current;
	//前驱跟上，向后遍历
	createInThread(current->rightChild, pre);
}

template<class T>
ThreadNode<T>* ThreadTree<T>::parent(ThreadNode<T>* t) {
	ThreadNode<T>* p;
	if (t == root)return nullptr;
	for (p = t; p->ltag == 0; p = p->leftChild);
	if (p->leftChild != nullptr) {
		for (p = p->leftChild; p != nullptr&&p->leftChild != t&&p->rightChild != t; p = p->rightChild);
	}
	if (p == nullptr || p->leftChild == nullptr) {
		for (p = t; p->rtag == 0; p = p->rightChild);
		for (p = p->rightChild; p != nullptr&&p->leftChild != t&&p->rightChild != t; p = p->leftChild);
	}
	return p;
}


