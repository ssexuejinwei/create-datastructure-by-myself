#pragma once
#include"BSTree.h"
class BSTSystem {
	BSTree<int> bstree;
	int RefValue;
public:
	bool InputElem(int value);
	//��������������
	bool InsertElem();
	//����Ԫ��
	bool SearchElem();
	//����Ԫ��
	bool Choose();
};
