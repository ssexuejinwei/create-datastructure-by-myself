#pragma once
#include<iostream>
#include"LinkedStack.h"
#include"Quene.h"

using namespace std;

template<typename Type>
struct BinTreeNode {
	//��������㶨��
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
	//��������ֹͣ��־
	void CreateBinTree(istream& in, BinTreeNode<Type>* &subTree);
	//���ļ����뽨��
	void PrintBTree(BinTreeNode<Type>* BT);
	//�Թ����ķ�ʽ���������
	bool Insert(BinTreeNode<Type>* &subTree, const T& x);
	//����
	void destroy(BinTreeNode<Type>* subTree);
	//ɾ��
	bool Find(BinTreeNode<Type>* subTree, const T&x)const;
	//����
	BinTreeNode<Type>* Copy(BinTreeNode<Type>* orignode);
	//����
	bool equal(BinTreeNode<Type>* a, BinTreeNode<Type>* b);
	//�ж�a,b�����Ƿ���ͬ

	int Height(BinTreeNode<Type>* subTree);
	//�������ĸ߶�
	int Size(BinTreeNode<Type>* subTree);
	//�������Ľ����
	BinTreeNode<Type>* Parent(BinTreeNode<Type>* subTree, BinTreeNode<Type>* current);
	//���ظ����
	BinTreeNode<Type>* Find(BinTreeNode<Type>* subTree, const T& x)const;
	//��ѰX
	void Traverse(BinTreeNode<Type>* subTree, ostream& out);
	//ǰ��������
	void preOrder(BinTreeNode<Type>* subTree, void(*visit)(BinTreeNode<Type>)* p);
	//ǰ�����
	void inOrder(BinTreeNode<Type>* subTree, void(*visit)(BinTreeNode<Type>* p));
	//�������
	void postOrder(BinTreeNode<Type>* Tree, void(*visit)(BinTreeNode<Type>*p));
	//�������
	friend istream& operator >> (istream& in, BinaryTree<Type>& Tree);
	friend ostream& operator <<(ostream& out, BinaryTree<Type>& Tree);
	//�ֱ�����������������
public:
	BinaryTree() :root(nullptr) {};
	BinaryTree(Type value) :RefValue(value), root(nullptr) {};
	//���캯��
	BinaryTree(BinaryTree<Type>& s) {
		root = Copy(s.root);
	}
	//���ƹ��캯��
	~BinaryTree() { destroy(root); }
	//��������
	bool IsEmpty() { return root == nullptr };
	//�ж϶������Ƿ�Ϊ��
	BinTreeNode<Type>* Parent(BinTreeNode<Type>* current) {
		return (root == nullptr || root == current) ?
			nullptr : Parent(root, current);
	}
	//���ظ��ڵ�
	BinTreeNode<Type>* LeftChild(BinTreeNode<Type>* current) {
		return (current == nullptr) ? nullptr : current->leftChild;
	}
	//��������Ů
	BinTreeNode<Type>* RightChild(BinTreeNode<Type>* current) {
		return (current == nullptr) ? nullptr : current->rightChild;
	}
	//��������Ů
	int Height() { return Height(root); }
	//�������߶�
	int Size() {return Size(root);}
	//�������ڵ���
	BinTreeNode<Type>* getRoot()const { return root };
	//ȡ�����
	void preOrder(void(*visit)(BinTreeNode<Type>* p)) {
		//preOrder(root, visit);
		//�ݹ��㷨

		//�ǵݹ��㷨
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
	//ǰ�����
	void inOrder(void(*visit)(BinTreeNode<Type>* p)) {
		//inOrder(root, visit);
		//�ݹ��㷨

		//�ǵݹ��㷨
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
	//�������
	void postOrder(void(*visit)(BinTreeNode<Type>* p)) {
		//postOrder(root, visit);
		//�ݹ��㷨

		//�ǵݹ��㷨
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
			//����ѭ�����
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
	//�������
	void levelOrder(void(*visit)(BinTreeNode<Type>* p));
	//��������
	int Insert(const Type item);
	BinTreeNode<Type>* Find(Type item)const;
	//����
	int operator==( BinaryTree<Type>& s, const BinaryTree<Type>& t) {
	}
};

template<class Type>
void BinaryTree<Type>::destroy(BinTreeNode<Type>* subTree) {
	//˽�к�������ָ��subTree��Ϊ�գ���ɾ����ΪsubTree������
	if (subTree != nullptr) {
		destroy(subTree->leftChild);
		destroy(subTree->rightChild);
		//�ֱ�ݹ�ɾ����������������
		delete subTree;
	}
}

template<class Type>
BinTreeNode<Type>* BinaryTree<Type>::Copy(BinTreeNode<Type>* orignode) {
	//˽�к���������һ��ָ����orignodeΪ���Ķ������ĸ���
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
	//˽�к������ӽڵ�subTree��ʼ�������ڵ�current�ĸ��ڵ�
	//���ҵ�current�ĸ��ڵ㣬�������ظ��ڵ��ַ�����򷵻�nullptr
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
	//Ϊ���򷵻�

}

template<class Type>
void BinaryTree<Type>::inOrder(BinTreeNode<Type>* subTree, void(*visit)(BinTreeNode<Type>* p)) {
	//���������subtreeΪ���ڵ������
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
		//���Ӹ��ڵ�ʱ���߶ȼ�1
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
	//�Եݹ�ķ�ʽ����������
	Type item;
	if (!in.eof()) {
		in >> item;
		if (item != RefValue) {
			subTree = new BinTreeNode<Type>(item);
			if(subTree==nullptr)
			{
				cerr << "�洢�������" << endl;
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
	//���ز���:���벢����һ�ö�����Tree��in�������������ù����ķ���
	return in;
}

template<class Type>
ostream& operator<<(ostream& out, BinaryTree<Type>& Tree) {
	out << "��������ǰ�����";
	Tree.Traverse(Tree.root, out);
	out << endl;
	return out;
}