#pragma once
//假设集合已经升序有序
#include<iostream>
using namespace std;

template<typename T>
struct SetNode
{
	T data;
	SetNode<T>* link;
	SetNode():link(nullptr) {};
	SetNode(T& a, SetNode<T>* ptr = nullptr) :data(a), link(ptr) {};
};

template<class T>
class LinkedSet {
	SetNode<T>* first, *last;
public:
	LinkedSet() { first = last = new SetNode<T>; }
	LinkedSet(LinkedSet<T>& R);
	//复制构造函数
	~LinkedSet() { makeEmpty(), delete first; }
	void makeEmpty();
	bool addMember(const T& x);
	bool delMember(const T& x);
	//删除集合中为X的元素
	LinkedSet<T>& operator=(LinkedSet<T>& R);
	//赋值
	LinkedSet<T>& operator+(LinkedSet<T>& R);
	//求this与R并集
	LinkedSet<T>& operator*(LinkedSet<T>& R);
	//求交集
	LinkedSet<T>& operator-(LinkedSet<T>& R);
	//求差
	bool IsContains(const T& x);
	//判断x是否是成员
	bool operator==(LinkedSet<T>& R);
	//判断this与r集合是否相等
	bool Min(T& x);
	bool Max(T& x);
};

template<class T>
LinkedSet<T>::LinkedSet<T>(LinkedSet<T>& R) {
	this->first = this->last = new SetNode<T>;
	SetNode<T>* p = R.first->link;;
	//R的第一个元素
	for (; p != nullptr; p = p->link) {
		last=last->link = new SetNode<T>(p->data);
	}
}

template<class T>
bool LinkedSet<T>::IsContains(const T& x){
	SetNode<T>* p = this->first->link;
	for (; p->data<x&&p!=nullptr; p = p->link);
	if (p != nullptr&&p->data == x)return true;
	else return false;
}

template<class T>
bool LinkedSet<T>::addMember(const T& x) {
	if (IsContains(x))return false;
	SetNode<T>* p = first->link, *pre = first;
	for (; p->data < x&&p != nullptr;) {
		pre = p;
		p = p->link;
	}
	SetNode<T>* newElem = new SetNode<T>(x);
	newElem->link = p;
	pre->link = newElem;
	if (p == nullptr)
		last = newElem;
	return true;

}

template<class T>
bool LinkedSet<T>::delMember(const T& x) {
	if (first->link == nullptr||!IsContains(x))return false;
	SetNode<T>* p = first->link, *pre = first;
	while (p != nullptr&&p->data < x) {
		pre = p;
		p = p->link;
	}
	if (p != null&&p->data == x) {
		pre->link = p->link;
		if (p == last)
			last = pre;
		delete p;
		return true;
	}
	else return false;
}

template<class T>
LinkedSet<T>& LinkedSet<T>::operator=(LinkedSet<T>& R) {
	this->first = this->last = new SetNode<T>;
	SetNode<T>* p = R.first->link;
	while (p != nullptr) {
		last = last->link = new SetNode<T>(p->data);
		p = p->link;
	}
	return *this;
}

template<class T>
LinkedSet<T>& LinkedSet<T>::operator+(LinkedSet<T>& R) {
	//结果暂存在A链中
	SetNode<T>* pa = this->first->link;
	SetNode<T>* pb = R.first->link;
	SetNode<T>* pc = first;
	while (pa != nullptr&&pb != nullptr) {
		if (pa->data == pb->data) {
			pc->link = pa;
			pa = pa->link;
			pb = pb->link;
		}
		else if (pa->data < pb->data) {
			pc->link = pa;
			pa = pa->link;
		}
		else {
			pc->link = new SetNode<T>(pb->data);
			pb = pb->link;
		}
		pc = pc->link;
	}
	if (pa == nullptr) {
		while (pb != nullptr) {
			pc=pc->link = new SetNode<T>(pb->data);
			pb = pb->link;
		}
	}
	else {
		pc->link = pa;
	}
	pc->link = nullptr;
	last = pc;
	return *this;
}

template<class T>
LinkedSet<T>& LinkedSet<T>::operator*(LinkedSet<T>& R) {
	SetNode<T>* pa = this->first->link;
	SetNode<T>* pb = R.first->link;
	SetNode<T>* pc = first;
	while (pa != nullptr&&pb != nullptr) {
		if (pa->data == pb->data) {
			pc=pc->link;
			pa = pa->link;
			pc = pc->link;
		}
		else if (pa->data < pb->data) {
			pc->link = pa->link;
			delete pa;
			pa = pc->link;
		}
		else {
			pb = pb->link;
		}
	}
	if (pa != nullptr) {
		while (pa != nullptr) {
			pc->link = pa->link;
			delete pa;
			pa = pc->link;
		}
	}
	pc->link = nullptr;
	last = pc;
	return *this;
}

template<class T>
LinkedSet<T>& LinkedSet<T>::operator-(LinkedSet<T>& R) {
	SetNode<T>* pa = this->first->link;
	SetNode<T>* pb = R.first->link;
	SetNode<T>* pc = first;
	while (pa != nullptr&&pb != nullptr) {
		if (pa->data == pb->data) {
			pc->link = pa->link;
			delete pa;
			pa = pc->link;
		}
		else if (pa->data < pb->data) {
			pc = pc->link;
			pa = pa->link;
		}
		else {
			pb = pb->link;
		}
	}
	if (pa == nullptr)
		last = pc;
	return *this;
}

template<class T>
bool LinkedSet<T>::operator==(LinkedSet<T>& R) {
	SetNode<T>* pa = first->link;
	SetNode<T>* pb = R.first->link;
	while (pa != nullptr&&pb != nullptr) {
		if (pa->data != pb->data) {
			return false;
		}
		pa = pa->link;
		pb = pb->link;
	}
	if (pa == pb == nullptr)return true;
	else return false;
}

template<class T>
bool LinkedSet<T>::Min(T& x) {
	T min;
	SetNode<T>* p = first->link;
	if (p == nullptr)return false;
	min = p->data;
	while (p != nullptr) {
		p = p->link;
		if (p->data < min)
			min = p->data;
	}
	x = min;
	return true;
}

template<class T>
bool LinkedSet<T>::Max(T& x) {
	T max;
	SetNode<T>* p = first->link;
	if (p == nullptr)return false;
	max = p->data;
	while (p != nullptr) {
		p = p->link;
		if (p->data > min)
			max = p->data;
	}
	x = max;
	return true;
}