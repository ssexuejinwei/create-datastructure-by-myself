#include"BSTSystem.h"
bool BSTSystem::InputElem(int value) {
	RefValue = value;
	cout << "please input key to create Bsort_Tree:" << endl;
	int x;
	cin >> x;
	while (x != value) {
		if (!(bstree.Insert(x))) {
			cout << "the input key<" << x << ">is have in!" << endl;
		}
		cin >> x;
	}
	cout << "Bsort_Tree is:" << endl;
	bstree.TreePrint();
	return true;
}

bool BSTSystem::InsertElem() {
	cout << "Please input key which inserted:";
	int x;
	cin >> x;
	bstree.Insert(x);
	bstree.TreePrint();
	return true;
}

bool BSTSystem::SearchElem() {
	cout << "Please input key which searched:";
	int x;
	cin >> x;
	if (bstree.Search(x)) {
		cout << "search success"<<endl;
	}
	else {
		cout << x << "is not exist！"<<endl;
	}
	return true;
}

bool BSTSystem::Choose() {
	cout << "Please select:";
	int index, tag = 1;
	while(cin>>index){
		if (index != 1 && tag == 1) {
			cout << "请先建立表,输入选项:";
			continue;
		}
		if (1 == index) {
			tag = 0;
			InputElem(0);
			cout << endl;
		}
		else if (2 == index) {
			InsertElem();
			cout << endl;
		}
		else if (3 == index) {
			SearchElem();
			cout << endl;
		}
		else if (4 == index) {
			exit(0);
		}
		else {
			cout << "输入有误请重新输入"<<endl;
		}
		cout << endl;
		cout << "Please select:";
	}
	return true;
}