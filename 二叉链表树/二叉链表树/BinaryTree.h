#pragma once
#include<iostream>
#include"LinkedStack.h"
#include"Quene.h"

using namespace std;

template<typename Type>
struct BinTreeNode {
	//二叉树结点定义
	Type data;
	BinTreeNode<Type> *leftChild, *rightChild;
	BinTreeNode() :leftChild(nullptr), rightChild(nullptr) {};
	BinTreeNode(Type& x, BinTreeNode<Type>* left = nullptr, BinTreeNode<Type>* right = nullptr) :data(x), 
		leftChild(left), rightChild(right) {};
};


template<typename Type>
struct stkNode {
	BinTreeNode<Type>* ptr;
	enum tag { L, R };
	stkNode(BinTreeNode<Type>* p=nullptr) :ptr(p), tag(L) {}
};
template<class Type>
class BinaryTree {
protected:
	BinTreeNode<Type>* root;
	Type RefValue;
	//数据输入停止标志
	void CreateBinTree(istream& in, BinTreeNode<Type>* &subTree);
	//从文件读入建树
	void PrintBTree(BinTreeNode<Type>* BT);
	//以广义表的方式输出二叉树
	bool Insert(BinTreeNode<Type>* &subTree, const T& x);
	//插入
	void destroy(BinTreeNode<Type>* subTree);
	//删除
	bool Find(BinTreeNode<Type>* subTree, const T&x)const;
	//查找
	BinTreeNode<Type>* Copy(BinTreeNode<Type>* orignode);
	//复制
	bool equal(BinTreeNode<Type>* a, BinTreeNode<Type>* b);
	//判断a,b子树是否相同

	int Height(BinTreeNode<Type>* subTree);
	//返回树的高度
	int Size(BinTreeNode<Type>* subTree);
	//返回树的结点数
	BinTreeNode<Type>* Parent(BinTreeNode<Type>* subTree, BinTreeNode<Type>* current);
	//返回父结点
	BinTreeNode<Type>* Find(BinTreeNode<Type>* subTree, const T& x)const;
	//搜寻X
	void Traverse(BinTreeNode<Type>* subTree, ostream& out);
	//前序遍历输出
	void preOrder(BinTreeNode<Type>* subTree, void(*visit)(BinTreeNode<Type>)* p);
	//前序遍历
	void inOrder(BinTreeNode<Type>* subTree, void(*visit)(BinTreeNode<Type>* p));
	//中序遍历
	void postOrder(BinTreeNode<Type>* Tree, void(*visit)(BinTreeNode<Type>*p));
	//后序遍历
	friend istream& operator >> (istream& in, BinaryTree<Type>& Tree);
	friend ostream& operator <<(ostream& out, BinaryTree<Type>& Tree);
	//分别重载输入输出运算符
public:
	BinaryTree() :root(nullptr) {};
	BinaryTree(Type value) :RefValue(value), root(nullptr) {};
	//构造函数
	BinaryTree(BinaryTree<Type>& s) {
		root = Copy(s.root);
	}
	//复制构造函数
	~BinaryTree() { destroy(root); }
	//析构函数
	bool IsEmpty() { return root == nullptr };
	//判断二叉树是否为空
	BinTreeNode<Type>* Parent(BinTreeNode<Type>* current) {
		return (root == nullptr || root == current) ?
			nullptr : Parent(root, current);
	}
	//返回父节点
	BinTreeNode<Type>* LeftChild(BinTreeNode<Type>* current) {
		return (current == nullptr) ? nullptr : current->leftChild;
	}
	//返回左子女
	BinTreeNode<Type>* RightChild(BinTreeNode<Type>* current) {
		return (current == nullptr) ? nullptr : current->rightChild;
	}
	//返回右子女
	int Height() { return Height(root); }
	//返回树高度
	int Size() {return Size(root);}
	//返回树节点数
	BinTreeNode<Type>* getRoot()const { return root };
	//取根结点
	void preOrder(void(*visit)(BinTreeNode<Type>* p)) {
		//preOrder(root, visit);
		//递归算法

		//非递归算法
		LinkedStack<BinTreeNode<Type>*>S;
		BinTreeNode<Type>* p = root;
		S.Push(nullptr);
		while (p != nullptr) {
			visit(p);
			if (p->rightChild != nullptr)S.Push(p);
			if (p->leftChild != nullptr)p = p->leftChild;
			else {
				S.Pop(p);
			}
		}
	}
	//前序遍历
	void inOrder(void(*visit)(BinTreeNode<Type>* p)) {
		//inOrder(root, visit);
		//递归算法

		//非递归算法
		LinkedStack<BinTreeNode<Type>* >S;
		BinTreeNode<Type>* p = root;
		S.Push(nullptr);
		do {
			while (p != nullptr) {
				S.Push(p);
				p = p->leftChild;
			}
			if (!S.Isempty()) {
				visit(p);
				S.Pop(p);
				p = p->rightChild;
			}

		}while(p!=nullptr||!S.Isempty())
	}
	//中序遍历
	void postOrder(void(*visit)(BinTreeNode<Type>* p)) {
		//postOrder(root, visit);
		//递归算法

		//非递归算法
		LinkedStack<stkNode<Type> >S;
		stkNode<Type> w;
		BinTreeNode<Type>* p = root;
		do {
			while (p != nullptr) {
				w.ptr = p; w.tag = L;
				S.Push(w);
				p=p->leftChild
			}
			int index = 1;
			//继续循环标记
			while (index && !S.Isempty()) {
				S.Pop(w);
				p = w.ptr;
				switch (w.tag) {
				case'L':w.tag = R; S.Push(w);
					index = 0;
					p = p->rightChild;
					break;
				case'R':visit(p);
					break;
				}
			}
		} while (!S.Isempty());
		cout << endl;

	}
	//后序遍历
	void levelOrder(void(*visit)(BinTreeNode<Type>* p));
	//层次序遍历
	int Insert(const Type item);
	BinTreeNode<Type>* Find(Type item)const;
	//搜索
	int operator==( BinaryTree<Type>& s, const BinaryTree<Type>& t) {
	}
};

