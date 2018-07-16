#pragma once
#include"BSTree.h"
class BSTSystem {
	BSTree<int> bstree;
	int RefValue;
public:
	bool InputElem(int value);
	//建立搜索二叉树
	bool InsertElem();
	//插入元素
	bool SearchElem();
	//搜索元素
	bool Choose();
};
