#pragma once
#include<iostream>
#include<stdlib.h>
using namespace std;

template<class E，class K>
struct BSTNode {
	E data;
	BSTNode<E,K>* left, *right;
	BSTNode() :left(nullptr), right(nullptr) {}
	BSTNode(const E d, BSTNode<E,K>* lp = nullptr, BSTNode<E,K>* rp = nullptr) :data(d), left(lp), right(rp) {}
	void setData(E d) { data = d }
	E getData() { return data; }
};

template<class E,class K>
class BSTree {
	BSTNode<E,K>* root;
	K RefValue;
	//输入停止标志
	BSTNode<T,K>* Search(const K x, BSTNode<E,K>* ptr);
	void makeEmpty(BSTNode<E,K>* & ptr);
	void PrintTree(BSTNode<E,K>* ptr)const;
	bool Insert(const E& x, BSTNode<E,K>* & ptr);
	bool Remove(const K x, BSTNode<E,K>*& ptr);
public:
	BSTree():root(nullptr){}
	~BSTree() { makeEmpty(root); }
	BSTNode<E,K>* Search(const K x) {
		return Search(K, root);
	}
	bool Insert(const E& x) {
		return Insert(x, root);
	}
	bool Remove(const K x) {
		return Remove(x, root);
	}
	void TreePrint() {
		PrintTree(root);
	}

};

template<class E,class K>
BSTNode<E,K>* BSTree<E.K>::Search(const K x, BSTNode<E,K>* ptr) {
	//在以根为Ptr的树中搜索X
	if (ptr == nullptr)return nullptr;
	else if (x < ptr->data)return Search(x, ptr->left);
	else if (x > ptr->data)return Search(x, ptr->right);
	else return ptr;
}

template<class E,class K>
bool BSTree<E,K>::Insert(const E& x, BSTNode<E,K>* & ptr){
	//在以ptr为根的树中插入值为x的结点
	if (ptr == nullptr) {
		ptr = new BSTNode<T>(x);
		//创建新结点
		if(ptr==nullptr)
		{
			cerr << "out of space" << endl;
			exit(1);
		}
		return true;
	}
	else if (x < ptr->data)Insert(x, ptr->left);
	else if (x > ptr->data)Insert(x, ptr->right);
	else return false;

}

template<class E,class K>
bool BSTree<T>::Remove(const K x, BSTNode<E,K>*& ptr) {
	BSTNode<E,K>* temp;
	if (ptr != nullptr) {
		if (x < ptr->data)Remove(x, ptr->left);
		else if (x > ptr->data)Remove(x, ptr->right);
		else if (ptr->left != nullptr&&ptr->right != nullptr) {
			//ptr结点有两个子节点
			temp = ptr->right;
			while (temp->left != nullptr)temp = temp->left;
			ptr->data = temp->data;
			Remove(ptr->data, ptr->right);
		}
		else {
			temp = ptr;
			if (ptr->left == nullptr)ptr = ptr->right;
			else if (ptr->right == nullptr)ptr = ptr->left;
			delete temp;
			return true;
		}
	}
	return false;
}

template<class E,class K>
void  BSTree<E,K>::PrintTree(BSTNode<E,K>* ptr)const {
	if (ptr != nullptr) {
		PrintTree(ptr->left);
		cout << ptr->data << "->";
		PrintTree(ptr->right);
	}
}

template<class E,class K>
void BSTree<E,K>::makeEmpty(BSTNode<E,K>* & ptr) {
	if (ptr != nullptr) {
		makeEmpty(ptr->left);
		makeEmpty(ptr->right);
		delete ptr;
	}
}