template<class Type>
void BinaryTree<Type>::destroy(BinTreeNode<Type>* subTree) {
	//私有函数：若指针subTree不为空，则删除根为subTree的子树
	if (subTree != nullptr) {
		destroy(subTree->leftChild);
		destroy(subTree->rightChild);
		//分别递归删除左子树和右子树
		delete subTree;
	}
}

template<class Type>
BinTreeNode<Type>* BinaryTree<Type>::Copy(BinTreeNode<Type>* orignode) {
	//私有函数，返回一个指向以orignode为根的二叉树的副本
	if (orignode == nullptr)return nullptr;
	BinTreeNode<Type>* temp = new BinTreeNode<Type>;
	temp->data = orignode->data;
	temp->leftChild = Copy(orignode->leftChild);
	temp->rightChild = Copy(orignode->rightChild);
	return temp;
}

template<class Type>
BinTreeNode<Type>* BinaryTree<Type>::
Parent(BinTreeNode<Type>* subTree, BinTreeNode<Type>* current) {
	//私有函数，从节点subTree开始，搜索节点current的父节点
	//若找到current的父节点，则函数返回父节点地址，否则返回nullptr
	if (subTree == nullptr)return nullptr;
	if (subTree->leftChild == current || subTree->rightChild == current)return subTree;
	BinTreeNode<Type>* p;
	if ((p = Parent(subTree->leftChild, current)) != nullptr)return p;
	else return Parent(subTree->rightChild, current);
}

template<class Type>
void BinaryTree<Type>::Traverse(BinTreeNode<Type>* subTree, ostream& out){
	if (subTree != nullptr) {
		out << subTree->data;
		Traverse(subTree->leftChild, out);
		Traverse(subTree->rightChild, out);
	}
	else return;
	//为空则返回

}

template<class Type>
void BinaryTree<Type>::inOrder(BinTreeNode<Type>* subTree, void(*visit)(BinTreeNode<Type>* p)) {
	//中序遍历以subtree为根节点的子树
	if (subTree != nullptr) {
		inOrder(subTree->leftChild, visit);
		visit(subTree);
		inOrder(subTree->rightChild, visit);
	}
	return;
}

template<class Type>
void BinaryTree<Type>::postOrder(BinTreeNode<Type>* subTree, void(*visit)(BinTreeNode<Type>* p)) {
	if (subTree != nullptr) {
		postOrder(subTree->leftChild, visit);
		postOrder(subTree->rightChild, visit);
		visit(subTree;)
	}
	return;
}

template<class Type>
void BinaryTree<Type>::preOrder(BinTreeNode<Type>* subTree, void(*visit)(BinTreeNode<Type>)* p) {
	if(subTree!=nullptr){
		visit(subtree);
		preOrder(subTree->leftChild, visit);
		preOrder(subTree->rightChild, visit);
	}
	return;
}

template<class Type>
int BinaryTree<Type>::Size(BinTreeNode<Type>* subTree) {
	if (subTree == nullptr)return 0;
	else {
		return 1 + Size(subTree->leftChild) + Size(subTree->rightChild);
	}
}

template<class Type>
int BinaryTree<Type>::Height(BinTreeNode<Type>* subTree) {
	if (subTree == nullptr)return 0;
	else {
		int i = Height(subTree->leftChild);
		int j = Height(subTree->rightChild);
		return (i >= j) ? i + 1 : j + 1;
		//增加根节点时，高度加1
	}
}

template<class Type>
bool BinaryTree<Type>::equal(BinTreeNode<Type>* a, BinTreeNode<Type>* b) {
	if (a == nullptr&&b == nullptr)return true;
	if (a != nullptr&&b != nullptr&&a->data == b->data
		&&equal(a->leftChild, b->leftChild) && equal(a->rightChild, b->rightChild))
		return true;
	else return false;
}

template<class Type>
void  BinaryTree<Type>::CreateBinTree(istream& in, BinTreeNode<Type>* &subTree) {
	//以递归的方式建立二叉树
	Type item;
	if (!in.eof()) {
		in >> item;
		if (item != RefValue) {
			subTree = new BinTreeNode<Type>(item);
			if(subTree==nullptr)
			{
				cerr << "存储分配出错" << endl;
				exit(1);
			}
			CreateBinTree(in, subTree->leftChild);
			CreateBinTree(in, subTree->rightChild);
		}
		else subTree = nullptr;
	}
}

template<class Type>
void  BinaryTree<Type>::PrintBTree(BinTreeNode<Type>* BT) {
	if (BT != nullptr) {
		cout << BT->data;
		if (BT->leftChild != nullptr || BT->rightChild != nullptr) {
			cout << "(";
			PrintBTree(BT->leftChild);
			cout << ",";
			if(BT->rightChild!=nullptr)
				PrintBTree(BT->rightChild);
			cout << ")";
		}
	}
}

template<class Type>
istream& operator >> (istream& in, BinaryTree<Type>& Tree) {
	//重载操作:输入并建立一棵二叉树Tree，in是输入流对象，用广义表的方法
	return in;
}

template<class Type>
ostream& operator<<(ostream& out, BinaryTree<Type>& Tree) {
	out << "二叉树的前序遍历";
	Tree.Traverse(Tree.root, out);
	out << endl;
	return out;
}