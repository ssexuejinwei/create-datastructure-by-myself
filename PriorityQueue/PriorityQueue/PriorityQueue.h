#pragma once
#include<iostream>
template<typename Type>
struct LinkNode {
	Type value;
	int pry;
	LinkNode<Type>* Link;
	LinkNode(Type& x,int i, LinkNode<Type>* ptr = nullptr) :value(x),pry(i), link(ptr) {};
	LinkNode<Type>(LinkNode<Type>* ptr = nullptr) : link(ptr) {};
};

//该优先级队列priority值越小优先级越高
template<class Type>
class PriorityQueue {
	LinkNode<Type>* front;
	LinkNode<Type>* rear;
	LinkNode<Type>* getHead() { return front; }
public:
	PriorityQueue() :front(nullptr), rear(nullptr) {};
	PriorityQueue(Type& data, int i, LinkNode<Type>* ptr) {
		LinkNode<Type>* newNode = new LinkNode<Type>(ptr);
		newNode->pry = i;
		newNode->value = data;
		newNode->Link = nullptr;
		front = rear = newNode;
	}
	~PriorityQueue() { makeEmpty(); }
	int Length()const;
	//int Search(Type x);
	//找到队列中值x的结点，并返回其位置

	LinkNode<Type>* MinPry();
	//找到队列中优先级最高的结点，并返回其位置

	void makeEmpty();
	bool IsEmpty() { return front == nullptr };
	bool Enqueue(Type& data,int weight);
	bool Dequeue(Type& x);
	
};

template<class Type>
int PriorityQueue<Type>::Length()const {
	if (IsEmpty())return 0;
	else {
		LinkNode<Type>* p = getHead();
		int count = 1;
		while (p->Link != nullptr) {
			p = p->Link;
			count++;
		}
		return count;
	}
}

template<class Type>
void PriorityQueue<Type>::makeEmpty() {
	if (IsEmpty())return;
	LinkNode<Type>* p;
	while (front != nullptr) {
		p = front;
		front = front->Link;
		delete p;
	}
	return;
}

template<class Type>
bool PriorityQueue<Type>::Enqueue(Type& data, int weight) {
	LinkNode<Type>* p = new LinkNode<Type>(data, weight);
	if (front == nullptr)front = rear = p;
	else {
		rear->Link = p;
		rear = p;
	}
}

/*template<class Type>
int PriorityQueue<Type>::Search(Type& x) {
}*/

template<class Type>
LinkNode<Type>* PriorityQueue<Type>::MinPry() {
	if (IsEmpty())return nullptr;
	LinkNode<Type>* p = front;
	LinkNode<Type>* position;
	int minPry = front->pry;
	while (p != nullptr) {
		p = p->Link;
		if (p->pry < minPry) {
			MinPry = p->pry;
			position = p;
		}
	}
	return position;
}

template<class Type>
bool PriorityQueue<Type>::Dequeue(Type& x) {
	if (IsEmpty())return false;
	int minPry = front->pry;
	LinkNode<Type>* pre = front;
	//找到最小权结点的前一个结点
	LinkNode<Type>* position = front;
	LinkNode<Type>* p = front;
	LinkNode<Type>* q = front;
	//遍历工具结点p,q
	while (p != nullptr) {
		p = p->Link;
		if (p->pry < minPry) {
			MinPry = p->pry;
			position = p;
		}
	}
	while (q->value != MinPry) {
		pre = q;
		q = q->Link;
	}


}
